#pragma once

#include "cartridge\cartridge.h"
#include "cpu\cpu.h"
#include "joypad\joypad.h"
#include "memory\memory_system.h"
#include "display\display.h"

#include <SDL_events.h>

struct Options;

class GBMO
{
public:
    GBMO( Options const& options );

    bool init();
    void deinit();
    bool update();
    bool handle_events();

    Cartridge& get_cartridge() { return m_cartridge;  }
    MemorySystem& get_memory_system() { return m_memory_system; }
    CPU& get_cpu() { return m_cpu; }
    Joypad& get_joypad() { return m_joypad; }
    Display& get_display() { return m_display; }

private:
    Cartridge m_cartridge;
    MemorySystem m_memory_system;
    CPU m_cpu;
    Joypad m_joypad;
    Display m_display;

    SDL_Event m_event;
};
