#include "memory/mbc_2.h"

#include "utils/assert.h"

MBC_2::MBC_2( u8* cartridge_rom, u8* cartridge_ram, u32 rom_size, u32 ram_size )
    : MBC( cartridge_rom, cartridge_ram, rom_size, ram_size )
    , m_rom_bank( 1 )
    , m_ramcs( false )
{
}

u8 MBC_2::read( u16 address )
{
    if( address < ROM_BANK_SIZE )
        return m_cartridge_rom[address];

    if( address < ROM_BANK_SIZE * 2 )
    {
        u32 const mapped_address = ( m_rom_bank * ROM_BANK_SIZE ) + ( address - ROM_BANK_SIZE );
        ASSERT( mapped_address < m_rom_size );
        return m_cartridge_rom[mapped_address];
    }

    if( address >= 0xA000 && address < 0xA200 )
    {
        u16 const mapped_address = address & 0x0FFF;
        ASSERT( mapped_address < m_ram_size );
        return m_cartridge_ram[mapped_address];
    }

    // Invalid address
    ASSERT( false );
    return 0xFF;
}

void MBC_2::write( u16 address, u8 data )
{
    if( address < 0x2000 )
    {
        if( ( address & WRITE_RAM_ROM_BIT ) == 0 )
        {
            m_ramcs = ( data & 0x0F ) == 0x0A;
        }
    }
    else if( address < 0x4000 )
    {
        if( ( address & WRITE_RAM_ROM_BIT ) != 0 )
        {
            m_rom_bank = ( data & 0x0F );
            if( m_rom_bank == 0 )
                m_rom_bank = 1;
        }
    }
    else if( address >= 0xA000 && address < 0xA200 && m_ramcs )
    {
        u16 const mapped_address = address & 0x0FFF;
        m_cartridge_ram[mapped_address] = data & 0x0F;
    }
}