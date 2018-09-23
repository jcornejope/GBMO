
#include "gbmo.h"
#include "options.h"
#include "utils/assert.h"

#include <SDL.h>

GBMO::GBMO( Options const& options )
    : m_cartridge( options.m_rom_path )
    , m_memory_system( *this )
    , m_cpu( m_memory_system )
    , m_joypad( m_cpu, m_memory_system )
    , m_display( m_cpu, m_memory_system )
{
    m_joypad.set_input_bindings( options.m_inputs );

    // Quita esto de aqui
    m_cartridge.print_header_values();
}

bool GBMO::init()
{
    if( SDL_Init( SDL_INIT_VIDEO ) != 0 )
    {
        ERROR_MSG( "SDL_Init Error [%s]", SDL_GetError() );
        return false;
    }

    return true;
}

void GBMO::deinit()
{
    SDL_Quit();
}

bool GBMO::update()
{
    if( !handle_input_event() )
        return false;

    u32 cycles = 0;
    while( cycles < 70224 )
    {
        cycles += m_cpu.process_interrupts();
        cycles += m_cpu.update();
        m_cpu.update_timer_registers( cycles );
        m_cpu.update_divider_register( cycles );
        m_display.update( cycles );
    }
    m_display.render();

    return true;
}

bool GBMO::handle_input_event()
{
    SDL_PumpEvents();
    while( SDL_PollEvent( &m_event ) )
    {
        // Check for user KB quit.
        if( ( m_event.type == SDL_QUIT ) ||
            ( m_event.type == SDL_KEYDOWN && m_event.key.keysym.sym == SDLK_ESCAPE ) )
        {
            return false;
        }
        
        if( m_event.type == SDL_KEYDOWN || m_event.type == SDL_KEYUP ||
            m_event.type == SDL_JOYBUTTONDOWN || m_event.type == SDL_JOYBUTTONUP ||
            m_event.type == SDL_JOYAXISMOTION )
        {
            m_joypad.handle_input_event( m_event );
        }
    }

    return true;
}
