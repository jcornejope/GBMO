#pragma once

#include "utils/types.h"

class GBMO;

class MemorySystem final
{
    static u16 const CARTRIDGE_ROM_MAP_SIZE = 0x8000;
    static u16 const CARTRIDGE_RAM_MAP_SIZE = 0xC000 - 0xA000;
    static u16 const ECHO_RAM_SIZE          = 0xFE00 - 0xE000;
    static u16 const SYSTEM_MEMORY_SIZE     = 0x10000 - CARTRIDGE_ROM_MAP_SIZE - CARTRIDGE_RAM_MAP_SIZE - ECHO_RAM_SIZE;

public:
    MemorySystem( GBMO& gameboy );

    u8  read_8( u16 address );
    u16 read_16( u16 address );

    void write( u16 address, u8 data );
    void write( u16 address, u16 data );

private:
    bool _is_memory_handled_by_cartridge( u16 const address ) const;
    u16 _remap_address( u16 const address ) const;

    u8 m_memory[SYSTEM_MEMORY_SIZE];
    GBMO& m_gameboy;
};
