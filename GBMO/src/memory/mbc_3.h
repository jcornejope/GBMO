#pragma once

#include "memory/mbc.h"

class MBC_3 : public MBC
{
    enum RAM_BANK_MAP : u8
    {
        RAM_BANK_0 = 0x00,
        RAM_BANK_1 = 0x01,
        RAM_BANK_2 = 0x02,
        RAM_BANK_3 = 0x03,

        RTC_S = 0x08,
        RTC_M = 0x09,
        RTC_H = 0x0A,
        RTC_DL = 0x0B,
        RTC_DH = 0x0C,
    };

    struct RTC
    {
        u8 m_s;
        u8 m_m;
        u8 m_h;
        u8 m_dl;
        u8 m_dh;
    };

public:
    MBC_3( u8* cartridge_rom, u8* cartridge_ram, u32 rom_size, u32 ram_size );

    virtual u8 read( u16 address ) override;
    virtual void write( u16 address, u8 data ) override;

private:
    u16 _get_ram_mapped_address( u16 const address ) const;

    u8 m_rom_bank;
    u8 m_ram_bank_n_rtc;

    RTC m_rtc;

    bool m_ramcs_n_clock_counter;
};
