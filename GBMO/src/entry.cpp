
#include <SDL.h>

#include <iostream>

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
    options.m_rom_path = "D:\\Dev\\GBMO\\rom_ai.gb";
    //options.m_rom_path = "D:\\Dev\\GBMO\\rom_sml.gb";
    //options.m_rom_path = "D:\\Dev\\GBMO\\rom_drm.gb";
    //options.m_rom_path = "D:\\Dev\\GBMO\\rom_z.gb";
    //options.m_rom_path = "D:\\Dev\\GBMO\\bgbtest.gb";
    //options.m_rom_path = "D:\\Dev\\GBMO\\Blargg-gb-tests\\cpu_instrs\\cpu_instrs\\cpu_instrs.gb";
    //options.m_rom_path = "D:\\Dev\\GBMO\\Blargg-gb-tests\\cpu_instrs\\cpu_instrs\\individual\\01-special.gb";
    //options.m_rom_path = "D:\\Dev\\GBMO\\Blargg-gb-tests\\cpu_instrs\\cpu_instrs\\individual\\02-interrupts.gb";
    //options.m_rom_path = "D:\\Dev\\GBMO\\Blargg-gb-tests\\cpu_instrs\\cpu_instrs\\individual\\03-op sp,hl.gb";
    //options.m_rom_path = "D:\\Dev\\GBMO\\Blargg-gb-tests\\cpu_instrs\\cpu_instrs\\individual\\04-op r,imm.gb";
    //options.m_rom_path = "D:\\Dev\\GBMO\\Blargg-gb-tests\\cpu_instrs\\cpu_instrs\\individual\\05-op rp.gb";
    //options.m_rom_path = "D:\\Dev\\GBMO\\Blargg-gb-tests\\cpu_instrs\\cpu_instrs\\individual\\06-ld r,r.gb";
    //options.m_rom_path = "D:\\Dev\\GBMO\\Blargg-gb-tests\\cpu_instrs\\cpu_instrs\\individual\\07-jr,jp,call,ret,rst.gb";
    //options.m_rom_path = "D:\\Dev\\GBMO\\Blargg-gb-tests\\cpu_instrs\\cpu_instrs\\individual\\08-misc instrs.gb";
    //options.m_rom_path = "D:\\Dev\\GBMO\\Blargg-gb-tests\\cpu_instrs\\cpu_instrs\\individual\\09-op r,r.gb";
    //options.m_rom_path = "D:\\Dev\\GBMO\\Blargg-gb-tests\\cpu_instrs\\cpu_instrs\\individual\\10-bit ops.gb";
    //options.m_rom_path = "D:\\Dev\\GBMO\\Blargg-gb-tests\\cpu_instrs\\cpu_instrs\\individual\\11-op a,(hl).gb";
    //options.m_rom_path = "D:\\Dev\\GBMO\\Blargg-gb-tests\\interrupt_time\\interrupt_time\\interrupt_time.gb";

    GBMO emulator(options);

    emulator.init();
    emulator.get_display().init( options );

    bool emulator_running = true;
    while( emulator_running )
    {
        emulator_running = emulator.update();
        Logger::instance().flush();
    }

    emulator.deinit();

    Logger::destroy_instance();

    return 0;
}
