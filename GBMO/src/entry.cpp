
#include <SDL.h>

#include "gbmo.h"
#include "options.h"
#include "utils/logger.h"

int main( int argc, char* argv[] )
{
    // TODO: SUPPORT args
    (void)argc;
    (void)argv;

    Logger::create_instance( ".\\log.txt" );

    Options options;
    options.m_rom_path = "..\\..\\roms\\rom_b_cpu_instrs.gb";

    GBMO emulator(options);

    bool emulator_running = emulator.init();
    emulator_running &= emulator.get_display().init( options );

    while( emulator_running )
    {
        emulator_running = emulator.update();
        Logger::instance().flush();
    }

    emulator.deinit();

    Logger::destroy_instance();

    return 0;
}
