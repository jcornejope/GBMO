#pragma once

#include <string>
#include "catridge_utils.h"

class MemorySystem;
class MBC;

class Cartridge
{
    friend class MemorySystem;

    static u32 const TITLE_SIZE = 16;
    static u32 const BANK_SIZE = 16;

    static char const* SAVE_FILE_EXT;

public:
    Cartridge(std::string const& rom_path);
    ~Cartridge();

    std::string const&  get_file_path() const           { return m_file_path; }
    char const*         get_title_name() const          { return &m_title_name[0]; }
    s32                 get_rom_size() const            { return m_rom_size; }
    CartridgeType       get_cartridge_type() const;
    ROMSize             get_rom_size_type() const;
    RAMSize             get_ram_size_type() const;
    DestinationCode     get_destination_code() const;
    u16                 get_license_code() const;
    bool                get_sgb_support() const;
    CGBSupport          get_cgb_support() const;
    u8                  get_version_number() const;
    u8                  get_header_checksum() const;
    u16                 get_cartridge_checksum() const;
    bool                has_battery() const;

    void print_header_values() const;
    void log_header_values() const;
    void dump_rom() const;

private:
    u8   _read( u16 address );
    void _write( u16 address, u8 data );

    /// Open and loads the content of the file into the cartridge rom memory.
    bool _load_rom();
    /// Reads the header data and sets all the value of the cartridge members.
    bool _load_header();
    bool _check_header_checksum() const;
    bool _create_ram();
    bool _create_mbc();

    /// Loads the savefile containing the ram.
    void _load_ram_sav();
    /// Saves the ram to a file for battery powered cartridges.
    void _save_ram_sav();
    /// Returns the size of the portion of ram needed to be save/load to/from file.
    u16 _get_save_ram_size();

    s32 _get_ram_size() const;

    /// Path to the file in disk which contains the rom.
    std::string m_file_path;
    /// Name of the game stored in the cartridge header.
    char m_title_name[TITLE_SIZE + 1];

    /// The full rom memory.
    u8* m_rom;
    /// The external ram memory.
    u8* m_ram;
    /// The MBC used in this cartridge
    MBC* m_mbc;
    /// Actual rom size in bytes (actual size of the loaded file).
    s32 m_rom_size;
};
