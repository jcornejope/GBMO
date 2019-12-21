#pragma once

#include "utils/input.h"

#include <SDL_events.h>
#include <SDL_joystick.h>
#include <SDL_gamecontroller.h>

class CPU;
class MemorySystem;

class Joypad
{
public:
    Joypad( CPU& cpu, MemorySystem& memory );

    void init();
    void deinit();

    bool wants_to_handle_input_event( u32 event_type ) const;
    void handle_input_event( SDL_Event& event );
    u8 get_inputs_for_memory( u8 joyp );

    void set_input_bindings( InputsConfig const& new_inputs, u16 const controller_dead_zone );

private:
    bool _are_buttons_enabled( u8 const joyp ) const    { return ( joyp & ( 1 << 5 ) ) == 0; }
    bool _are_directions_enabled( u8 const joyp ) const { return ( joyp & ( 1 << 4 ) ) == 0; }

    bool _handle_input_flag( bool const pressed, u32 const bit_index, u8 const joyp );

    CPU& m_cpu;
    MemorySystem& m_memory;

    SDL_GameController* m_game_controller;
    SDL_JoystickID m_joystick_id;

    InputsConfig m_inputs;
    u16 m_controller_dead_zone;
    u8 m_input_flags;
};
