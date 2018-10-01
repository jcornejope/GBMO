#pragma once

#include "utils/types.h"

/// Memory Bank Controller
class MBC
{
public:
    MBC( u8* cartridge_rom, u8* cartridge_ram, u32 rom_size, u32 ram_size ) 
        : m_cartridge_rom( cartridge_rom )
        , m_cartridge_ram( cartridge_ram )
        , m_rom_size( rom_size )
        , m_ram_size( ram_size ) 
    {}

    MBC( u8* cartridge_rom, u8* cartridge_ram ) 
        : m_cartridge_rom( cartridge_rom )
        , m_cartridge_ram( cartridge_ram )
        , m_rom_size( 0x8000 )
        , m_ram_size( 0 )
    {}

    virtual ~MBC() {}

    virtual u8 read( u16 address ) = 0;
    virtual void write( u16 address, u8 data ) = 0;

protected:
    static u16 const MEMORY_BANK_SIZE = 0x4000;

    u8* m_cartridge_rom;
    u8* m_cartridge_ram;

    u32 m_rom_size;
    u32 m_ram_size;
};
