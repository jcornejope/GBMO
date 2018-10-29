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
    u8 get_inputs_for_memory( u8 joyp );

    void set_input_bindings( InputsConfig const& new_inputs );

private:
    bool _are_buttons_enabled( u8 const joyp ) const    { return ( joyp & ( 1 << 5 ) ) == 0; }
    bool _are_directions_enabled( u8 const joyp ) const { return ( joyp & ( 1 << 4 ) ) == 0; }

    CPU& m_cpu;
    MemorySystem& m_memory;

    InputsConfig m_inputs;
    u8 m_input_flags;
};
