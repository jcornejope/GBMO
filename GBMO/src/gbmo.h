#pragma once

#include "cartridge\cartridge.h"
#include "cpu\cpu.h"
#include "joypad\joypad.h"
#include "memory\memory_system.h"

#include <SDL_events.h>

struct Options;

class GBMO
{
public:
    GBMO( Options const& options );

    bool update();
    void handle_input_event( SDL_Event& event );

private:
    Cartridge m_cartridge;
    MemorySystem m_memory_system;
    CPU m_cpu;
    Joypad m_joypad;
};
