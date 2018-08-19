
#include "memory/memory_system.h"
#include "cartridge/cartridge.h"

#include <cstring>
#include <cassert>

MemorySystem::MemorySystem( Cartridge& cartridge )
    : m_cartridge( cartridge )
{
    std::memset( &m_memory, 0, SYSTEM_MEMORY_SIZE );
}

u8 MemorySystem::read_8( u16 address )
{
    if( ( address < 0x8000 ) ||
        ( address >= 0xA000 && address < 0xC000 ) )
    {
        return m_cartridge._read( address );
    }
    
    u16 mapped_address = address - CARTRIDGE_ROM_MAP_SIZE;
    if( address >= 0xC000 )
        mapped_address -= CARTRIDGE_RAM_MAP_SIZE;
    if( address >= 0xE000 && address <= 0xFDFF )
        mapped_address -= address - 0x2000;
    else
        mapped_address -= ECHO_RAM_SIZE;

    return m_memory[mapped_address];
}

u16 MemorySystem::read_16( u16 address )
{
    word value;

    value.lo  = read_8( address );
    value.hi = read_8( address + 1 );

    return value.data;
}

void MemorySystem::write( u16 /*address*/, u8 /*data*/ )
{
    assert( false ); // NOT IMPLEMENTED!!
}

void MemorySystem::write( u16 /*address*/, u16 /*data*/ )
{
    assert( false ); // NOT IMPLEMENTED!!
}
