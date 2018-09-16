#include <iostream>

#include "gbmo.h"
#include "options.h"

int main( int argc, char* argv[] )
{
    // TODO: SUPPORT args
    (void)argc;
    (void)argv;

    Options options;
    options.m_rom_path = "D:\\Dev\\GBMO\\rom_t.gb";
    GBMO emulator(options);

    emulator.init();
    emulator.get_display().init( options );

    bool emulator_running = true;
    while( emulator_running )
    {
        emulator_running = emulator.update();
    }

    emulator.deinit();

    return 0;
}
