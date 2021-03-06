
#include "cartridge.h"

#include "memory/mbc_none.h"
#include "memory/mbc_1.h"
#include "memory/mbc_2.h"
#include "memory/mbc_3.h"
#include "options.h"
#include "utils/assert.h"
#include "utils/logger.h"
#include "utils/utils.h"

#include <fstream>
#include <iostream>
#include <zip.h>

char const* Cartridge::SAVE_FILE_EXT = ".sav";

Cartridge::Cartridge( Options const& options )
    : m_file_path( options.m_rom_path.c_str() )
    , m_zip_passwd( options.m_zip_password.c_str() )
    , m_rom( nullptr )
    , m_ram( nullptr )
    , m_mbc( nullptr )
    , m_rom_size( -1 )
    , m_rom_loaded_successfully( false )
    , m_ram_save_load_enabled( options.m_ram_save_enabled )
{
    std::memset( &m_title_name, 0, TITLE_SIZE + 1 );

    bool ok = false;
    if( _load_rom() )
    {
        ok = true;
        ok &= _load_header();
        _create_ram();
        ok &= _create_mbc();

        if( m_ram_save_load_enabled && has_battery() )
            _load_ram_sav();
    }

    if( !ok )
    {
        LOG_E( LogCat::ROM, "ROM failed to load: %s", m_file_path );
        ERROR_MSG( "ROM failed to load: %s", m_file_path ); // TODO: Make ERROR_MSG add a log too.
    }

    m_rom_loaded_successfully = ok;
}

Cartridge::~Cartridge()
{
    if( m_rom_loaded_successfully && m_ram_save_load_enabled && has_battery() )
        _save_ram_sav();

    delete[] m_rom;
    m_rom = nullptr;

    delete[] m_ram;
    m_ram = nullptr;

    delete m_mbc;
    m_mbc = nullptr;
}

void Cartridge::update_timer( float delta_time_ms )
{
    if( m_mbc && has_timer() )
        m_mbc->update_timer( delta_time_ms );
}

bool Cartridge::_load_rom()
{
    LOG( LogCat::ROM, "Loading ROM [%s]", m_file_path );

    // Open ZIP file
    int zip_error = ZIP_ER_OK;
    zip_t* zip_file = zip_open(m_file_path, ZIP_RDONLY, &zip_error );
    if( zip_file && zip_error == ZIP_ER_OK )
    {
        // Find a gb or gbc rom file within the zip archive.
        zip_set_default_password( zip_file, m_zip_passwd );
        for( zip_int64_t i = 0, num = zip_get_num_entries( zip_file, ZIP_FL_UNCHANGED );
            ( i < num ) && ( m_rom == nullptr );
            ++i )
        {
            zip_stat_t zip_stat{};
            if( zip_stat_index( zip_file, i, ZIP_FL_UNCHANGED, &zip_stat ) == 0 )
            {
                if( zip_stat.valid & ( ZIP_STAT_NAME | ZIP_STAT_SIZE ) )
                {
                    char const* ext_char = strrchr( zip_stat.name, '.' );
                    if( !ext_char )
                        continue;

                    std::string ext{ ext_char };
                    for( int c = 0; ext[c] != '\0'; ++c )
                        ext[c] = static_cast<char>( tolower( ext[c] ) );
                    
                    if( ext == ".gb" || ext == ".gbc" )
                    {
                        zip_file_t* rom_file = zip_fopen_index( zip_file, i, ZIP_FL_UNCHANGED );
                        if( rom_file )
                        {
                            m_rom_size = static_cast<s32>( zip_stat.size );
                            if( m_rom_size <= 0 )
                                LOG_W( LogCat::ROM, "File [%s] is empty!", zip_stat.name );

                            m_rom = new u8[m_rom_size];
                            zip_int64_t bytes_read = zip_fread( rom_file, m_rom, m_rom_size );
                            if( bytes_read != m_rom_size )
                            {
                                m_rom_size = 0;
                                delete[] m_rom;
                                m_rom = nullptr;

                                LOG_W( LogCat::ROM, "Error reading file [%s] in ZIP archive - [%ll] bytes read from [%ll]", zip_stat.name, bytes_read, m_rom_size );
                            }

                            zip_fclose( rom_file );
                        }
                        else
                        {
                            zip_error_t *error = zip_get_error( zip_file );
                            LOG_W( LogCat::ROM, "Error opening file [%s] in ZIP archive - Error [%s]", zip_stat.name, zip_error_strerror( error ) );
                        }
                    }
                }
            }
        }
    }
    else if( zip_error != ZIP_ER_NOZIP )
    {
        LOG_W( LogCat::ROM, "Error opening zip file [%d]", zip_error );
    }

    if( zip_file )
        zip_discard( zip_file );

    if( m_rom_size > 0 )
        return true;

    // Open file as binary, for reading and seek to the end of the file
    std::ifstream file( m_file_path, std::ios::in | std::ios::binary | std::ios::ate );

    if( !file.is_open() )
    {
        LOG_E( LogCat::ROM, "ROM file not found or unable to open." );
        return false;
    }

    m_rom_size = static_cast<s32>( file.tellg() );
    if( m_rom_size <= 0 )
    {
        LOG_E( LogCat::ROM, "File is empty." );
        file.close();
        return false;
    }

    m_rom = new u8[m_rom_size];
    file.seekg( std::ios::beg );
    file.read( reinterpret_cast<char*>( m_rom ), m_rom_size );

    file.close();
    return true;
}

CartridgeType Cartridge::get_cartridge_type() const 
{
    return CartridgeType( m_rom[0x0147] );
}

ROMSize Cartridge::get_rom_size_type() const 
{
    return ROMSize( m_rom[0x0148] ); 
}

RAMSize Cartridge::get_ram_size_type() const 
{
    return RAMSize( m_rom[0x0149] ); 
}

DestinationCode Cartridge::get_destination_code() const
{
    return DestinationCode( m_rom[0x014A] );
}

u16 Cartridge::get_license_code() const
{
    // License code - 0x33 on the old license code byte will indicate to use the new license code value.
    u16 code = m_rom[0x014B];
    if( code == 0x33 )
    {
        code = m_rom[0x0145];
        code |= m_rom[0x0144] << 8;
    }

    return code;
}

bool Cartridge::get_sgb_support() const
{
    return m_rom[0x0146] == 0x03;
}

CGBSupport Cartridge::get_cgb_support() const
{
    CGBSupport support = CGBSupport( m_rom[0x0143] );
    if( m_rom[0x0143] == 0x42 || m_rom[0x0143] == 0x44 )
        support = CGBSupport::NO_CGB_NO_PALETTE_INIT;

    return support;
}

u8 Cartridge::get_version_number() const
{
    return m_rom[0x014C];
}

u8 Cartridge::get_header_checksum() const
{
    return m_rom[0x014D];
}

u16 Cartridge::get_cartridge_checksum() const
{
    u16 checksum = m_rom[0x014F];
    checksum |= m_rom[0x014E] << 8;
    return checksum;
}

bool Cartridge::has_battery() const
{
    switch( get_cartridge_type() )
    {
    case CartridgeType::MBC1_RAM_BATTERY:
    case CartridgeType::MBC2_BATTERY:
    case CartridgeType::ROM_RAM_BATTERY:            
    case CartridgeType::MMM01_RAM_BATTERY:
    case CartridgeType::MBC3_TIMER_BATTERY:
    case CartridgeType::MBC3_TIMER_RAM_BATTERY:
    case CartridgeType::MBC3_RAM_BATTERY:
    case CartridgeType::MBC4_RAM_BATTERY:
    case CartridgeType::MBC5_RAM_BATTERY:
    case CartridgeType::MBC5_RUMBLE_RAM_BATTERY:
    case CartridgeType::HuC1_RAM_BATTERY:
        return true;
        break;
    }
    return false;
}

bool Cartridge::has_timer() const
{
    CartridgeType ct = get_cartridge_type();
    return ct == CartridgeType::MBC3_TIMER_BATTERY || ct == CartridgeType::MBC3_TIMER_RAM_BATTERY;
}

u8 Cartridge::_read( u16 address )
{
    ASSERT_MSG( m_mbc, "Trying to read from a cartridge with no MBC instance created [%s]", to_string( get_cartridge_type() ) );
    if( m_mbc == nullptr )
        return 0xFF;
    return m_mbc->read( address );
}

void Cartridge::_write( u16 address, u8 data )
{
    ASSERT_MSG( m_mbc, "Trying to write to a cartridge with no MBC instance created [%s]", to_string( get_cartridge_type() ) );
    if( m_mbc != nullptr )
        m_mbc->write( address, data );
}

bool Cartridge::_load_header()
{
    // TODO: Depending on the cartridge the title size varies as newer cartridge are limited to 15 or 11 chars.
    u32 const title_size = TITLE_SIZE;

    // Title
    for( u32 i = 0u; i < title_size; ++i )
        m_title_name[i] = m_rom[0x0134 + i];

    return true;
}

bool Cartridge::_check_header_checksum() const
{
    u8 value = 0;
    for( int i = 0x0134; i < 0x014D; ++i )
        value += ~m_rom[i];

    return value == get_header_checksum();
}

void Cartridge::_create_ram()
{
    auto const ram_size = _get_ram_size();

    if( ram_size > 0 )
    {
        m_ram = new u8[ram_size];
        memset( m_ram, 0x00, ram_size );
    }
}

bool Cartridge::_create_mbc()
{
    switch( get_cartridge_type() )
    {
    case CartridgeType::ROM_ONLY:               m_mbc = new MBC_None( m_rom, m_ram );   break;
    case CartridgeType::MBC1:
    case CartridgeType::MBC1_RAM:
    case CartridgeType::MBC1_RAM_BATTERY:       m_mbc = new MBC_1( m_rom, m_ram, get_rom_size(), _get_ram_size() ); break;
    case CartridgeType::MBC2:
    case CartridgeType::MBC2_BATTERY:           m_mbc = new MBC_2( m_rom, m_ram, get_rom_size(), _get_ram_size() ); break;
    case CartridgeType::MBC3:
    case CartridgeType::MBC3_RAM:
    case CartridgeType::MBC3_RAM_BATTERY:
    case CartridgeType::MBC3_TIMER_BATTERY:
    case CartridgeType::MBC3_TIMER_RAM_BATTERY: m_mbc = new MBC_3( m_rom, m_ram, get_rom_size(), _get_ram_size() ); break;
    }

    if( m_mbc == nullptr )
        LOG_E( LogCat::ROM, "Error trying to create MBC [%s]", to_string( get_cartridge_type() ) );

    return m_mbc != nullptr;
}

void Cartridge::_load_ram_sav()
{
    ASSERT_MSG( has_battery(), "Trying to load the ram from a cartridge with no battery support!" );
    ASSERT_MSG( m_ram_save_load_enabled, "Cartridge RAM save and load is disabled!" );

    std::string const save_file{ m_file_path + std::string{ SAVE_FILE_EXT } };
    LOG( LogCat::ROM, "Loading RAM save [%s]", save_file.c_str() );

    std::ifstream file( save_file, std::ios::in | std::ios::binary | std::ios::ate );
    if( !file.is_open() )
    {
        LOG( LogCat::ROM, "RAM save not found" );
        return;
    }

    u32 const ram_size = _get_ram_size();
    ASSERT( file.tellg() == ram_size );
    if( file.tellg() != ram_size )
    {
        LOG( LogCat::ROM, "RAM save size [%u] doesn't match cartridge ram size [%u]!", file.tellg() , ram_size );
        return;
    }

    file.seekg( std::ios::beg );
    file.read( reinterpret_cast<char*>( m_ram ), ram_size );

    if( m_mbc && has_timer() )
        m_mbc->on_load( file );

    //file.close();
}

void Cartridge::_save_ram_sav()
{
    ASSERT_MSG( has_battery(), "Trying to save the RAM from a cartridge with no battery support!" );
    ASSERT_MSG( m_ram_save_load_enabled, "Cartridge RAM save and load is disabled!" );

    std::string const save_file{ m_file_path + std::string{ SAVE_FILE_EXT } };
    LOG( LogCat::ROM, "Saving RAM save [%s]", save_file.c_str() );

    std::ofstream file( save_file, std::ios::out | std::ios::binary );
    if( !file.is_open() )
    {
        LOG( LogCat::ROM, "Failed to save RAM. File not open. Is file locked or read-only?" );
        return;
    }

    file.write( reinterpret_cast<char const*>( m_ram ), _get_ram_size() );

    if( m_mbc && has_timer() )
        m_mbc->on_save( file );

    //file.close();
}

u32 Cartridge::_get_ram_size() const
{
    auto const catridge_type = get_cartridge_type();
    if( catridge_type == CartridgeType::MBC2 || catridge_type == CartridgeType::MBC2_BATTERY )
    {
        // When using a MBC2 chip 00h must be specified in RAMSize, even though the MBC2 includes a built-in RAM of 512 x 4 bits.
        return 0x200;
    }

    s32 ret = 0;
    switch( get_ram_size_type() )
    {
    case RAMSize::RAM_2:    ret = 1024 * 2;   break;
    case RAMSize::RAM_8:    ret = 1024 * 8;   break;
    case RAMSize::RAM_32:   ret = 1024 * 32;  break;
    }

    return ret;
}

void Cartridge::print_header_values() const
{
    std::cout << "ROM Loaded: " << m_title_name << std::endl;
    std::cout << "Type: " << to_string( get_cartridge_type() ) << std::endl;
    std::cout << "ROMSize: " << m_rom_size << " Type: " << to_string( get_rom_size_type() ) << std::endl;
    std::cout << "RAMSize: " << to_string( get_ram_size_type() ) << std::endl;
    std::cout << "Destination: " << to_string( get_destination_code() ) << std::endl;
    std::cout << "SGB support: " << std::boolalpha << get_sgb_support() << std::endl;
    std::cout << "CGB support: " << to_string( get_cgb_support() ) << std::endl;
    std::cout << "Version: " << static_cast<int>( get_version_number() ) << std::endl;
    
    word license = { get_license_code() };
    std::cout << "License Code: " << std::hex << static_cast<int>( license.hi ) << " " << static_cast<int>( license.lo ) << std::endl;
    word checksum = { get_cartridge_checksum() };
    std::cout << "Cartridge Checksum: " << static_cast<int>( checksum.hi ) << " " << static_cast<int>( checksum.lo ) << std::endl;
    std::cout << "Header Checksum [" << std::dec << static_cast<int>( get_header_checksum() ) << "] Passed?: " << std::boolalpha << _check_header_checksum() << std::endl;

    std::cout << std::endl;
}

void Cartridge::log_header_values() const
{
    LOG( LogCat::ROM, "----------------------------------------------------" );
    LOG( LogCat::ROM, "ROM Loaded: %s", m_title_name );
    LOG( LogCat::ROM, "Type: %s", to_string( get_cartridge_type() ) );
    LOG( LogCat::ROM, "ROMSize: %d Type: %s", m_rom_size, to_string( get_rom_size_type() ) );
    LOG( LogCat::ROM, "RAMSize: %s", to_string( get_ram_size_type() ) );
    LOG( LogCat::ROM, "Destination: %s", to_string( get_destination_code() ) );
    LOG( LogCat::ROM, "SGB support: %s", bool_to_alpha( get_sgb_support() ) );
    LOG( LogCat::ROM, "CGB support: %s", to_string( get_cgb_support() ) );
    LOG( LogCat::ROM, "Version: %d", static_cast<int>( get_version_number() ) );

    word license = { get_license_code() };
    LOG( LogCat::ROM, "License Code: %#04x %#04x", static_cast<int>( license.hi ), static_cast<int>( license.lo ) );
    word checksum = { get_cartridge_checksum() };
    LOG( LogCat::ROM, "Cartridge Checksum: %#04x %#04x", static_cast<int>( checksum.hi ), static_cast<int>( checksum.lo ) );
    LOG( LogCat::ROM, "Header Checksum [%d] Passed? %s", static_cast<int>( get_header_checksum() ), bool_to_alpha( _check_header_checksum() ) );
    LOG( LogCat::ROM, "----------------------------------------------------" );
}

void Cartridge::dump_rom() const
{
    std::cout << "=========== ROM DUMP: " << m_title_name << "===========" << std::endl;
    for( s32 i = 0; i < m_rom_size; ++i )
    {
        std::cout << std::hex << static_cast<int>( m_rom[i] ) << " ";
        if( i != 0 && i % BANK_SIZE == 0 )
            std::cout << std::endl;
    }
    std::cout << std::endl << "================================" << std::endl;
}
