
#include "display.h"

#include "cpu/cpu.h"
#include "memory/memory_system.h"
#include "options.h"
#include "utils/assert.h"

#include <SDL.h>

Display::Palette const Display::PALE_GREEN_PALETTE = { { 215,245,215 },{ 108,166,108 },{ 30,89,74 },{ 0,19,26 } };
Display::Palette const Display::GREEN_PALETTE = { { 155,188,15 },{ 139,172,15 },{ 48,98,48 },{ 15,56,15 } };
Display::Palette const Display::BW_PALETTE = { { 255,255,255 },{ 0xCC,0xCC,0xCC },{ 0x77,0x77,0x77 },{ 0x0,0x0,0x0 } };

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
    if( ( lcdc & LCDC::DISPLAY_ENABLE ) != 0 )
    {
        m_display_cycles += cycles;
        u8 lcdc_stat = m_memory.read_8( LCDC_STAT_ADDR );
        m_mode = static_cast<Mode>( lcdc_stat & LCDC_STAT::MODE );

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
        //_process_ly_lyc();    // Don't think we need this here...
    }
}

void Display::render()
{
    ASSERT( m_texture && m_renderer );

    SDL_UpdateTexture( m_texture, NULL, m_frame_buffer, SCREEN_WIDTH * sizeof( Colour ) );
    SDL_RenderClear( m_renderer );
    SDL_RenderCopy( m_renderer, m_texture, NULL, NULL );
    SDL_RenderPresent( m_renderer );
}

void Display::_set_mode( Mode new_mode )
{
    u32 new_mode_u32 = static_cast<u32>( new_mode );
    ASSERT_MSG( ( new_mode_u32 & 0xFC ) == 0, 
                "Trying to set an invalid mode [%d], it will be clamped! [%d]", 
                new_mode_u32, new_mode_u32 & 0x03 );

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
    ASSERT_MSG( ( m_memory.read_8( LCD_CONTROL_ADDR ) & LCDC::DISPLAY_ENABLE ) != 0, 
                "LCD display needs to be enabled to compare ly and lyc!. It doesn't make sense to do it." );

    u8 ly = m_memory.read_8( LCDC_Y_ADDR );
    u8 lyc = m_memory.read_8( LY_COMPARE_ADDR );
    u8 lcdc_stat = m_memory.read_8( LCDC_STAT_ADDR );

    if( ly == lyc )
    {
        lcdc_stat |= LCDC_STAT::LY_LYC_CONICIDENCE;
        if( ( lcdc_stat & LCDC_STAT::LYC_INT ) != 0 )
        {
            m_cpu.request_interrupt( Interrupts::LCD_STAT );
        }
    }
    else
    {
        lcdc_stat &= ~LCDC_STAT::LY_LYC_CONICIDENCE;
    }

    m_memory.write( LCDC_STAT_ADDR, lcdc_stat );
}

void Display::_process_lcdc_stat_interrupt( LCDC_STAT const stat_interrupt ) const
{
    u8 lcdc_stat = m_memory.read_8( LCDC_STAT_ADDR );
    if( ( lcdc_stat & stat_interrupt ) != 0 )
    {
        m_cpu.request_interrupt( Interrupts::LCD_STAT );
    }
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
            _process_lcdc_stat_interrupt( LCDC_STAT::V_BLANK_INT );

            //m_display_cycles = 0; // need this?

            m_cpu.request_interrupt( Interrupts::V_BLANK );
        }
        else
        {
            _set_mode( Mode::SEARCHING_OAM_RAM );
            _process_lcdc_stat_interrupt( LCDC_STAT::OAM_INT );
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
            _process_lcdc_stat_interrupt( LCDC_STAT::OAM_INT );
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

        u8 const lcdc = m_memory.read_8( LCD_CONTROL_ADDR );
        if( lcdc & LCDC::BG_DISPLAY )
            _draw_background_to_frame_buffer();

        if( lcdc & LCDC::WINDOW_DISPLAY_ENABLE )
            _draw_window_to_frame_buffer();

        if( lcdc & LCDC::OBJ_DISPLAY_ENABLE )
            _draw_sprites_to_frame_buffer();

        _set_mode( Mode::H_BLANK );
        _process_lcdc_stat_interrupt( LCDC_STAT::H_BLANK_INT );
    }
}

void Display::_draw_background_to_frame_buffer()
{
    // Bear in mind that every operation here is power of 2 so we use shifts.
    u8 const lcdc = m_memory.read_8( LCD_CONTROL_ADDR );
    ASSERT( lcdc & LCDC::DISPLAY_ENABLE );
    ASSERT( lcdc & LCDC::BG_DISPLAY );
    
    u8 const scroll_y = m_memory.read_8( SCROLL_Y_ADDR );
    u8 const scroll_x = m_memory.read_8( SCROLL_X_ADDR );
    u8 const lcd_y = m_memory.read_8( LCDC_Y_ADDR );

    PixelColourIdParams params;
    u8 const y = scroll_y + lcd_y;
    params.y_start_tile = ( y >> 3 ) << 5;
    params.tile_y_offset = ( y % 8 ) << 1;

    params.tile_map_address = ( lcdc & LCDC::BG_TILE_MAP_SELECT ) == 0 ? 0x9800 : 0x9C00;
    params.tile_data_address = ( lcdc & LCDC::BG_N_WINDOW_TILE_DATA ) == 0 ? 0x8800 : 0x8000;
    params.signed_tile_data = ( lcdc & LCDC::BG_N_WINDOW_TILE_DATA ) == 0;

    Palette palette;
    _fill_dmg_palette_for_bg( palette );

    for( u8 i = 0; i < SCREEN_WIDTH; ++i )
    {
        params.x = scroll_x + i;
        u8 colour_id = _get_pixel_colour_id( params );
        u32 const frame_buffer_idx = i + ( lcd_y * SCREEN_WIDTH );
        m_frame_buffer[frame_buffer_idx] = palette[colour_id];
    }
}

void Display::_draw_window_to_frame_buffer()
{
    u8 const lcdc = m_memory.read_8( LCD_CONTROL_ADDR );
    ASSERT( lcdc & LCDC::DISPLAY_ENABLE );
    ASSERT( lcdc & LCDC::WINDOW_DISPLAY_ENABLE );

    u8 const window_y = m_memory.read_8( WINDOW_Y_ADDR );
    u8 const window_x = m_memory.read_8( WINDOW_X_ADDR );
    u8 const lcd_y = m_memory.read_8( LCDC_Y_ADDR );
    if( window_y > lcd_y || window_y > 143 || window_x > 166 )
        return;

    PixelColourIdParams params;

    u8 const y = lcd_y - window_y;
    params.y_start_tile = ( y >> 3 ) << 5;
    params.tile_y_offset = ( y % 8 ) << 1;

    params.tile_map_address = ( lcdc & LCDC::WINDOW_TILE_MAP_SELECT ) == 0 ? 0x9800 : 0x9C00;
    params.tile_data_address = ( lcdc & LCDC::BG_N_WINDOW_TILE_DATA ) == 0 ? 0x8800 : 0x8000;
    params.signed_tile_data = ( lcdc & LCDC::BG_N_WINDOW_TILE_DATA ) == 0;

    Palette palette;
    _fill_dmg_palette_for_bg( palette );

    u8 const x_start = window_x > 6 ? window_x - 7 : 0;
    for( u8 i = x_start; i < SCREEN_WIDTH; ++i )
    {
        params.x = i - x_start;
        u8 const colour_id = _get_pixel_colour_id( params );
        u32 const frame_buffer_idx = i + ( lcd_y * SCREEN_WIDTH );
        m_frame_buffer[frame_buffer_idx] = palette[colour_id];
    }
}

void Display::_draw_sprites_to_frame_buffer()
{
    u8 const lcdc = m_memory.read_8( LCD_CONTROL_ADDR );
    ASSERT( lcdc & LCDC::OBJ_DISPLAY_ENABLE );
    
    (void)lcdc;
}

Display::Palette const& Display::_get_current_palette() const
{
    // TODO: have a palette selector
    return PALE_GREEN_PALETTE;
}

void Display::_fill_dmg_palette_for_bg( Display::Palette& palette ) const
{
    u8 const dmg_palette = m_memory.read_8( BG_PALETTE_ADDR );
    Palette const& current_bg_palette = _get_current_palette();
    palette[0] = current_bg_palette[dmg_palette & PALETTE::COLOUR_0];
    palette[1] = current_bg_palette[( dmg_palette & PALETTE::COLOUR_1 ) >> 2];
    palette[2] = current_bg_palette[( dmg_palette & PALETTE::COLOUR_2 ) >> 4];
    palette[3] = current_bg_palette[( dmg_palette & PALETTE::COLOUR_3 ) >> 6];
}

u8 Display::_get_pixel_colour_id( PixelColourIdParams const& params ) const
{
    u8 const x_tile = params.x >> 3;
    u16 const map_id = params.y_start_tile + x_tile;
    ASSERT( map_id < 1024 );

    u16 const tile_address = params.tile_map_address + map_id;
    u8 const tile_data_id = params.signed_tile_data
                        ? static_cast<u8>( static_cast<s16>( m_memory.read_8( tile_address ) ) + 128 )
                        : m_memory.read_8( tile_address );

    word const tile_data = { m_memory.read_16( params.tile_data_address + ( tile_data_id << 4 ) + params.tile_y_offset ) };
    s32 const pixel_in_tile = ( ( params.x % 8 ) - 7 ) * -1; // Get the pixel and mirror the byte.
    u8 colour_id = ( ( tile_data.lo >> pixel_in_tile ) & 1 ) << 1;
    colour_id |= ( tile_data.hi >> pixel_in_tile ) & 1;

    return colour_id;
}
