/*
Copyright 2017 Google, Inc

Licensed under the Apache License, Version 2.0 ( the "License" );
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http ://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include <rpal/rpal.h>
#include <rpHostCommonPlatformIFaceLib/rpHostCommonPlatformIFaceLib.h>
#include <kernelAcquisitionLib/kernelAcquisitionLib.h>
#include <librpcm/librpcm.h>
#include <libRestOutput/libRestOutput.h>
#include <cryptoLib/cryptoLib.h>

//=============================================================================
//  RP HCP Module Requirements
//=============================================================================
RpHcp_ModuleId g_current_Module_id = RP_HCP_MODULE_ID_BULK_COLLECTOR;
#define RPAL_FILE_ID    111


//=============================================================================
//  Core Functionality
//=============================================================================

// The destination URL to POST data to.
#ifndef BULK_COLLECTOR_DEST
#define BULK_COLLECTOR_DEST                 "www.google.com:443/"
#endif

#ifndef BULK_COLLECTOR_TIMEOUT
#define BULK_COLLECTOR_TIMEOUT              (60 * 10)
#endif

// The API key to use in the POST.
#ifndef BULK_COLLECTOR_API_KEY
#define BULK_COLLECTOR_API_KEY              "x-goog-api-key: abcdef"
#endif

// The customer id.
#ifndef BULK_COLLECTOR_CUSTOMER_ID
#define BULK_COLLECTOR_CUSTOMER_ID          "\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F"
#endif

// The collector id.
#ifndef BULK_COLLECTOR_COLLECTOR_ID
#define BULK_COLLECTOR_COLLECTOR_ID         "\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F"
#endif

// The maximum number of Slabs that are kept in memory before offloading to disk.
#ifndef BULK_COLLECTOR_MAX_SLABS_IN_MEM
#define BULK_COLLECTOR_MAX_SLABS_IN_MEM     (50)
#endif

#ifndef BULK_COLLECTOR_SLAB_SIZE
#define BULK_COLLECTOR_SLAB_SIZE    (1024 * 1024 * 5)
#endif

typedef struct
{
    RU32 bytesInSlab;
    RU8 data[ BULK_COLLECTOR_SLAB_SIZE ];
} Slab;

typedef struct
{
    RU32 nInStash;
    Slab* slabs[ BULK_COLLECTOR_MAX_SLABS_IN_MEM ];
} Stash;

RPRIVATE rMutex g_stashMutex = NULL;
RPRIVATE rEvent g_exfilEvent = NULL;

RPRIVATE RU32 g_nSlabsInMem = 0;
RPRIVATE Stash g_exfilStash = { 0 };
RPRIVATE Stash g_readyStash = { 0 };

RPRIVATE
Slab*
    _newSlab
    (

    )
{
    Slab* pSlab = NULL;
    if( NULL != ( pSlab = rpal_memory_alloc( sizeof( Slab ) ) ) )
    {
        g_nSlabsInMem++;
    }
    return pSlab;
}

RPRIVATE
RBOOL
    slabToPayload
    (
        Slab* pSlab,
        rString payload
    )
{
    RBOOL isSuccess = FALSE;

    rSequence jsonPayload = NULL;
    rList jsonEnvelope = NULL;
    rSequence chunk = NULL;
    rSequence metadata = NULL;
    rSequence source = NULL;
    RU8 collectionUuid[ RPAL_UUID_SIZE ] = { 0 };

    RPCHAR jsonMap[] = {
        "chunk",        // 0
        "metadata",     // 1
        "id",           // 2
        "type",         // 3
        "customer_id",  // 4
        "collector_id", // 5
        "size",         // 6
        "source",       // 7
        "data",         // 8
    };

    if( NULL != pSlab &&
        NULL != payload )
    {   
        if( NULL != ( jsonPayload = rSequence_new() ) &&
            NULL != ( jsonEnvelope = rList_new( 0, RPCM_SEQUENCE ) ) &&
            NULL != ( chunk = rSequence_new() ) &&
            NULL != ( metadata = rSequence_new() ) &&
            NULL != ( source = rSequence_new() ) &&
            rSequence_addBUFFER( source, 4, (RPU8)BULK_COLLECTOR_CUSTOMER_ID, sizeof( BULK_COLLECTOR_CUSTOMER_ID ) ) &&
            rSequence_addBUFFER( source, 5, (RPU8)BULK_COLLECTOR_COLLECTOR_ID, sizeof( BULK_COLLECTOR_COLLECTOR_ID ) ) &&
            rSequence_addRU32( metadata, 3, 4 ) &&
            CryptoLib_genRandomBytes( collectionUuid, sizeof( collectionUuid ) ) &&
            rSequence_addBUFFER( metadata, 2, collectionUuid, sizeof( collectionUuid ) ) &&
            rSequence_addBUFFER( chunk, 8, pSlab->data, pSlab->bytesInSlab ) &&
            rSequence_addSEQUENCE( metadata, 7, source ) &&
            rSequence_addSEQUENCE( chunk, 1, metadata ) &&
            rSequence_addSEQUENCE( jsonPayload, 0, chunk ) &&
            rList_addSEQUENCE( jsonEnvelope, jsonPayload ) )
        {
            if( rList_toJson( jsonEnvelope, jsonMap, ARRAY_N_ELEM( jsonMap ), payload ) )
            {
                isSuccess = TRUE;
            }
        }

        rSequence_shallowFree( jsonPayload );
        rList_shallowFree( jsonEnvelope );
        rSequence_shallowFree( chunk );
        rSequence_shallowFree( metadata );
        rSequence_shallowFree( source );
    }

    return isSuccess;
}

RPRIVATE
RU32
RPAL_THREAD_FUNC
    exfilThread
    (
        rEvent isTimeToStop
    )
{
    Slab* pSlab = NULL;
    RU32 i = 0;
    rString payload = NULL;
    restOutputContext restCtx = NULL;
    RU32 statusCode = 0;

    if( NULL != ( restCtx = restOutput_newContext( BULK_COLLECTOR_DEST, BULK_COLLECTOR_API_KEY ) ) )
    {
        if( NULL != ( payload = rpal_stringbuffer_new( 1024, 10 * 1024 ) ) )
        {
            while( !rEvent_wait( isTimeToStop, 0 ) )
            {
                if( rEvent_wait( g_exfilEvent, MSEC_FROM_SEC( 1 ) ) )
                {
                    rMutex_lock( g_stashMutex );

                    // Make sure there is something in the Stash, pop the first Slab.
                    if( 0 != g_exfilStash.nInStash )
                    {
                        pSlab = g_exfilStash.slabs[ 0 ];

                        // Move all the Slabs up in the queue.
                        for( i = 1; i < g_exfilStash.nInStash; i++ )
                        {
                            g_exfilStash.slabs[ i - 1 ] = g_exfilStash.slabs[ i ];
                        }

                        g_exfilStash.nInStash--;
                        g_exfilStash.slabs[ g_exfilStash.nInStash ] = NULL;
                    }

                    rMutex_unlock( g_stashMutex );
                }

                // Ok we got a Slab to send home.
                if( NULL != pSlab )
                {
                    // Assemble the payload.
                    if( slabToPayload( pSlab, payload ) )
                    {
                        // We successfully assembled a JSON string for payload.
                        if( restOutput_send( restCtx, rpal_stringbuffer_getStringA( payload ), &statusCode, BULK_COLLECTOR_TIMEOUT ) )
                        {
                            rpal_debug_info( "REST POST Sent with status code: " RF_U32, statusCode );
                        }
                        else
                        {
                            rpal_debug_info( "REST POST Failed to send" );
                        }
                    }

                    // We are now done with this Slab, move it to the ready Stash.
                    rMutex_lock( g_stashMutex );

                    g_readyStash.slabs[ g_readyStash.nInStash ] = pSlab;
                    g_readyStash.nInStash++;

                    rMutex_unlock( g_stashMutex );

                    pSlab = NULL;

                    // By calling reset, it means we can re-use the string but whatever memory
                    // is already allocated gets re-used which is nice for performance.
                    rpal_stringbuffer_reset( payload );
                }

                if( rEvent_wait( isTimeToStop, 0 ) )
                {
                    break;
                }
            }

            rpal_stringbuffer_free( payload );
            payload = NULL;
        }
        else
        {
            rpal_debug_critical( "could not allocate payload stringbuffer, exiting." );
        }

        restOutput_freeContext( restCtx );
    }
    else
    {
        rpal_debug_critical( "could not create rest context" );
    }

    return 0;
}

RPRIVATE
RVOID
    collectFromKernel
    (
        rEvent isTimeToStop
    )
{
    Slab* pCurrentSlab = NULL;

    // Initialize the first Slab.
    if( NULL != ( pCurrentSlab = _newSlab() ) )
    {
        rpal_debug_info( "RP HCP Bulk Collector Running...\n" );
        while( !rEvent_wait( isTimeToStop, MSEC_FROM_SEC( 1 ) ) )
        {
            pCurrentSlab->bytesInSlab = sizeof( pCurrentSlab->data );

            if( kAcq_getNewDnsPackets( (KernelAcqDnsPacket*)pCurrentSlab->data, &pCurrentSlab->bytesInSlab ) )
            {
                if( 0 == pCurrentSlab->bytesInSlab )
                {
                    // If we got no data there is no need to publish this Slab for exfil.
                    continue;
                }

                // Send the slab over for exfil.
                rMutex_lock( g_stashMutex );

                g_exfilStash.slabs[ g_exfilStash.nInStash ] = pCurrentSlab;
                g_exfilStash.nInStash++;
                rEvent_set( g_exfilEvent );
                pCurrentSlab = NULL;

                rMutex_unlock( g_stashMutex );

                do
                {
                    rMutex_lock( g_stashMutex );

                    // Is there a free Slab ready for us to use?
                    if( 0 != g_readyStash.nInStash )
                    {
                        pCurrentSlab = g_readyStash.slabs[ g_readyStash.nInStash - 1 ];
                        g_readyStash.nInStash--;
                    }

                    // If there was no free Slabs, and we're below the maximum, we'll allocate
                    // a new one and add it to the circuit.
                    if( NULL == pCurrentSlab &&
                        BULK_COLLECTOR_MAX_SLABS_IN_MEM > g_nSlabsInMem )
                    {
                        rpal_debug_info( "need Slab but none are free, allocating." );
                        pCurrentSlab = _newSlab();
                    }

                    rMutex_unlock( g_stashMutex );

                    // If we couldn't get a Slab by this point, we'll keep aggressively 
                    // try to get one.
                } while( NULL == pCurrentSlab &&
                         !rEvent_wait( isTimeToStop, 100 ) );

                // By this point, if pCurrentSlab is NULL it means it's time to bail.
                if( NULL == pCurrentSlab )
                {
                    continue;
                }
            }
            else
            {
                rpal_debug_warning( "could not get dns packets from kernel, acq not present?" );
            }
        }

        rpal_memory_free( pCurrentSlab );
        pCurrentSlab = NULL;
    }
    else
    {
        rpal_debug_critical( "could not allocate first slab, exiting." );
    }
}


//=============================================================================
//  RP HCP Module Entry Points
//=============================================================================
RVOID
    RpHcpI_receiveMessage
    (
        rSequence message
    )
{
    UNREFERENCED_PARAMETER( message );
    // We do not intend of really receiving any tasking at the moment.
}

RU32
RPAL_THREAD_FUNC
    RpHcpI_mainThread
    (
        rEvent isTimeToStop
    )
{
    RU32 ret = (RU32)(-1);

    RU32 i = 0;
    rThread hExfilThread = NULL;

    FORCE_LINK_THAT(HCP_IFACE);
    
    if( CryptoLib_init() )
    {
        if( NULL != ( g_stashMutex = rMutex_create() ) )
        {
            if( NULL != ( g_exfilEvent = rEvent_create( TRUE ) ) )
            {
                if( kAcq_init() )
                {
                    // Start the thread that will do the exfil.
                    if( NULL != ( hExfilThread = rpal_thread_new( exfilThread, isTimeToStop ) ) )
                    {
                        ret = 0;

                        // We start collecting from the kernel within this current thread.
                        collectFromKernel( isTimeToStop );

                        // We'll give X seconds to the exfil thread before exiting.
                        rpal_thread_wait( hExfilThread, MSEC_FROM_SEC( 30 ) );
                    }
                    else
                    {
                        rpal_debug_error( "could not create exfil thread, exiting." );
                    }

                    kAcq_deinit();
                }
                else
                {
                    rpal_debug_critical( "could not initialize kernel acquisition lib, exiting." );
                }

                // Drain the stash, for now just free it all.
                rMutex_lock( g_stashMutex );

                for( i = 0; i < g_exfilStash.nInStash; i++ )
                {
                    if( NULL != g_exfilStash.slabs[ i ] )
                    {
                        rpal_memory_free( g_exfilStash.slabs[ i ] );
                        g_exfilStash.slabs[ i ] = NULL;
                    }
                }

                for( i = 0; i < g_readyStash.nInStash; i++ )
                {
                    if( NULL != g_readyStash.slabs[ i ] )
                    {
                        rpal_memory_free( g_readyStash.slabs[ i ] );
                        g_readyStash.slabs[ i ] = NULL;
                    }
                }

                g_nSlabsInMem = 0;
                rEvent_unset( g_exfilEvent );

                rMutex_unlock( g_stashMutex );

                rEvent_free( g_exfilEvent );
                g_exfilEvent = NULL;
            }
            else
            {
                rpal_debug_critical( "could not create exfil event, exiting." );
            }

            rMutex_free( g_stashMutex );
            g_stashMutex = NULL;
        }
        else
        {
            rpal_debug_critical( "could not create stash mutex, exiting." );
        }

        CryptoLib_deinit();
    }
    else
    {
        rpal_debug_critical( "could not initialize crypto lib." );
    }

    g_nSlabsInMem = 0;
    rpal_memory_zero( &g_exfilStash, sizeof( g_exfilStash ) );
    rpal_memory_zero( &g_readyStash, sizeof( g_readyStash ) );

    return ret;
}

