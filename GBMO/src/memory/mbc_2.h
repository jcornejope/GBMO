#pragma once

#include "memory/mbc.h"

class MBC_2 : public MBC
{
    enum { WRITE_RAM_ROM_BIT = 0x0100 };

public:
    MBC_2( u8* cartridge_rom, u8* cartridge_ram, u32 rom_size, u32 ram_size );

    virtual u8 read( u16 address ) override;
    virtual void write( u16 address, u8 data ) override;

private:
//    u16 _get_ram_mapped_address( u16 const address ) const;

    u8 m_rom_bank;
    bool m_ramcs;
};

