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

enum ADDRESSES : u16
{
    IO_ADDRESS_START = 0xFF00,

    P1_JOYP_ADDR = 0xFF00,

    DIV_ADDR  = 0xFF04,
    TIMA_ADDR = 0xFF05,
    TMA_ADDR  = 0xFF06,
    TAC_ADDR  = 0xFF07,

    IF_ADDR = 0xFF0F,
    IE_ADDR = 0xFFFF,
};

enum Interrupts : u8
{
    V_BLANK     = 0,
    LCD_STAT    = 1,
    TIMER       = 1 << 1,
    SERIAL      = 1 << 2,
    JOYPAD      = 1 << 3
};
