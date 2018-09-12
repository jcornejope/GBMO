
#include "memory/memory_system.h"

#include "cartridge/cartridge.h"
#include "gbmo.h"
#include "joypad/joypad.h"

#include <cstring>
#include <cassert>

MemorySystem::MemorySystem( GBMO& gameboy )
    : m_gameboy( gameboy )
{
    std::memset( &m_memory, 0, SYSTEM_MEMORY_SIZE );
}

u8 MemorySystem::read_8( u16 address )
{
    if( _is_memory_handled_by_cartridge( address ) )
    {
        return m_gameboy.get_cartridge()._read( address );
    }

    u16 mapped_address = _remap_address( address );
    assert( mapped_address < SYSTEM_MEMORY_SIZE );
    return m_memory[mapped_address];
}

u16 MemorySystem::read_16( u16 address )
{
    word value;

    value.lo = read_8( address );
    value.hi = read_8( address + 1 );

    return value.data;
}

void MemorySystem::write( u16 address, u8 data )
{
    if( _is_memory_handled_by_cartridge( address ) )
    {
        m_gameboy.get_cartridge()._write( address, data );
        return;
    }
    
    if( address >= 0xFEA0 && address <= 0xFEFF )
    {
        assert( false ); // THIS SHOULDN'T BE HAPPENING. THIS IS PROHIBITED!!
        return;
    }

    // TODO: ALL THE SPECIAL CASES (DIV, TIMERS, LCD REGS. ETC.)
    if( address == DIV_ADDR )
    {
        data = 0x00;
    }
    else if( address == P1_JOYP_ADDR )
    {
        // Remove the low part of data as it is read only.

        if( ( ( data & 0x30 ) ^ 0x30 ) != 0 )
        {
            u8 low_data = m_gameboy.get_joypad().get_inputs_for_memory( data );
            data = ( data & 0xF0 ) | low_data;
        }
        else
            data &= 0xF0;
    }

    u16 mapped_address = _remap_address( address );
    assert( mapped_address < SYSTEM_MEMORY_SIZE );
    m_memory[mapped_address] = data;
}

void MemorySystem::write( u16 address, u16 data )
{
    word value = { data };

    write( address, value.lo );
    write( address + 1, value.hi );
}

bool MemorySystem::_is_memory_handled_by_cartridge( u16 const address ) const
{
    return ( address < 0x8000 ) || ( address >= 0xA000 && address < 0xC000 );
}

u16 MemorySystem::_remap_address( u16 const address ) const
{
    u16 mapped_address = address - CARTRIDGE_ROM_MAP_SIZE;
    if( address >= 0xC000 )
        mapped_address -= CARTRIDGE_RAM_MAP_SIZE;
    if( address >= 0xE000 )
    {
        if( address <= 0xFDFF )
            mapped_address -= 0x2000;
        else
            mapped_address -= ECHO_RAM_SIZE;
    }

    return mapped_address;
}
