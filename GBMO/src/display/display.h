#pragma once

class MemorySystem;
struct Options;

struct SDL_Window;
struct SDL_Renderer;

class Display
{
    enum class Mode
    {
        H_BLANK = 0,
        V_BLANK,
        SEARCHING_OAM_RAM,
        TRANSFERRING_TO_LCD_DRIVER
    };

public:
    Display( MemorySystem& memory );

    bool init( Options const& options );
    void update();
    void render();

private:
    MemorySystem& m_memory;

    SDL_Window* m_window;
    SDL_Renderer* m_renderer;

    Mode m_mode;
};
