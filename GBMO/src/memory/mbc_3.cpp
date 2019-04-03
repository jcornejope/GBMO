#include "memory/mbc_3.h"
#include <fstream>

#include "utils/assert.h"

MBC_3::MBC_3( u8* cartridge_rom, u8* cartridge_ram, u32 rom_size, u32 ram_size )
    : MBC( cartridge_rom, cartridge_ram, rom_size, ram_size )
    , m_elapsed_milliseconds( 0.f )
    , m_timer_latched_secs( 0 )
    , m_rom_bank( 1 )
    , m_ram_bank_n_rtc( 0 )
    , m_ramcs_n_clock_counter( false )
{}

u8 MBC_3::read( u16 address )
{
    if( address < ROM_BANK_SIZE )
        return m_cartridge_rom[address];

    if( address < ROM_BANK_SIZE * 2 )
    {
        u32 const mapped_address = ( m_rom_bank * ROM_BANK_SIZE ) + ( address - ROM_BANK_SIZE );
        ASSERT( mapped_address < m_rom_size );
        return m_cartridge_rom[mapped_address];
    }

    if( address >= 0xA000 && address <= 0xBFFF && m_cartridge_ram )
    {
        switch( m_ram_bank_n_rtc )
        {
        case RAM_BANK_0:
        case RAM_BANK_1:
        case RAM_BANK_2:
        case RAM_BANK_3:
            return m_cartridge_ram[_get_ram_mapped_address( address )];
            break;
        case RTC_S:  //break;
        case RTC_M:  //break;
        case RTC_H:  //break;
        case RTC_DL: //break;
        case RTC_DH: //break;
            // TODO RTC
            return 0xFF;
        }
    }

    // Invalid address
    ASSERT( false );
    return 0xFF;
}

void MBC_3::write( u16 address, u8 data )
{
    if( address < 0x2000 )
    {
        if( m_cartridge_ram )
            m_ramcs_n_clock_counter = ( data & 0x0F ) == 0x0A;
    }
    else if( address < 0x4000 )
    {
        m_rom_bank = data & 0x7F;
        if( m_rom_bank == 0 )
            m_rom_bank = 1;
    }
    else if( address < 0x6000 )
    {
        m_ram_bank_n_rtc = data;
    }
    else if( address < 0x8000 )
    {
        // TODO LATCH
    }
    else if( address >= 0xA000 && address <= 0xBFFF )
    {
        switch( m_ram_bank_n_rtc )
        {
        case RAM_BANK_0:
        case RAM_BANK_1:
        case RAM_BANK_2:
        case RAM_BANK_3:
        {
            if( m_cartridge_ram && m_ramcs_n_clock_counter )
                m_cartridge_ram[_get_ram_mapped_address( address )] = data;
        }
            break;
        case RTC_S: break;
        case RTC_M: break;
        case RTC_H: break;
        case RTC_DL: break;
        case RTC_DH: break;
            // TODO RTC
        }
    }
    else
    {
        ASSERT( false );
    }
}

void MBC_3::update_timer( float delta_time_ms )
{
    if( m_rtc.m_dh & RTC_DH_FLAGS::HALT )
        return;

    m_elapsed_milliseconds += delta_time_ms;
    while( m_elapsed_milliseconds >= 1000 )
    {
        m_elapsed_milliseconds -= 1000;

        if( !m_rtc.m_latched )
        {
            ++m_rtc.m_s;
            if( m_rtc.m_s == 60 )
            {
                ++m_rtc.m_m;
                if( m_rtc.m_m == 60 )
                {
                    ++m_rtc.m_h;
                    if( m_rtc.m_h == 24 )
                    {
                        u16 day = ( ( m_rtc.m_dh & 1 ) << 8 ) | m_rtc.m_dl;
                        ++day;
                        
                        // calc carry
                        if( day & 0x200 )
                        {
                            m_rtc.m_dh |= RTC_DH_FLAGS::CARRY;
                            day = 0;
                        }

                        m_rtc.m_dl = day & 0xFF;
                        m_rtc.m_dh |= day & 0x100;
                    }
                }
            }
        }
        else
        {
            ++m_timer_latched_secs;
        }
    }
}

void MBC_3::on_load( std::ifstream& file )
{
    ASSERT_MSG( file.is_open(), "Trying to load RTC for MBC3 but save file is not open!" );

    // use m_timer_latched_secs, save RTC and save the date
    if( !file.is_open() )
        return;
}

void MBC_3::on_save( std::ofstream& file )
{
    ASSERT_MSG( file.is_open(), "Trying to save RTC for MBC3 but save file is not open!" );

    // restore the date and calculate the RTC values for it
    if( !file.is_open() )
        return;
}

u16 MBC_3::_get_ram_mapped_address( u16 const address ) const
{
    u16 mapped_address = ( m_ram_bank_n_rtc * RAM_BANK_SIZE ) + ( address - 0xA000 );
    ASSERT( mapped_address < m_ram_size );
    return mapped_address;
}
