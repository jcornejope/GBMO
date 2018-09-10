#include <iostream>
#include <SDL.h>

#include "gbmo.h"
#include "options.h"

int foo(int param)
{
    std::cout << param << std::endl;

    return 3;
}

int main( int argc, char* argv[] )
{
    (void)argc;
    (void)argv;

    if( SDL_Init( SDL_INIT_VIDEO ) != 0 )
    {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = 0;
    window = SDL_CreateWindow( "GBMO v0.1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 160, 144, SDL_WINDOW_SHOWN );
    //SDL_Renderer* renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    SDL_Event events;

    Options options;
    options.m_rom_path = "D:\\Dev\\GBMO\\rom_t.gb";
    GBMO emulator(options);

    bool emulator_running = true;
    while( emulator_running )
    {
        // Check for user KB quit.
        SDL_PumpEvents();
        while( SDL_PollEvent( &events ) ) 
        {
            if( ( events.type == SDL_QUIT ) ||
                ( events.type == SDL_KEYDOWN && events.key.keysym.sym == SDLK_ESCAPE ) )
            {
                emulator_running = false;
            }
        }

        // Run the emulator
        emulator.update();
    }

    SDL_Quit();
    return 0;
}
