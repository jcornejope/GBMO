#pragma once

#include "utils/types.h"
#include "options.h"

class MemorySystem;
class CPU;

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;

class Display
{
    enum class Mode : u8
    {
        H_BLANK = 0,
        V_BLANK,
        SEARCHING_OAM_RAM,
        TRANSFERRING_TO_LCD_DRIVER
    };

    enum LCDC : u8
    {
        BG_DISPLAY              = 1,        // Bit 0 - BG Display ( 0 = Off, 1 = On )
        OBJ_DISPLAY_ENABLE      = 1 << 1,   // Bit 1 - OBJ (Sprite) Display Enable ( 0 = Off, 1 = On )
        OBJ_SIZE                = 1 << 2,   // Bit 2 - OBJ( Sprite ) Size( 0 = 8x8, 1 = 8x16 )
        BG_TILE_MAP_SELECT      = 1 << 3,   // Bit 3 - BG Tile Map Display Select( 0 = 9800 - 9BFF, 1 = 9C00 - 9FFF )
        BG_N_WINDOW_TILE_DATA   = 1 << 4,   // Bit 4 - BG & Window Tile Data Select( 0 = 8800 - 97FF, 1 = 8000 - 8FFF )
        WINDOW_DISPLAY_ENABLE   = 1 << 5,   // Bit 5 - Window Display Enable( 0 = Off, 1 = On )
        WINDOW_TILE_MAP_SELECT  = 1 << 6,   // Bit 6 - Window Tile Map Display Select( 0 = 9800 - 9BFF, 1 = 9C00 - 9FFF )        
        DISPLAY_ENABLE          = 1 << 7    // Bit 7 - LCD Display Enable ( 0 = Off, 1 = On )
    };

    enum LCDC_STAT : u8
    {
        LYC_INT             = 1 << 6,   // Bit 6 - LYC = LY Coincidence Interrupt( 1 = Enable ) ( Read / Write )
        OAM_INT             = 1 << 5,   // Bit 5 - Mode 2 OAM Interrupt( 1 = Enable ) ( Read / Write )
        V_BLANK_INT         = 1 << 4,   // Bit 4 - Mode 1 V - Blank Interrupt( 1 = Enable ) ( Read / Write )
        H_BLANK_INT         = 1 << 3,   // Bit 3 - Mode 0 H - Blank Interrupt( 1 = Enable ) ( Read / Write )
        LY_LYC_CONICIDENCE  = 1 << 2,   // Bit 2 - Coincidence Flag( 0:LYC<>LY, 1 : LYC = LY ) ( Read Only )
        MODE                = 0x03      // Bit 1 - 0 - Mode Flag( Mode 0 - 3 ) ( Read Only )
    };

    enum PALETTE : u8
    {
        COLOUR_3 = 0x03 << 6,   // Bit 7 - 6 - Shade for Color Number 3
        COLOUR_2 = 0x03 << 4,   // Bit 5 - 4 - Shade for Color Number 2
        COLOUR_1 = 0x03 << 2,   // Bit 3 - 2 - Shade for Color Number 1
        COLOUR_0 = 0x03         // Bit 1 - 0 - Shade for Color Number 0
    };

    enum DMG_PALETTE_COLOURS : u8
    {
        WHITE       = 0,
        LIGHT_GREY  = 1,
        DARK_GREY   = 2,
        BLACK       = 3
    };

    // TODO: This would be probably better if is aligned to 32...
    struct Colour
    {
        bool operator==( Colour const& c ) { return r == c.r && g == c.g && b == c.b; }
        bool operator!=( Colour const& c ) { return !( *this == c ); }

        u8 r;
        u8 g;
        u8 b;
    };

    enum SPRITE_ATTR_FLAGS : u8
    {
        OBJ_BG_PRIORITY = 1 << 7,   // Bit7   OBJ - to - BG Priority( 0 = OBJ Above BG, 1 = OBJ Behind BG color 1 - 3 )
                                    // ( Used for both BG and Window.BG color 0 is always behind OBJ )
        Y_FLIP          = 1 << 6,   // Bit6   Y flip( 0 = Normal, 1 = Vertically mirrored )
        X_FLIP          = 1 << 5,   // Bit5   X flip( 0 = Normal, 1 = Horizontally mirrored )
        PALETTE         = 1 << 4,   // Bit4   Palette number  **Non CGB Mode Only** ( 0 = OBP0, 1 = OBP1 )
        TILE_BANK       = 1 << 3,   // Bit3   Tile VRAM - Bank * *CGB Mode Only** ( 0 = Bank 0, 1 = Bank 1 )
        CGB_PALETTE     = 0x03      // Bit2 - 0 Palette number  **CGB Mode Only** ( OBP0 - 7 )
    };

    struct Sprite
    {
        u8 y_pos;
        u8 x_pos;
        u8 tile_num;
        u8 attributes;
    };

    enum WINDOW_MODE : u8
    {
        USE_OPTIONS, 

        WINDOWED_1x,
        WINDOWED_3x,
        WINDOWED_5x,
        FULLSCREEN,
        FULLSCREEN_STRETCHED,

        NUM_MODES,
        FIRST_WINDOW_MODE = USE_OPTIONS
    };

    static u32 const SCREEN_WIDTH   = 160;
    static u32 const SCREEN_HEIGHT  = 144;
    static u32 const FRAMEBUFFER_SIZE = SCREEN_WIDTH * SCREEN_HEIGHT;

    // Using average value for now...
    static u32 const H_BLANK_MIN_CYCLES     = 204;  // 201 - 207
    static u32 const OAM_MIN_CYCLES         = 80;   //  77 -  83
    static u32 const TRANSFER_MIN_CYCLES    = 172;  // 169 - 175
    static u32 const CYCLES_TO_LY_INCREMENT = 456;
    static u32 const V_BLANK_CYCLES         = 4560;

public:
    static u32 const NUM_SYSTEM_PALETTES = 3;

    Display( CPU& cpu, MemorySystem& memory );
    ~Display();

    bool init( Options const& options );
    void update( u32 cycles );
    void render();
    
    bool is_ready_for_render() const { return m_ready_for_render; }
    void cycle_window_mode();
    void cycle_palette();

private:
    typedef Colour Palette[4];
    static Palette const PALETTES[NUM_SYSTEM_PALETTES];

    void _set_mode( Mode new_mode );
    void _process_ly_lyc();
    void _process_lcdc_stat_interrupt( LCDC_STAT const stat_interrupt ) const;

    // Mode update
    void _update_h_blank();
    void _update_v_blank();
    void _update_oam_ram();
    void _update_transferring();

    // Draw to the current scanline in the frame buffer
    void _draw_background_to_frame_buffer();
    void _draw_window_to_frame_buffer();
    void _draw_sprites_to_frame_buffer();

    Palette const& _get_current_palette() const;
    void _fill_palette( Palette& palette, u16 definition_address ) const;

    bool _initialize_display( DisplayOptions const& options );

    struct PixelColourIdParams
    {
        u16 tile_map_address;
        u16 tile_data_address;
        u16 y_start_tile;
        u8 tile_y_offset;
        u8 x;
        bool signed_tile_data;
    };
    FORCE_INLINE u8 _get_pixel_colour_id( PixelColourIdParams const& params ) const;

    MemorySystem& m_memory;
    CPU& m_cpu;

    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    SDL_Texture* m_texture;

    Colour m_frame_buffer[FRAMEBUFFER_SIZE];

    Mode m_mode;
    WINDOW_MODE m_window_mode;
    DisplayOptions m_startup_display_options;

    u32 m_display_cycles;
    u32 m_current_palette_idx;

    bool m_ready_for_render;
};
