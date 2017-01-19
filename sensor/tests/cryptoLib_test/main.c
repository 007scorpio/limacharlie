#include <rpal/rpal.h>
#include <cryptoLib/cryptoLib.h>
#include <Basic.h>

#define RPAL_FILE_ID     91

RU8 g_test_priv[ CRYPTOLIB_ASYM_KEY_SIZE_PRI ] = {
    0x30, 0x82, 0x04, 0xa4, 0x02, 0x01, 0x00, 0x02, 0x82, 0x01, 0x01, 0x00, 0xcb, 0x1f, 0x6d, 0x39,
    0x9a, 0xef, 0x58, 0x4d, 0xab, 0x6d, 0xee, 0x30, 0xde, 0xe1, 0x79, 0x79, 0x13, 0xaa, 0x04, 0xd9,
    0x92, 0x22, 0x99, 0xe9, 0xb4, 0x7e, 0x9f, 0x48, 0xa5, 0xb5, 0x76, 0x8b, 0x88, 0xb9, 0x87, 0x46,
    0xdf, 0xa0, 0xd1, 0xec, 0xab, 0x0a, 0x25, 0xbd, 0x2b, 0x98, 0xb0, 0x8a, 0x29, 0xfc, 0x75, 0x9a,
    0x41, 0x31, 0xa0, 0x40, 0x8e, 0xa5, 0x28, 0xe4, 0x4c, 0x15, 0xf8, 0x27, 0x72, 0xd6, 0xb9, 0x29,
    0x4d, 0xa1, 0xf5, 0xa3, 0xf0, 0xb6, 0x99, 0x81, 0xb8, 0x95, 0x09, 0x7d, 0xb3, 0x36, 0x47, 0xfd,
    0xde, 0x6b, 0x37, 0xc3, 0x25, 0x42, 0x9e, 0xf7, 0x8e, 0x89, 0x1f, 0xa1, 0x4b, 0x5c, 0x0e, 0x5a,
    0x19, 0x85, 0x9f, 0xe5, 0x48, 0xd8, 0xc3, 0xd1, 0x5c, 0x36, 0xe8, 0x89, 0xa3, 0x4a, 0xe4, 0xcb,
    0xaf, 0x55, 0xcb, 0xc0, 0x61, 0x95, 0x4c, 0x4c, 0xaa, 0xb9, 0xe9, 0x51, 0xb0, 0x48, 0x34, 0x63,
    0xf8, 0x9d, 0x4f, 0x60, 0xb6, 0x59, 0xa4, 0xa5, 0x30, 0x14, 0x2a, 0x3b, 0x17, 0xe9, 0x5d, 0xec,
    0x47, 0x2b, 0x1c, 0x51, 0x0c, 0x73, 0x94, 0xf5, 0xe7, 0x9f, 0xeb, 0xaf, 0xd1, 0x88, 0x1f, 0x7a,
    0xd6, 0x32, 0x10, 0x98, 0x88, 0xae, 0x96, 0x84, 0xe1, 0x28, 0xfd, 0x55, 0xe3, 0x67, 0xfe, 0x3f,
    0x81, 0xf7, 0xf4, 0x0f, 0x3a, 0x06, 0x17, 0x21, 0xae, 0x24, 0x2f, 0x51, 0x08, 0xe2, 0x0f, 0x12,
    0x6d, 0x82, 0xbe, 0xa9, 0xd5, 0x34, 0xa9, 0xba, 0x39, 0x43, 0xfb, 0xee, 0x35, 0xf4, 0xdb, 0x2b,
    0x48, 0xa2, 0x55, 0xa7, 0x13, 0xfb, 0xc8, 0x3c, 0xfa, 0xa3, 0x6b, 0x11, 0x92, 0x38, 0x54, 0x89,
    0xac, 0xfa, 0x13, 0x76, 0x7d, 0x52, 0x19, 0xa5, 0xc0, 0x7b, 0x20, 0x17, 0x59, 0x2c, 0x75, 0xcb,
    0xd7, 0x57, 0xdf, 0x51, 0xe5, 0x23, 0xcd, 0xa0, 0x89, 0x40, 0xef, 0x8f, 0x02, 0x03, 0x01, 0x00,
    0x01, 0x02, 0x82, 0x01, 0x01, 0x00, 0x86, 0x76, 0x6f, 0x5f, 0xca, 0xe8, 0xd6, 0x93, 0xd4, 0x00,
    0x19, 0xc5, 0xd0, 0x45, 0x82, 0x9c, 0x5c, 0x20, 0x18, 0xc5, 0xce, 0xaf, 0x89, 0x23, 0xe4, 0x90,
    0x4d, 0xf1, 0x51, 0x81, 0x26, 0xd0, 0x87, 0xda, 0x09, 0x6b, 0x29, 0x6e, 0xd4, 0x88, 0xcf, 0x51,
    0x10, 0x5a, 0x82, 0x19, 0xba, 0x04, 0x3c, 0x77, 0x1b, 0x82, 0xd9, 0xd5, 0x78, 0x38, 0x44, 0x35,
    0xa1, 0x34, 0x40, 0x09, 0xeb, 0x14, 0x72, 0x39, 0x22, 0xa9, 0xec, 0xf2, 0x62, 0x21, 0xfc, 0x9f,
    0x64, 0x4f, 0x33, 0x59, 0xb5, 0xc6, 0xb8, 0x74, 0x1e, 0x84, 0x38, 0x50, 0xd1, 0xc1, 0x25, 0x51,
    0x4c, 0xda, 0xa4, 0x48, 0xb1, 0xdf, 0x9c, 0x7b, 0x7c, 0x24, 0xb8, 0xf0, 0x74, 0x40, 0xdc, 0x50,
    0x62, 0x90, 0x9d, 0x72, 0xdb, 0xcd, 0x01, 0x83, 0xfa, 0xa1, 0xbb, 0x98, 0x18, 0x21, 0x6a, 0x77,
    0xe2, 0xe2, 0x7d, 0xc2, 0x44, 0x68, 0xd8, 0x51, 0x42, 0xb4, 0x65, 0x1e, 0x86, 0x5c, 0x78, 0xb7,
    0x87, 0xdd, 0xe5, 0x2d, 0x9f, 0xae, 0xc6, 0x1e, 0x86, 0x57, 0x66, 0x2c, 0x7f, 0x03, 0x80, 0x84,
    0x03, 0x1b, 0xf8, 0xdc, 0x98, 0x3f, 0x18, 0xcb, 0x77, 0xab, 0x2f, 0x23, 0x82, 0x9a, 0xbb, 0x36,
    0x75, 0xb8, 0xd6, 0xb5, 0x33, 0x54, 0xe3, 0x1a, 0xc1, 0x4d, 0x48, 0x6a, 0x36, 0xcc, 0x05, 0x6a,
    0x49, 0xaa, 0x0a, 0x6d, 0xdc, 0x58, 0x65, 0xbc, 0x13, 0x5b, 0xd9, 0x49, 0x17, 0xee, 0x02, 0x26,
    0x2b, 0x97, 0xa9, 0xda, 0xc4, 0xf7, 0x7f, 0x37, 0xa5, 0x6a, 0xf5, 0x76, 0x11, 0xaa, 0x70, 0xd5,
    0x0e, 0xb4, 0x61, 0x86, 0x2e, 0x00, 0x84, 0x4b, 0x11, 0xeb, 0x76, 0x82, 0xa4, 0x66, 0x20, 0x42,
    0x0c, 0xe0, 0x2f, 0xd5, 0xf9, 0x3c, 0x25, 0x43, 0xc1, 0xea, 0x69, 0xb4, 0x68, 0xc2, 0x23, 0x19,
    0x82, 0xa3, 0xdf, 0xd7, 0xc6, 0x81, 0x02, 0x81, 0x81, 0x00, 0xf7, 0xa3, 0x05, 0xb6, 0xa1, 0xf5,
    0x15, 0x11, 0x5c, 0x8e, 0xcd, 0xce, 0x1f, 0xa7, 0x77, 0x1c, 0xb5, 0x15, 0x20, 0xc0, 0x77, 0xe3,
    0x20, 0x68, 0xb4, 0xd4, 0xcf, 0x09, 0x28, 0x2c, 0x45, 0x12, 0x86, 0x97, 0x17, 0x03, 0xf9, 0xe1,
    0xa5, 0x9b, 0xef, 0xad, 0xb8, 0xc5, 0xbf, 0xef, 0x2f, 0x59, 0x71, 0x96, 0x8b, 0x4c, 0xa3, 0x99,
    0xce, 0xab, 0x04, 0x1d, 0xe2, 0x97, 0x63, 0x20, 0xed, 0x69, 0x0c, 0xd0, 0xb9, 0xdc, 0xe5, 0x2e,
    0x21, 0xe6, 0x39, 0x1c, 0xfa, 0xf8, 0x11, 0xfb, 0x9c, 0xf2, 0x25, 0x34, 0x4a, 0x2c, 0xde, 0x72,
    0xe7, 0xb1, 0x71, 0x7e, 0x22, 0x74, 0xc3, 0x88, 0xeb, 0x9e, 0xaf, 0x09, 0x8c, 0xa6, 0xaf, 0xe5,
    0xef, 0x1a, 0xe1, 0xfc, 0x1f, 0x49, 0x23, 0xc1, 0x86, 0x26, 0x2b, 0x25, 0xfc, 0xe5, 0xbe, 0x83,
    0xd8, 0xd6, 0x90, 0x33, 0xb8, 0x5b, 0xbe, 0xe4, 0x07, 0x49, 0x02, 0x81, 0x81, 0x00, 0xd1, 0xfb,
    0x8d, 0x56, 0xf3, 0xb2, 0x06, 0xb2, 0x1c, 0xa2, 0xf2, 0x48, 0x3c, 0x36, 0x19, 0xb8, 0x26, 0x6b,
    0xbe, 0xb7, 0xb3, 0xe0, 0xe6, 0xe6, 0x99, 0x31, 0x53, 0xd3, 0xc0, 0x94, 0xd4, 0x92, 0x55, 0xb0,
    0x7f, 0xcf, 0x55, 0x13, 0x5e, 0xad, 0x1d, 0x75, 0x15, 0x2b, 0xc5, 0xcc, 0x76, 0x74, 0x07, 0x0a,
    0x1e, 0x2a, 0x77, 0xb2, 0x69, 0xfe, 0x20, 0x27, 0xa7, 0xef, 0x26, 0x19, 0x12, 0xf2, 0x37, 0x55,
    0x1d, 0x5d, 0x4c, 0xd2, 0x44, 0xba, 0xc5, 0x17, 0x15, 0x11, 0x3d, 0x38, 0x23, 0x95, 0xee, 0xf5,
    0x20, 0x7c, 0x58, 0x25, 0x79, 0x61, 0x64, 0x5e, 0xc7, 0x01, 0xc2, 0x28, 0x85, 0x5b, 0x75, 0xa4,
    0x92, 0x38, 0xc2, 0x8d, 0xd2, 0xa3, 0x9d, 0xbe, 0x09, 0xa4, 0xb7, 0x37, 0xf7, 0x65, 0xee, 0x0f,
    0xae, 0xad, 0x79, 0xa7, 0xc7, 0x47, 0xf2, 0xd2, 0x4f, 0x28, 0xbc, 0x3a, 0x08, 0x17, 0x02, 0x81,
    0x80, 0x20, 0x2c, 0xb3, 0x3a, 0x56, 0x72, 0xa4, 0x69, 0x1c, 0x10, 0x85, 0xd6, 0xe9, 0x2f, 0xf5,
    0xfe, 0xe9, 0xdc, 0x33, 0xe4, 0x2d, 0xef, 0x79, 0xaf, 0x81, 0x07, 0x41, 0x5b, 0x1c, 0x38, 0x1c,
    0x45, 0x5a, 0xed, 0x58, 0x95, 0x30, 0xab, 0x4b, 0xbc, 0x25, 0xf8, 0xf9, 0x4f, 0xe0, 0x2f, 0x30,
    0x84, 0xbb, 0x88, 0x66, 0xd2, 0xef, 0x52, 0xb5, 0x92, 0x6c, 0xb7, 0x81, 0x50, 0x50, 0x15, 0xe0,
    0x22, 0xcd, 0x02, 0x75, 0x93, 0xa8, 0xc7, 0x44, 0xaa, 0x47, 0xf3, 0x66, 0xfc, 0x42, 0x41, 0xe1,
    0xd3, 0x68, 0x58, 0x11, 0xe7, 0x20, 0x83, 0xe7, 0x6c, 0x9b, 0xa5, 0x5a, 0xce, 0xb6, 0xf5, 0x1c,
    0x40, 0x02, 0xd8, 0x07, 0xc9, 0x44, 0x83, 0x68, 0x7c, 0xa2, 0xae, 0x02, 0x56, 0x9b, 0x69, 0xb2,
    0x87, 0x55, 0x05, 0xdb, 0x84, 0xf2, 0x2a, 0xe9, 0x4a, 0x7f, 0x73, 0xe8, 0xd9, 0x2a, 0xc5, 0x2f,
    0xd9, 0x02, 0x81, 0x80, 0x56, 0xf5, 0xeb, 0x79, 0xd8, 0x20, 0xa1, 0x1f, 0x40, 0x36, 0xc7, 0x49,
    0xdd, 0x0d, 0xb6, 0xa7, 0x09, 0xda, 0x53, 0x38, 0x76, 0xd9, 0x2c, 0x26, 0xd1, 0xc8, 0x98, 0xe3,
    0xb7, 0xfc, 0xaa, 0xf0, 0x13, 0x66, 0xad, 0xf7, 0xaa, 0x4f, 0x04, 0x45, 0x83, 0x4e, 0x8a, 0xbe,
    0xff, 0x02, 0x87, 0x07, 0xd4, 0x26, 0x7f, 0x89, 0xac, 0xda, 0x89, 0x84, 0xc1, 0xc2, 0x4a, 0x8d,
    0x02, 0xe5, 0x1d, 0x70, 0x8c, 0x33, 0xc6, 0x9e, 0x6e, 0x03, 0x22, 0x8d, 0x8a, 0xb3, 0xdd, 0x78,
    0xaf, 0x36, 0xc1, 0x9e, 0x05, 0x41, 0x24, 0xfb, 0xf9, 0xf1, 0x43, 0x0c, 0x6f, 0x69, 0xc4, 0xd6,
    0xd8, 0x96, 0xb9, 0x6b, 0xc0, 0x13, 0xb0, 0xae, 0xaa, 0xfb, 0xdb, 0x01, 0x01, 0x81, 0xc3, 0x32,
    0xa0, 0xe2, 0x1f, 0xa5, 0xe9, 0xea, 0x3a, 0xb8, 0x03, 0x0a, 0xd5, 0xbf, 0xd9, 0x32, 0xf9, 0xaf,
    0x70, 0x0c, 0x44, 0x6f, 0x02, 0x81, 0x81, 0x00, 0xbd, 0x91, 0xd7, 0x9d, 0x9c, 0x7c, 0x7b, 0xed,
    0x4f, 0x7d, 0x5c, 0xa8, 0x72, 0x5a, 0xe0, 0x72, 0x73, 0xfe, 0x93, 0x5b, 0x13, 0x03, 0x25, 0x3d,
    0x1f, 0xeb, 0xf2, 0x04, 0xdb, 0x95, 0x85, 0x51, 0x2d, 0xdd, 0x5a, 0xe8, 0xc0, 0x47, 0xd2, 0xcb,
    0x15, 0xc9, 0x49, 0x3a, 0x7f, 0x33, 0x9a, 0x2e, 0xa2, 0xd8, 0x68, 0x8a, 0xcf, 0x10, 0x89, 0xe7,
    0xd7, 0xb2, 0x24, 0xff, 0x71, 0xdf, 0xc5, 0xd3, 0x2a, 0x5b, 0xed, 0x34, 0x15, 0xb4, 0x26, 0x9e,
    0xf6, 0x03, 0x67, 0x8e, 0x3f, 0x1f, 0x44, 0x20, 0x80, 0x87, 0xf2, 0x6e, 0x63, 0xd6, 0xe5, 0x6a,
    0x30, 0x99, 0xad, 0xc9, 0x81, 0x3c, 0x26, 0x04, 0x79, 0x72, 0x8a, 0xf9, 0xaa, 0xd3, 0x43, 0x1b,
    0x44, 0x95, 0xc7, 0x66, 0x19, 0x98, 0x1d, 0x9e, 0x33, 0x22, 0xe8, 0xfe, 0xa6, 0x9e, 0xad, 0x12,
    0x5a, 0x9f, 0x6a, 0xc5, 0x49, 0xbf, 0x68, 0x26 };
RU8 g_test_pub[ CRYPTOLIB_ASYM_KEY_SIZE_PUB ] = {
    0x30, 0x82, 0x01, 0x22, 0x30, 0x0d, 0x06, 0x09, 0x2a, 0x86, 0x48, 0x86,
    0xf7, 0x0d, 0x01, 0x01, 0x01, 0x05, 0x00, 0x03, 0x82, 0x01, 0x0f, 0x00,
    0x30, 0x82, 0x01, 0x0a, 0x02, 0x82, 0x01, 0x01, 0x00, 0xcb, 0x1f, 0x6d,
    0x39, 0x9a, 0xef, 0x58, 0x4d, 0xab, 0x6d, 0xee, 0x30, 0xde, 0xe1, 0x79,
    0x79, 0x13, 0xaa, 0x04, 0xd9, 0x92, 0x22, 0x99, 0xe9, 0xb4, 0x7e, 0x9f,
    0x48, 0xa5, 0xb5, 0x76, 0x8b, 0x88, 0xb9, 0x87, 0x46, 0xdf, 0xa0, 0xd1,
    0xec, 0xab, 0x0a, 0x25, 0xbd, 0x2b, 0x98, 0xb0, 0x8a, 0x29, 0xfc, 0x75,
    0x9a, 0x41, 0x31, 0xa0, 0x40, 0x8e, 0xa5, 0x28, 0xe4, 0x4c, 0x15, 0xf8,
    0x27, 0x72, 0xd6, 0xb9, 0x29, 0x4d, 0xa1, 0xf5, 0xa3, 0xf0, 0xb6, 0x99,
    0x81, 0xb8, 0x95, 0x09, 0x7d, 0xb3, 0x36, 0x47, 0xfd, 0xde, 0x6b, 0x37,
    0xc3, 0x25, 0x42, 0x9e, 0xf7, 0x8e, 0x89, 0x1f, 0xa1, 0x4b, 0x5c, 0x0e,
    0x5a, 0x19, 0x85, 0x9f, 0xe5, 0x48, 0xd8, 0xc3, 0xd1, 0x5c, 0x36, 0xe8,
    0x89, 0xa3, 0x4a, 0xe4, 0xcb, 0xaf, 0x55, 0xcb, 0xc0, 0x61, 0x95, 0x4c,
    0x4c, 0xaa, 0xb9, 0xe9, 0x51, 0xb0, 0x48, 0x34, 0x63, 0xf8, 0x9d, 0x4f,
    0x60, 0xb6, 0x59, 0xa4, 0xa5, 0x30, 0x14, 0x2a, 0x3b, 0x17, 0xe9, 0x5d,
    0xec, 0x47, 0x2b, 0x1c, 0x51, 0x0c, 0x73, 0x94, 0xf5, 0xe7, 0x9f, 0xeb,
    0xaf, 0xd1, 0x88, 0x1f, 0x7a, 0xd6, 0x32, 0x10, 0x98, 0x88, 0xae, 0x96,
    0x84, 0xe1, 0x28, 0xfd, 0x55, 0xe3, 0x67, 0xfe, 0x3f, 0x81, 0xf7, 0xf4,
    0x0f, 0x3a, 0x06, 0x17, 0x21, 0xae, 0x24, 0x2f, 0x51, 0x08, 0xe2, 0x0f,
    0x12, 0x6d, 0x82, 0xbe, 0xa9, 0xd5, 0x34, 0xa9, 0xba, 0x39, 0x43, 0xfb,
    0xee, 0x35, 0xf4, 0xdb, 0x2b, 0x48, 0xa2, 0x55, 0xa7, 0x13, 0xfb, 0xc8,
    0x3c, 0xfa, 0xa3, 0x6b, 0x11, 0x92, 0x38, 0x54, 0x89, 0xac, 0xfa, 0x13,
    0x76, 0x7d, 0x52, 0x19, 0xa5, 0xc0, 0x7b, 0x20, 0x17, 0x59, 0x2c, 0x75,
    0xcb, 0xd7, 0x57, 0xdf, 0x51, 0xe5, 0x23, 0xcd, 0xa0, 0x89, 0x40, 0xef,
    0x8f, 0x02, 0x03, 0x01, 0x00, 0x01
};

void test_memoryLeaks(void)
{
    RU32 memUsed = 0;

    rpal_Context_cleanup();

    memUsed = rpal_memory_totalUsed();

    CU_ASSERT_EQUAL( memUsed, 0 );

    if( 0 != memUsed )
    {
        rpal_debug_critical( "Memory leak: %d bytes.\n", memUsed );
        printf( "\nMemory leak: %d bytes.\n", memUsed );

        rpal_memory_findMemory();
    }
}

void test_init( void )
{
    CU_ASSERT_TRUE( CryptoLib_init() );
}

void test_deinit( void )
{
    CryptoLib_deinit();
}

void test_hashing( void )
{
    CryptoLib_Hash hash = { 0 };
    RPCHAR test_str_1 = "thisisatest";
    RU8 test_hash_1[ CRYPTOLIB_HASH_SIZE ] = { 0xa7, 0xc9, 0x62, 0x62, 0xc2, 0x1d, 0xb9, 0xa0, 
                                               0x6f, 0xd4, 0x9e, 0x30, 0x7d, 0x69, 0x4f, 0xd9, 
                                               0x5f, 0x62, 0x45, 0x69, 0xf9, 0xb3, 0x5b, 0xb3, 
                                               0xff, 0xac, 0xd8, 0x80, 0x44, 0x0f, 0x97, 0x87 };

    CU_ASSERT_TRUE( CryptoLib_hash( test_str_1, rpal_string_strlenA( test_str_1 ), &hash ) );
    CU_ASSERT_EQUAL( rpal_memory_memcmp( &hash, test_hash_1, sizeof( hash ) ), 0 );

    CU_ASSERT_FALSE( CryptoLib_hash( 0, sizeof( test_str_1 ), &hash ) );
    CU_ASSERT_FALSE( CryptoLib_hash( test_str_1, 0, &hash ) );
    CU_ASSERT_FALSE( CryptoLib_hash( test_str_1, sizeof( test_str_1 ), NULL ) );
}

void test_file_hashing( void )
{
    CryptoLib_Hash hash = { 0 };
    RPNCHAR testFileName = _NC( "__test_file" );
    RPCHAR test_str_1 = "thisisatest";
    RU8 test_hash_1[ CRYPTOLIB_HASH_SIZE ] = { 0xa7, 0xc9, 0x62, 0x62, 0xc2, 0x1d, 0xb9, 0xa0,
        0x6f, 0xd4, 0x9e, 0x30, 0x7d, 0x69, 0x4f, 0xd9,
        0x5f, 0x62, 0x45, 0x69, 0xf9, 0xb3, 0x5b, 0xb3,
        0xff, 0xac, 0xd8, 0x80, 0x44, 0x0f, 0x97, 0x87 };

    CU_ASSERT_TRUE_FATAL( rpal_file_write( testFileName, test_str_1, rpal_string_strlenA( test_str_1 ), TRUE ) );

    CU_ASSERT_TRUE( CryptoLib_hashFile( testFileName, &hash, FALSE ) );
    CU_ASSERT_EQUAL( rpal_memory_memcmp( &hash, test_hash_1, sizeof( hash ) ), 0 );

    rpal_file_delete( testFileName, FALSE );

    CU_ASSERT_FALSE( CryptoLib_hashFile( NULL, &hash, FALSE ) );
    CU_ASSERT_FALSE( CryptoLib_hashFile( testFileName, NULL, FALSE ) );
}

void test_random_bytes( void )
{
    RU8 test_buff[ 63 ] = { 0 };
    RU8 test_ref[ 63 ] = { 0 };

    CU_ASSERT_TRUE( CryptoLib_genRandomBytes( test_buff, sizeof( test_buff ) ) );
    CU_ASSERT_NOT_EQUAL( rpal_memory_memcmp( test_buff, test_ref, sizeof( test_buff ) ), 0 );

    CU_ASSERT_FALSE( CryptoLib_genRandomBytes( NULL, sizeof( test_buff ) ) );
    CU_ASSERT_FALSE( CryptoLib_genRandomBytes( test_buff, 0 ) );
}

void test_sym_encryption( void )
{
    RU8 test_key[ CRYPTOLIB_SYM_KEY_SIZE ] = { 0 };
    RU8 test_iv[ CRYPTOLIB_SYM_IV_SIZE ] = { 0 };
    RU8 test_scratch_iv[ CRYPTOLIB_SYM_IV_SIZE ] = { 0 };
    RU8 test_buff[ 1000 ] = { 0 };
    rBlob test_blob = NULL;

    CryptoLib_SymContext ctx1 = NULL;
    CryptoLib_SymContext ctx2 = NULL;

    CU_ASSERT_TRUE_FATAL( CryptoLib_genRandomBytes( test_buff, sizeof( test_buff ) ) );
    CU_ASSERT_TRUE_FATAL( CryptoLib_genRandomBytes( test_key, sizeof( test_key ) ) );
    CU_ASSERT_TRUE_FATAL( CryptoLib_genRandomBytes( test_iv, sizeof( test_iv ) ) );

    test_blob = rpal_blob_create( 0, 0 );
    CU_ASSERT_NOT_EQUAL_FATAL( test_blob, NULL );
    CU_ASSERT_TRUE_FATAL( rpal_blob_add( test_blob, test_buff, sizeof( test_buff ) ) );

    rpal_memory_memcpy( test_scratch_iv, test_iv, sizeof( test_scratch_iv ) );
    CU_ASSERT_TRUE( CryptoLib_symEncrypt( test_blob, test_key, test_scratch_iv, NULL ) );
    if( sizeof( test_buff ) == rpal_blob_getSize( test_blob ) )
    {
        CU_ASSERT_NOT_EQUAL( rpal_memory_memcmp( rpal_blob_getBuffer( test_blob ), test_buff, sizeof( test_buff ) ), 0 );
    }
    rpal_memory_memcpy( test_scratch_iv, test_iv, sizeof( test_scratch_iv ) );
    CU_ASSERT_TRUE( CryptoLib_symDecrypt( test_blob, test_key, test_scratch_iv, NULL ) );
    CU_ASSERT_EQUAL( rpal_blob_getSize( test_blob ), sizeof( test_buff ) );
    CU_ASSERT_EQUAL( rpal_memory_memcmp( rpal_blob_getBuffer( test_blob ), test_buff, sizeof( test_buff ) ), 0 );

    rpal_blob_free( test_blob );
    test_blob = NULL;

    ctx1 = CryptoLib_symEncInitContext( test_key, test_iv );
    CU_ASSERT_NOT_EQUAL_FATAL( ctx1, NULL );
    ctx2 = CryptoLib_symDecInitContext( test_key, test_iv );
    CU_ASSERT_NOT_EQUAL_FATAL( ctx2, NULL );

    test_blob = rpal_blob_create( 0, 0 );
    CU_ASSERT_NOT_EQUAL_FATAL( test_blob, NULL );
    CU_ASSERT_TRUE_FATAL( rpal_blob_add( test_blob, test_buff, sizeof( test_buff ) ) );

    CU_ASSERT_TRUE( CryptoLib_symEncrypt( test_blob, NULL, NULL, ctx1) );
    if( sizeof( test_buff ) == rpal_blob_getSize( test_blob ) )
    {
        CU_ASSERT_NOT_EQUAL( rpal_memory_memcmp( rpal_blob_getBuffer( test_blob ), test_buff, sizeof( test_buff ) ), 0 );
    }
    CU_ASSERT_TRUE( CryptoLib_symDecrypt( test_blob, NULL, NULL, ctx2 ) );
    CU_ASSERT_EQUAL( rpal_blob_getSize( test_blob ), sizeof( test_buff ) );
    CU_ASSERT_EQUAL( rpal_memory_memcmp( rpal_blob_getBuffer( test_blob ), test_buff, sizeof( test_buff ) ), 0 );

    rpal_blob_free( test_blob );

    CryptoLib_symFreeContext( ctx1 );
    CryptoLib_symFreeContext( ctx2 );
}

void test_sig( void )
{
    RU8 test_buff[ 800 ] = { 0 };
    RU8 test_sig[ CRYPTOLIB_SIGNATURE_SIZE ] = { 0 };
    RU8 test_ref[ CRYPTOLIB_SIGNATURE_SIZE ] = { 0 };
    
    CryptoLib_genRandomBytes( test_buff, sizeof( test_buff ) );

    CU_ASSERT_TRUE( CryptoLib_sign( test_buff, sizeof( test_buff ), g_test_priv, test_sig ) );

    CU_ASSERT_NOT_EQUAL( rpal_memory_memcmp( test_sig, test_ref, sizeof( test_sig ) ), 0 );

    CU_ASSERT_TRUE( CryptoLib_verify( test_buff, sizeof( test_buff ), g_test_pub, test_sig ) );

    CU_ASSERT_FALSE( CryptoLib_sign( NULL, sizeof( test_buff ), g_test_priv, test_sig ) );
    CU_ASSERT_FALSE( CryptoLib_sign( test_buff, 0, g_test_priv, test_sig ) );
    CU_ASSERT_FALSE( CryptoLib_sign( test_buff, sizeof( test_buff ), NULL, test_sig ) );
    CU_ASSERT_FALSE( CryptoLib_sign( test_buff, sizeof( test_buff ), g_test_priv, NULL ) );

    CU_ASSERT_FALSE( CryptoLib_verify( NULL, sizeof( test_buff ), g_test_pub, test_sig ) );
    CU_ASSERT_FALSE( CryptoLib_verify( test_buff, 0, g_test_pub, test_sig ) );
    CU_ASSERT_FALSE( CryptoLib_verify( test_buff, sizeof( test_buff ), NULL, test_sig ) );
    CU_ASSERT_FALSE( CryptoLib_verify( test_buff, sizeof( test_buff ), g_test_pub, NULL ) );
}

void test_asym( void )
{
    RU8 test_buff[ CRYPTOLIB_ASYM_MAX_SIZE ] = { 0 };
    RU8* pEncrypted = NULL;
    RU8* pDecrypted = NULL;
    RU32 encSize = 0;
    RU32 decSize = 0;

    CryptoLib_genRandomBytes( test_buff, sizeof( test_buff ) );

    CU_ASSERT_TRUE( CryptoLib_asymEncrypt( test_buff, sizeof( test_buff ), g_test_pub, &pEncrypted, &encSize ) );
    CU_ASSERT_TRUE( sizeof( test_buff ) <= encSize );
    CU_ASSERT_NOT_EQUAL_FATAL( pEncrypted, NULL );

    CU_ASSERT_TRUE( CryptoLib_asymDecrypt( pEncrypted, encSize, g_test_priv, &pDecrypted, &decSize ) );
    CU_ASSERT_EQUAL( decSize, sizeof( test_buff ) );
    CU_ASSERT_NOT_EQUAL_FATAL( pDecrypted, NULL );
    CU_ASSERT_EQUAL( rpal_memory_memcmp( test_buff, pDecrypted, decSize ), 0 );

    CU_ASSERT_FALSE( CryptoLib_asymEncrypt( NULL, sizeof( test_buff ), g_test_pub, &pEncrypted, &encSize ) );
    CU_ASSERT_FALSE( CryptoLib_asymEncrypt( test_buff, 0, g_test_pub, &pEncrypted, &encSize ) );
    CU_ASSERT_FALSE( CryptoLib_asymEncrypt( test_buff, sizeof( test_buff ), NULL, &pEncrypted, &encSize ) );
    CU_ASSERT_FALSE( CryptoLib_asymEncrypt( test_buff, sizeof( test_buff ), g_test_pub, NULL, &encSize ) );
    CU_ASSERT_FALSE( CryptoLib_asymEncrypt( test_buff, sizeof( test_buff ), g_test_pub, &pEncrypted, NULL ) );
    CU_ASSERT_FALSE( CryptoLib_asymEncrypt( test_buff, 8096, g_test_pub, &pEncrypted, &encSize ) );

    CU_ASSERT_FALSE( CryptoLib_asymDecrypt( NULL, encSize, g_test_priv, &pDecrypted, &decSize ) );
    CU_ASSERT_FALSE( CryptoLib_asymDecrypt( pEncrypted, 0, g_test_priv, &pDecrypted, &decSize ) );
    CU_ASSERT_FALSE( CryptoLib_asymDecrypt( pEncrypted, encSize, NULL, &pDecrypted, &decSize ) );
    CU_ASSERT_FALSE( CryptoLib_asymDecrypt( pEncrypted, encSize, g_test_priv, NULL, &decSize ) );
    CU_ASSERT_FALSE( CryptoLib_asymDecrypt( pEncrypted, encSize, g_test_priv, &pDecrypted, NULL ) );

    rpal_memory_free( pEncrypted );
    rpal_memory_free( pDecrypted );
}

void test_fast_asym( void )
{
    RU8 test_buff[ 8000 ] = { 0 };
    rBlob test_blob = NULL;

    CryptoLib_genRandomBytes( test_buff, sizeof( test_buff ) );

    test_blob = rpal_blob_create( 0, 0 );
    CU_ASSERT_NOT_EQUAL_FATAL( test_blob, NULL );

    CU_ASSERT_TRUE_FATAL( rpal_blob_add( test_blob, test_buff, sizeof( test_buff ) ) );

    CU_ASSERT_TRUE( CryptoLib_fastAsymEncrypt( test_blob, g_test_pub ) );
    CU_ASSERT_TRUE( sizeof( test_buff ) < rpal_blob_getSize( test_blob ) );

    CU_ASSERT_TRUE( CryptoLib_fastAsymDecrypt( test_blob, g_test_priv ) );
    CU_ASSERT_TRUE( sizeof( test_buff ) == rpal_blob_getSize( test_blob ) );
    CU_ASSERT_EQUAL( rpal_memory_memcmp( test_buff, rpal_blob_getBuffer( test_blob ), sizeof( test_buff ) ), 0 );

    CU_ASSERT_FALSE( CryptoLib_fastAsymEncrypt( NULL, g_test_pub ) );
    CU_ASSERT_FALSE( CryptoLib_fastAsymEncrypt( test_blob, NULL ) );

    CU_ASSERT_FALSE( CryptoLib_fastAsymDecrypt( NULL, g_test_priv ) );
    CU_ASSERT_FALSE( CryptoLib_fastAsymDecrypt( test_blob, NULL ) );

    rpal_blob_free( test_blob );
}

int
    main
    (
        int argc,
        char* argv[]
    )
{
    int ret = 1;

    CU_pSuite suite = NULL;

    UNREFERENCED_PARAMETER( argc );
    UNREFERENCED_PARAMETER( argv );

    rpal_initialize( NULL, 1 );

    CU_initialize_registry();

    if( NULL != ( suite = CU_add_suite( "cryptoLib", NULL, NULL ) ) )
    {
        if( NULL == CU_add_test( suite, "initialize", test_init ) || 
            NULL == CU_add_test( suite, "hashing", test_hashing ) ||
            NULL == CU_add_test( suite, "file_hashing", test_file_hashing ) ||
            NULL == CU_add_test( suite, "random", test_random_bytes ) ||
            NULL == CU_add_test( suite, "sym_crypt", test_sym_encryption ) ||
            NULL == CU_add_test( suite, "signature", test_sig ) ||
            NULL == CU_add_test( suite, "asym_crypt", test_asym ) ||
            NULL == CU_add_test( suite, "fast_asym", test_fast_asym ) ||
            NULL == CU_add_test( suite, "deinitialize", test_deinit ) ||
            NULL == CU_add_test( suite, "memoryLeaks", test_memoryLeaks ) )
        {
            ret = 0;
        }
    }

    CU_basic_run_tests();

    CU_cleanup_registry();

    rpal_Context_deinitialize();

    return ret;
}

