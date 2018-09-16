#include "display.h"
#include "memory/memory_system.h"
#include "options.h"

#include <SDL.h>

Display::Display( MemorySystem & memory )
    : m_memory( memory )
    , m_window( nullptr )
    , m_renderer( nullptr )
    , m_mode( Mode::H_BLANK )
{
}

bool Display::init( Options const & options )
{
    m_window = SDL_CreateWindow( "GBMO v0.1",
                                 SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                 160 * options.m_resolution_scale, 144 * options.m_resolution_scale,
                                 SDL_WINDOW_SHOWN );
    m_renderer = SDL_CreateRenderer( m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );

    return m_window && m_renderer;
}

void Display::update()
{
}
