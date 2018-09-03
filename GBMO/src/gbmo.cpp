
#include "gbmo.h"
#include "options.h"

GBMO::GBMO( Options const& options )
    : m_cartridge( options.m_rom_path )
    , m_memory_system( m_cartridge )
    , m_cpu( m_memory_system )
{
    // Quita esto de aqui
    m_cartridge.print_header_values();
}

bool GBMO::update()
{
    u32 cycles = m_cpu.update();

    return cycles != 0;
}
