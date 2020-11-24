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
    void read_oam_chunk( u16 address, u8* buffer, u16 size );

    void write( u16 address, u8 data );
    void write( u16 address, u16 data );

    void non_protected_write( u16 address, u8 data );

private:
    bool _is_memory_handled_by_cartridge( u16 const address ) const;

    static u16 _remap_address( u16 const address );
    u8 _get_read_mask( u16 address ) const;

    void _start_dma_transfer();

    u8 m_memory[SYSTEM_MEMORY_SIZE];
    GBMO& m_gameboy;
};
