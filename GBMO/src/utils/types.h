#pragma once

#pragma warning( disable : 4201 ) // annonnymous struct/union

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef char s8;
typedef short s16;
typedef int s32;

typedef union
{
    u16 data;

    struct
    {
#ifdef HIGH_ENDIAN
        u8 hi;
        u8 lo;
#else
        u8 lo;
        u8 hi;
#endif
    };
} word;
