#pragma once

#pragma warning( disable : 4201 ) // annonnymous struct/union

#ifdef _MSC_VER
#define FORCE_INLINE __forceinline
#else
#define FORCE_INLINE inline
#endif

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
    OAM_START_ADDR      = 0xFE00,
    OAM_END_ADDR        = 0xFE9F,
    IO_ADDRESS_START    = 0xFF00,

    P1_JOYP_ADDR = 0xFF00,

    DIV_ADDR  = 0xFF04,
    TIMA_ADDR = 0xFF05,
    TMA_ADDR  = 0xFF06,
    TAC_ADDR  = 0xFF07,

    IF_ADDR = 0xFF0F,
    IE_ADDR = 0xFFFF,

    LCD_CONTROL_ADDR    = 0xFF40,
    LCDC_STAT_ADDR      = 0xFF41,
    SCROLL_Y_ADDR       = 0xFF42,
    SCROLL_X_ADDR       = 0xFF43,
    LCDC_Y_ADDR         = 0xFF44,
    LY_COMPARE_ADDR     = 0xFF45,
    DMA_TRANSFER_ADDR   = 0xFF46,
    BG_PALETTE_ADDR     = 0xFF47,
    OBJ_0_PALETTE_ADDR  = 0xFF48,
    OBJ_1_PALETTE_ADDR  = 0xFF49,
    WINDOW_Y_ADDR       = 0xFF4A,
    WINDOW_X_ADDR       = 0xFF4B,
};

enum Interrupts : u8
{
    V_BLANK     = 1,
    LCD_STAT    = 1 << 1,
    TIMER       = 1 << 2,
    SERIAL      = 1 << 3,
    JOYPAD      = 1 << 4
};
