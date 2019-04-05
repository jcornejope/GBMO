#include "memory/mbc_3.h"
#include <fstream>
#include <chrono>

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
        case RTC_S:  return m_rtc.m_s;  break;
        case RTC_M:  return m_rtc.m_m;  break;
        case RTC_H:  return m_rtc.m_h;  break;
        case RTC_DL: return m_rtc.m_dl; break;
        case RTC_DH: return m_rtc.m_dh; break;
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
        if( m_rtc_pre_latch_active && data == 0x1 )
        {
            m_rtc.m_latched = !m_rtc.m_latched;
            m_rtc_pre_latch_active = false;
        }
        else if( data == 0x0 )
        {
            m_rtc_pre_latch_active = true;
        }
        else
        {
            m_rtc_pre_latch_active = false;
        }
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
        case RTC_S:     m_rtc.m_s  = data;  break;
        case RTC_M:     m_rtc.m_m  = data;  break;
        case RTC_H:     m_rtc.m_h  = data;  break;
        case RTC_DL:    m_rtc.m_dl = data;  break;
        case RTC_DH:    m_rtc.m_dh = data;  break;
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
            _add_time_to_rtc( 1 );
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

    file.read( reinterpret_cast<char*>( &m_rtc ), sizeof( m_rtc ) );

    {
        using namespace std::chrono;
        
        seconds::rep saved_secs_since_epoch;
        file.read( reinterpret_cast<char*>( &saved_secs_since_epoch ), sizeof( saved_secs_since_epoch ) );

        time_point<system_clock> time_now = system_clock::now();
        auto secs_since_epoch = duration_cast<seconds>( time_now.time_since_epoch() ).count();

        auto secs_since_save = secs_since_epoch - saved_secs_since_epoch;
        if( secs_since_save > 0 )
        {
            _add_time_to_rtc( static_cast<u32>( secs_since_save ) );
        }
    }

}

void MBC_3::on_save( std::ofstream& file )
{
    ASSERT_MSG( file.is_open(), "Trying to save RTC for MBC3 but save file is not open!" );

    if( m_timer_latched_secs > 0.f )
    {
        _add_time_to_rtc( m_timer_latched_secs );
    }

    std::streamsize s = sizeof( m_rtc );
    file.write( reinterpret_cast<char*>( &m_rtc ), sizeof( m_rtc ) );

    {
        using namespace std::chrono;
        time_point<system_clock> time_now = system_clock::now();
        auto secs_since_epoch = duration_cast<seconds>( time_now.time_since_epoch() ).count();
        s = sizeof( secs_since_epoch );
        file.write( reinterpret_cast<char*>( &secs_since_epoch ), sizeof( secs_since_epoch ) );
    }
}

u16 MBC_3::_get_ram_mapped_address( u16 const address ) const
{
    u16 mapped_address = ( m_ram_bank_n_rtc * RAM_BANK_SIZE ) + ( address - 0xA000 );
    ASSERT( mapped_address < m_ram_size );
    return mapped_address;
}

void MBC_3::_add_time_to_rtc( u32 secs )
{   
    secs += m_rtc.m_s;
    u32 mins = m_rtc.m_m + ( secs / 60 );
    u32 hours = m_rtc.m_h + ( mins / 60 );

    u32 days = ( ( m_rtc.m_dh & 1 ) << 8 ) | m_rtc.m_dl;
    days += hours / 24;

    // calc carry
    if( days >= 0x200 )
    {
        m_rtc.m_dh |= RTC_DH_FLAGS::CARRY;
        days %= 0x200;
    }

    m_rtc.m_dl = days & 0xFF;
    m_rtc.m_dh |= days & 0x100;

    m_rtc.m_s = secs % 60;
    m_rtc.m_m = mins % 60;
    m_rtc.m_h = hours % 24;
}
