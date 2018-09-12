
#include "gbmo.h"
#include "options.h"

GBMO::GBMO( Options const& options )
    : m_cartridge( options.m_rom_path )
    , m_memory_system( *this )
    , m_cpu( m_memory_system )
    , m_joypad( m_cpu, m_memory_system )
{
    m_joypad.set_input_bindings( options.m_inputs );

    // Quita esto de aqui
    m_cartridge.print_header_values();
}

bool GBMO::update()
{
    u32 cycles = m_cpu.process_interrupts();
    cycles += m_cpu.update();
    m_cpu.update_timer_registers( cycles );
    m_cpu.update_divider_register( cycles );

    return cycles != 0;
}

void GBMO::handle_input_event( SDL_Event & event )
{
    if( event.type == SDL_KEYDOWN || event.type == SDL_KEYUP ||
        event.type == SDL_JOYBUTTONDOWN || event.type == SDL_JOYBUTTONUP || 
        event.type == SDL_JOYAXISMOTION )
    {
        m_joypad.handle_input_event( event );
    }
}
