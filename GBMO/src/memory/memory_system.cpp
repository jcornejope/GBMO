
#include "memory/memory_system.h"

#include "cartridge/cartridge.h"
#include "gbmo.h"
#include "joypad/joypad.h"
#include "sound/sound.h"
#include "utils/assert.h"

MemorySystem::MemorySystem( GBMO& gameboy )
    : m_gameboy( gameboy )
{
    std::memset( &m_memory, 0x00, SYSTEM_MEMORY_SIZE );

    // Reset VRAM (0x8000-0x9FFF).
    //std::memset( &m_memory[_remap_address( 0x8000 )], 0x00, 0x2000 );

    // Reset Wave Table
    // DMG: 84 40 43 AA 2D 78 92 3C 60 59 59 B0 34 B8 2E DA
    // CGB: 00 FF 00 FF 00 FF 00 FF 00 FF 00 FF 00 FF 00 FF
    u8 const wave_table[] = { 0x84, 0x40, 0x43, 0xAA, 0x2D, 0x78, 0x92, 0x3C, 0x60, 0x59, 0x59, 0xB0, 0x34, 0xB8, 0x2E, 0xDA };
    std::memcpy( &m_memory[_remap_address( SND_WAVE_TABLE_ADDR )], &wave_table, sizeof( wave_table ) );
}

u8 MemorySystem::read_8( u16 address )
{
    if( _is_memory_handled_by_cartridge( address ) )
        return m_gameboy.get_cartridge()._read( address );
    
    u8 const read_mask = _get_read_mask( address );

    u16 mapped_address = _remap_address( address );
    return m_memory[mapped_address] | read_mask;
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

    switch( address )
    {
    case DIV_ADDR:
    case LCDC_Y_ADDR:
    {
        data = 0x00;
    }
    break;
    case P1_JOYP_ADDR:
    {
        // Remove the low part of data as it is read only.
        u8 low_data = m_gameboy.get_joypad().get_inputs_for_memory( data );
        data = ( data & 0x30 ) | low_data;
    }
    break;
    case LCDC_STAT_ADDR:
    {
        // Remove bits 0 - 1 as they are read only.
        data = ( data & 0xFC ) | ( read_8( LCDC_STAT_ADDR ) & 0x03 );
    }
    break;
    case SND_ON_OFF_ADDR:
    {
        auto const snd_on_off = read_8( SND_ON_OFF_ADDR );

        // Remove bits 0 - 3 they are read only.
        data = ( data & 0xF0 ) | ( snd_on_off & 0x0F );

        if( ( snd_on_off & Sound::MASTER_SWITCH ) && ( data & Sound::MASTER_SWITCH ) == 0 )
        {
            m_gameboy.get_sound().disable();
        }
        else if( ( snd_on_off & Sound::MASTER_SWITCH ) == 0 && ( data & Sound::MASTER_SWITCH ) )
        {
            m_gameboy.get_sound().enable();
        }
    }
    break;
    default: 
    {
        if( address >= SND_PWR_REG_START_ADDR && address <= SND_PWR_REG_END_ADDR && !m_gameboy.get_sound().is_enabled() )
        {
            // Sound register writes are ignored when the device is disabled (except DMG that allows write on lenght counters)
            if( address != CH1_LENGHT_N_DUTY_ADDR && address != CH2_LENGHT_N_DUTY_ADDR && address != CH3_LENGTH_ADDR && address != CH4_LENGTH_ADDR )
                return;
        }
    }
    break;
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

u8 MemorySystem::_get_read_mask( u16 address ) const
{
    //      NRx0 NRx1 NRx2 NRx3 NRx4
    //-------------------------- -
    //NR1x  $80  $3F $00  $FF  $BF
    //NR2x  $FF  $3F $00  $FF  $BF
    //NR3x  $7F  $FF $9F  $FF  $BF
    //NR4x  $FF  $FF $00  $00  $BF
    //NR5x  $00  $00 $70

    //$FF27 - $FF2F always read back as $FF
    static u8 const SND_READ_MASK[] = { 0x80, 0x3F, 0x00, 0xFF, 0xBF, 
                                        0xFF, 0x3F, 0x00, 0xFF, 0xBF, 
                                        0x7F, 0xFF, 0x9F, 0xFF, 0xBF, 
                                        0xFF, 0xFF, 0x00, 0x00, 0xBF, 
                                        0x00, 0x00, 0x70, 0xFF, 0xFF, 
                                        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
                                        0xFF, 0xFF };

    if( address >= 0xFF10 && address <= 0xFF2F )
        return SND_READ_MASK[address - 0xFF10];

    if( address == DMA_TRANSFER_ADDR )
        return 0xFF;

    return 0x00;
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
