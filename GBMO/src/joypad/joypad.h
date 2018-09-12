#pragma once

#include <SDL_events.h>
#include <string>

#include "options.h"

class CPU;
class MemorySystem;

class Joypad
{
public:
    Joypad( CPU& cpu, MemorySystem& memory );

    void handle_input_event( SDL_Event& event );
    void set_inputs_on_memory();

    void set_input_bindings( InputsConfig const& new_inputs );

private:
    CPU& m_cpu;
    MemorySystem& m_memory;

    InputsConfig m_inputs;
    u8 m_input_flags;
};
