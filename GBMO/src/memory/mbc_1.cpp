#include "memory/mbc_1.h"

#include "utils/assert.h"

MBC_1::MBC_1( u8* cartridge_rom, u8* cartridge_ram, u32 rom_size, u32 ram_size )
    : MBC( cartridge_rom, cartridge_ram, rom_size, ram_size )
    , m_rom_bank( 1 )
    , m_ram_bank( 0 )
    , m_ram_enabled( false )
    , m_rom_mode( true )
{}

u8 MBC_1::read( u16 address )
{
    if( address < ROM_BANK_SIZE )
        return m_cartridge_rom[address];

    if( address < ROM_BANK_SIZE * 2 )
    {
        u8 const rom_bank = m_rom_mode ? ( m_rom_bank | ( m_hi_rom_bank << 5 ) ) : 1;
        u16 const mapped_address = ( rom_bank * ROM_BANK_SIZE ) + ( address - ROM_BANK_SIZE );
        ASSERT( mapped_address < m_rom_size );
        return m_cartridge_rom[mapped_address];
    }

    if( address >= 0xA000 && address <= 0xBFFF && m_cartridge_ram )
    {
        return m_cartridge_ram[_get_ram_mapped_address( address )];
    }

    // Invalid address
    ASSERT( false );
    return 0xFF;
}

void MBC_1::write( u16 address, u8 data )
{
    if( address < 0x2000 )
    {
        if( m_cartridge_ram )
            m_ram_enabled = ( data & 0x0F ) == 0x0A;
    }
    else if( address < 0x4000 )
    {
        m_rom_bank |= data & 0x1F;
        if( ( m_rom_bank & 0x1F ) == 0 )
            ++m_rom_bank;
    }
    else if( address < 0x6000 )
    {
        m_hi_rom_bank = data & 0x3;
    }
    else if( address < 0x8000 )
    {
        m_rom_mode = ( data & 0x1 ) == 0;
    }
    else if( address >= 0xA000 && address <= 0xBFFF )
    {
        if( m_cartridge_ram )
            m_cartridge_ram[_get_ram_mapped_address( address )] = data;
    }
    else
    {
        ASSERT( false );
    }
}

u16 MBC_1::_get_ram_mapped_address( u16 const address ) const
{
    u8 const ram_bank = m_rom_mode ? 1 : m_ram_bank;
    u16 mapped_address = ( ram_bank * RAM_BANK_SIZE ) + ( address - 0xA000 );
    ASSERT( mapped_address < m_ram_size );
    return mapped_address;
}
