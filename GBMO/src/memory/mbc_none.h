#pragma once

#include "memory/mbc.h"

/// Memory Bank Controller
class MBC_None : public MBC
{
public:
    MBC_None( u8* cartridge_rom, u8* cartridge_ram ) : MBC( cartridge_rom, cartridge_ram ) {}

    virtual u8 read( u16 address ) override;
    virtual void write( u16 address, u8 data ) override;
};
