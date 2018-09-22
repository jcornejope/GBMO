#include "display.h"
#include "memory/memory_system.h"
#include "options.h"
#include "utils/assert.h"

#include <SDL.h>

Display::Display( MemorySystem & memory )
    : m_memory( memory )
    , m_window( nullptr )
    , m_renderer( nullptr )
    , m_mode( Mode::SEARCHING_OAM_RAM )
{
}

Display::~Display()
{
    SDL_DestroyTexture( m_texture );
    SDL_DestroyRenderer( m_renderer );
    SDL_DestroyWindow( m_window );
}

bool Display::init( Options const & options )
{
    m_window = SDL_CreateWindow( "GBMO v0.1",
                                 SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                 160 * options.m_resolution_scale, 144 * options.m_resolution_scale,
                                 SDL_WINDOW_SHOWN );
    m_renderer = SDL_CreateRenderer( m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    m_texture = SDL_CreateTexture( m_renderer, 
                                   SDL_PIXELFORMAT_RGB24, 
                                   SDL_TEXTUREACCESS_STREAMING, 
                                   SCREEN_WIDTH, SCREEN_HEIGHT );

    std::memset( m_frame_buffer, 0xFF, sizeof( m_frame_buffer ) );
    render();

    return m_window && m_renderer && m_texture;
}

void Display::update()
{
    u8 lcdc = m_memory.read_8( LCD_CONTROL_ADDR );
    if( ( lcdc & DISPLAY_ENABLE ) != 0 )
    {

    }
    else
    {

    }
}

void Display::render()
{
    ASSERT( m_texture && m_renderer );

    SDL_UpdateTexture( m_texture, NULL, m_frame_buffer, SCREEN_WIDTH * sizeof( Pixel ) );
    SDL_RenderClear( m_renderer );
    SDL_RenderCopy( m_renderer, m_texture, NULL, NULL );
    SDL_RenderPresent( m_renderer );
}
