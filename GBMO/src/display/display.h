#pragma once

#include "utils/types.h"

class MemorySystem;
class CPU;
struct Options;

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;

struct Pixel
{
    u8 r;
    u8 g;
    u8 b;
};

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
        BG_DISPLAY              = 0,        // Bit 0 - BG Display ( 0 = Off, 1 = On )
        OBJ_DISPLAY_ENABLE      = 1,        // Bit 1 - OBJ (Sprite) Display Enable ( 0 = Off, 1 = On )
        OBJ_SIZE                = 1 << 1,   // Bit 2 - OBJ( Sprite ) Size( 0 = 8x8, 1 = 8x16 )
        BG_TILE_MAP_SELECT      = 1 << 2,   // Bit 3 - BG Tile Map Display Select( 0 = 9800 - 9BFF, 1 = 9C00 - 9FFF )
        BG_N_WINDOW_TILE_DATA   = 1 << 3,   // Bit 4 - BG & Window Tile Data Select( 0 = 8800 - 97FF, 1 = 8000 - 8FFF )
        WINDOW_DISPLAY_ENABLE   = 1 << 4,   // Bit 5 - Window Display Enable( 0 = Off, 1 = On )
        WINDOW_TILE_MAP_SELECT  = 1 << 5,   // Bit 6 - Window Tile Map Display Select( 0 = 9800 - 9BFF, 1 = 9C00 - 9FFF )        
        DISPLAY_ENABLE          = 1 << 6    // Bit 7 - LCD Display Enable ( 0 = Off, 1 = On )
    };

    enum LCDC_STAT : u8
    {
        LYC_INT             = 1 << 5,   // Bit 6 - LYC = LY Coincidence Interrupt( 1 = Enable ) ( Read / Write )
        OAM_INT             = 1 << 4,   // Bit 5 - Mode 2 OAM Interrupt( 1 = Enable ) ( Read / Write )
        V_BLANK_INT         = 1 << 3,   // Bit 4 - Mode 1 V - Blank Interrupt( 1 = Enable ) ( Read / Write )
        H_BLANK_INT         = 1 << 2,   // Bit 3 - Mode 0 H - Blank Interrupt( 1 = Enable ) ( Read / Write )
        LY_LYC_CONICIDENCE  = 1,        // Bit 2 - Coincidence Flag( 0:LYC<>LY, 1 : LYC = LY ) ( Read Only )
        MODE                = 0x03      // Bit 1 - 0 - Mode Flag( Mode 0 - 3 ) ( Read Only )
    };

    static u32 const SCREEN_WIDTH   = 160;
    static u32 const SCREEN_HEIGHT  = 144;

    // Using average value for now...
    static u32 const H_BLANK_MIN_CYCLES     = 204;  // 201 - 207
    static u32 const OAM_MIN_CYCLES         = 80;   //  77 -  83
    static u32 const TRANSFER_MIN_CYCLES    = 172;  // 169 - 175
    static u32 const CYCLES_TO_LY_INCREMENT = 456;
    static u32 const V_BLANK_CYCLES         = 4560;

public:
    Display( CPU& cpu, MemorySystem& memory );
    ~Display();

    bool init( Options const& options );
    void update( u32 cycles );
    void render();

private:
    void _set_mode( Mode new_mode );
    void _process_ly_lyc();
    
    // Mode update
    void _update_h_blank();
    void _update_v_blank();
    void _update_oam_ram();
    void _update_transferring();

    // Draw to the current scanline in the frame buffer
    void _draw_background_to_frame_buffer();
    void _draw_window_to_frame_buffer();
    void _draw_sprites_to_frame_buffer();

    MemorySystem& m_memory;
    CPU& m_cpu;

    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    SDL_Texture* m_texture;

    Pixel m_frame_buffer[SCREEN_WIDTH * SCREEN_HEIGHT];

    Mode m_mode;

    u32 m_display_cycles;
};
