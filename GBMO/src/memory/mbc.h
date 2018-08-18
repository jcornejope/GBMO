#pragma once

#include "utils/types.h"

/// Memory Bank Controller
class MBC
{
public:
    MBC( u8* cartridge_rom, u8* cartridge_ram ) : m_cartridge_rom( cartridge_rom ), m_cartridge_ram( cartridge_ram ) {}
    virtual ~MBC() {}

    virtual u8 read( u16 address ) = 0;
    virtual void write( u16 address, u8 data ) = 0;

protected:
    u8* m_cartridge_rom;
    u8* m_cartridge_ram;
};
