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
    if( SDL_Init( SDL_INIT_VIDEO ) != 0 )
    {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    //int i = 0;
    //int f = 10;
    //std::function<int( int )> v = std::bind( foo, i++ );
    //v(f);
    //(this->v());
    //std::cout << i << std::endl;

    Options options;
    options.m_rom_path = "D:\\Dev\\GBMO\\rom_sml.gb";
    GBMO emulator(options);

    getchar();

    SDL_Quit();
    return 0;
}
