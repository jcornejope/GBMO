
#include "memory/memory_system.h"

#include "cartridge/cartridge.h"
#include "gbmo.h"
#include "joypad/joypad.h"
#include "utils/assert.h"

MemorySystem::MemorySystem( GBMO& gameboy )
    : m_gameboy( gameboy )
{
    std::memset( &m_memory, 0, SYSTEM_MEMORY_SIZE );
}

u8 MemorySystem::read_8( u16 address )
{
    if( _is_memory_handled_by_cartridge( address ) )
        return m_gameboy.get_cartridge()._read( address );
    else if( address == DMA_TRANSFER_ADDR )
        return 0xFF;    // Write-only

    u16 mapped_address = _remap_address( address );
    return m_memory[mapped_address];
}

u16 MemorySystem::read_16( u16 address )
{
    word value;

    value.lo = read_8( address );
    value.hi = read_8( address + 1 );

    return value.data;
}

void MemorySystem::read_oam_chunk( u16 address, u8* buffer, u16 size )
{
    ASSERT( address >= OAM_START_ADDR && address + size <= OAM_END_ADDR + 1 );
    ASSERT( buffer );

    u16 mapped_address = _remap_address( address );
    std::memcpy( buffer, &m_memory[mapped_address], size );
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
        //ASSERT_MSG( false, "Trying to write on PROHIBITED address [%#06x]", address );
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
        u8 low_data = m_gameboy.get_joypad().get_inputs_for_memory( data );
        data = ( data & 0x30 ) | low_data;
    }

    u16 mapped_address = _remap_address( address );
    m_memory[mapped_address] = data;

    if( address == DMA_TRANSFER_ADDR )
        _start_dma_transfer();
}

void MemorySystem::write( u16 address, u16 data )
{
    word value = { data };

    write( address, value.lo );
    write( address + 1, value.hi );
}

void MemorySystem::non_protected_write( u16 address, u8 data )
{
    u16 mapped_address = _remap_address( address );
    m_memory[mapped_address] = data;
}

bool MemorySystem::_is_memory_handled_by_cartridge( u16 const address ) const
{
    return ( address < 0x8000 ) || ( address >= 0xA000 && address < 0xC000 );
}

u16 MemorySystem::_remap_address( u16 const address )
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

    ASSERT_MSG( mapped_address < SYSTEM_MEMORY_SIZE, "mapped_address [%#06x] out of bounds!", mapped_address );
    return mapped_address;
}

void MemorySystem::_start_dma_transfer()
{
    static u16 const DMA_TRANSFER_MAPPED_ADDR = _remap_address( DMA_TRANSFER_ADDR );
    static u16 const OAM_MAPPED_ADDR = _remap_address( OAM_START_ADDR );

    // TODO: Should this be done gradually so it takes 160 cycles?

    u16 const source_addr = static_cast<u16>( m_memory[DMA_TRANSFER_MAPPED_ADDR] ) << 8;
    //ASSERT_MSG( source_addr >= 0x80 && source_addr <= 0xDF, "Invalid source address[%#04x] for DMA transfer to OAM!", source_addr );
    ASSERT_MSG( source_addr <= 0xF100, "Invalid source address[%#04x] for DMA transfer to OAM!", source_addr );
    if( source_addr > 0xF100 )
        return;

    if( _is_memory_handled_by_cartridge( source_addr ) )
    {
        for( u16 i = 0; i < 0x100; ++i )
            m_memory[OAM_MAPPED_ADDR + i] = read_8( source_addr + i );
    }
    else
    {
        u16 const source_mapped_addr = _remap_address( source_addr );
        std::memcpy( &m_memory[OAM_MAPPED_ADDR], &m_memory[source_mapped_addr], 0x100 );
    }
}
