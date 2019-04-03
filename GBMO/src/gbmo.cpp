
#include "gbmo.h"
#include "options.h"
#include "utils/assert.h"
#include "utils/logger.h"

#include <SDL.h>
#include <thread>

GBMO::GBMO( Options const& options )
    : m_cartridge( options.m_rom_path )
    , m_memory_system( *this )
    , m_cpu( m_memory_system )
    , m_joypad( m_cpu, m_memory_system )
    , m_display( m_cpu, m_memory_system )
{
    m_joypad.set_input_bindings( options.m_inputs );

    // Quita esto de aqui
    LOG( NO_CAT, "Rom loaded: %s [%s]", options.m_rom_path.c_str(), m_cartridge.get_title_name() );

    m_cartridge.print_header_values();
    m_cartridge.log_header_values();
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
    auto start = std::chrono::high_resolution_clock::now();
    
    if( !handle_input_event() )
        return false;

    u32 cycles_to_render = 0;
    u32 cycles = 0;
    while( cycles_to_render < 70224 )
    {
        cycles = m_cpu.process_interrupts();
        cycles += m_cpu.update();
        m_cpu.update_timer_registers( cycles );
        m_cpu.update_divider_register( cycles );
        m_display.update( cycles );

        cycles_to_render += cycles;
    }
    m_display.render();

    static float const frame_time = 1000.0f / 59.73f;

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float, std::milli> diff = end - start;

    m_cartridge.update_timer( diff.count() );

    float const frame_delta = frame_time - diff.count();
    if( frame_delta > 0.f )
    {
        // TODO ADD THIS INTO THE OPTIONS (~60FPS)
        std::this_thread::sleep_for( std::chrono::duration<float, std::milli>( frame_delta ) );
    }
    //LOG( "UPDATE", "Update time: %f [%f] -> %f", diff.count(), frame_time, frame_delta );

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

        if( m_event.type == SDL_KEYDOWN && m_event.key.keysym.sym == SDLK_F2 )
        {
            m_display.cycle_palette();
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
