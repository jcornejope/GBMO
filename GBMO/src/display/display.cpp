
#include "display.h"

#include "cpu/cpu.h"
#include "memory/memory_system.h"
#include "options.h"
#include "utils/assert.h"

#include <SDL.h>

Display::Display( CPU& cpu, MemorySystem & memory )
    : m_memory( memory )
    , m_cpu( cpu )
    , m_window( nullptr )
    , m_renderer( nullptr )
    , m_texture( nullptr )
    , m_mode( Mode::SEARCHING_OAM_RAM )
    , m_display_cycles(0)
{
    std::memset( m_frame_buffer, 0xFF, sizeof( m_frame_buffer ) );
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
                                 SCREEN_WIDTH * options.m_resolution_scale, SCREEN_HEIGHT * options.m_resolution_scale,
                                 SDL_WINDOW_SHOWN );

    m_renderer = SDL_CreateRenderer( m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );

    m_texture = SDL_CreateTexture( m_renderer, 
                                   SDL_PIXELFORMAT_RGB24, 
                                   SDL_TEXTUREACCESS_STREAMING, 
                                   SCREEN_WIDTH, SCREEN_HEIGHT );

    render();

    return m_window && m_renderer && m_texture;
}

void Display::update( u32 cycles )
{
    u8 lcdc = m_memory.read_8( LCD_CONTROL_ADDR );
    if( ( lcdc & DISPLAY_ENABLE ) != 0 )
    {
        m_display_cycles += cycles;
        m_mode = static_cast<Mode>( lcdc & MODE );

        switch( m_mode )
        {
        case Mode::H_BLANK:                     _update_h_blank();          break;
        case Mode::V_BLANK:                     _update_v_blank();          break;
        case Mode::SEARCHING_OAM_RAM:           _update_oam_ram();          break;
        case Mode::TRANSFERRING_TO_LCD_DRIVER:  _update_transferring();     break;
        default:
            ERROR_MSG( "Invalid Display mode [%d]", m_mode );
            break;
        }
    }
    else
    {
        m_display_cycles = 0;
        m_memory.write( LCDC_Y_ADDR, u8( 0 ) );
        _set_mode( Mode::H_BLANK );
        _process_ly_lyc();
    }
}

void Display::render()
{
    ASSERT( m_texture && m_renderer );

    SDL_UpdateTexture( m_texture, NULL, m_frame_buffer, SCREEN_WIDTH * sizeof( Pixel ) );
    SDL_RenderClear( m_renderer );
    SDL_RenderCopy( m_renderer, m_texture, NULL, NULL );
    SDL_RenderPresent( m_renderer );

    std::memset( m_frame_buffer, m_frame_buffer[0].r + 1, sizeof( m_frame_buffer ) );
}

void Display::_set_mode( Mode new_mode )
{
    u32 new_mode_u32 = static_cast<u32>( new_mode );
    ASSERT_MSG( ( new_mode_u32 & 0xFC ) == 0, "Trying to set an invalid mode [%d], it will be clamped! [%d]", new_mode_u32, new_mode_u32 & 0x03 );

    if( m_mode != new_mode )
    {
        m_mode = new_mode;

        u8 lcdc_stat = m_memory.read_8( LCDC_STAT_ADDR );
        lcdc_stat = ( lcdc_stat & 0xFC ) | ( new_mode_u32 & 0x03 );
        m_memory.write( LCDC_STAT_ADDR, lcdc_stat );
    }
}

void Display::_process_ly_lyc()
{
}

void Display::_update_h_blank()
{
    if( m_display_cycles >= H_BLANK_MIN_CYCLES )
    {
        m_display_cycles -= H_BLANK_MIN_CYCLES;

        u8 ly = m_memory.read_8( LCDC_Y_ADDR ) + 1;
        m_memory.write( LCDC_Y_ADDR, ly );
        _process_ly_lyc();

        if( ly == SCREEN_HEIGHT )
        {
            _set_mode( Mode::V_BLANK );
            //m_display_cycles = 0; / need this?

            u8 lcdc_stat = m_memory.read_8( LCDC_STAT_ADDR );
            if( ( lcdc_stat & V_BLANK_INT ) != 0 )
            {
                m_cpu.request_interrupt( Interrupts::V_BLANK );
            }
        }
        else
        {
            _set_mode( Mode::SEARCHING_OAM_RAM );

            u8 lcdc_stat = m_memory.read_8( LCDC_STAT_ADDR );
            if( ( lcdc_stat & OAM_INT ) != 0 )
            {
                m_cpu.request_interrupt( Interrupts::LCD_STAT );
            }
        }
    }
}

void Display::_update_v_blank()
{
    if( m_display_cycles >= CYCLES_TO_LY_INCREMENT )
    {
        m_display_cycles -= CYCLES_TO_LY_INCREMENT;

        // V-BLANK lasts 10 times CYCLES_TO_LY_INCREMENT (V_BLANK_CYCLES = 4560)
        // that means the LY increases from 144 to 153 during V-Blank.
        // the following increment will change LY to 0 and change mode.
        u8 ly = m_memory.read_8( LCDC_Y_ADDR ) + 1;
        if( ly == 153 )
        {
            ly = 0;
        }

        m_memory.write( LCDC_Y_ADDR, ly );
        _process_ly_lyc();

        if( ly == 0 )
        {
            _set_mode( Mode::SEARCHING_OAM_RAM );

            u8 lcdc_stat = m_memory.read_8( LCDC_STAT_ADDR );
            if( ( lcdc_stat & OAM_INT ) != 0 )
            {
                m_cpu.request_interrupt( Interrupts::LCD_STAT );
            }
        }
    }
}

void Display::_update_oam_ram()
{
    if( m_display_cycles >= OAM_MIN_CYCLES )
    {
        m_display_cycles -= OAM_MIN_CYCLES;

        _set_mode( Mode::TRANSFERRING_TO_LCD_DRIVER );
    }
}

void Display::_update_transferring()
{
    if( m_display_cycles >= TRANSFER_MIN_CYCLES )
    {
        m_display_cycles -= TRANSFER_MIN_CYCLES;

        _draw_background_to_frame_buffer();
        _draw_window_to_frame_buffer();
        _draw_sprites_to_frame_buffer();

        _set_mode( Mode::H_BLANK );
    }
}

void Display::_draw_background_to_frame_buffer()
{
}

void Display::_draw_window_to_frame_buffer()
{
}

void Display::_draw_sprites_to_frame_buffer()
{
}
