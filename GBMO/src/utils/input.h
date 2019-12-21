#pragma once

#include "utils/types.h"

#include <SDL_keycode.h>
#include <SDL_gamecontroller.h>

enum Inputs
{
    RIGHT = 0,
    LEFT,
    UP,
    DOWN,
    A,
    B,
    SELECT,
    START,

    NUM_INPUTS,

    DIRECTIONS_END = DOWN,
    BUTTONS_START = A,
};

enum AxisInputs
{
    L_STICK_Y_POS,
    L_STICK_Y_NEG,
    L_STICK_X_POS,
    L_STICK_X_NEG,
                 
    R_STICK_Y_POS,
    R_STICK_Y_NEG,
    R_STICK_X_POS,
    R_STICK_X_NEG,

    L_TRIGGER_POS,
    R_TRIGGER_POS,

    NUM_AXIS_INPUTS,

    // Alias
    L_STICK_DOWN    = L_STICK_Y_POS,
    L_STICK_UP      = L_STICK_Y_NEG,
    L_STICK_RIGHT   = L_STICK_X_POS,
    L_STICK_LEFT    = L_STICK_X_NEG,

    R_STICK_DOWN    = R_STICK_Y_POS,
    R_STICK_UP      = R_STICK_Y_NEG,
    R_STICK_RIGHT   = R_STICK_X_POS,
    R_STICK_LEFT    = R_STICK_X_NEG,

    L_TRIGGER       = L_TRIGGER_POS,
    R_TRIGGER       = R_TRIGGER_POS,

    INVALID         = NUM_AXIS_INPUTS
};

union InputBindElem
{
    SDL_Keycode key_code;
    AxisInputs controller_axis;
    SDL_GameControllerButton controller_button;
};

enum class InputBindType : u8
{
    KEY,
    AXIS,
    BUTTON,

    INVALID
};

struct InputBind
{
    InputBind() : m_input_bind{ 0 }, m_type{ InputBindType::INVALID } {}
    InputBind( SDL_Keycode const key ) : m_input_bind{ key }, m_type{ InputBindType::KEY } {};
    InputBind( AxisInputs const axis ) : m_type{ InputBindType::AXIS } { m_input_bind.controller_axis = axis; };
    InputBind( SDL_GameControllerButton const button ) : m_type{ InputBindType::BUTTON } { m_input_bind.controller_button = button; };

    InputBindElem m_input_bind;
    InputBindType m_type;
};

void translate_from_axis_input( AxisInputs axis_input, SDL_GameControllerAxis& sdl_axis, s32& sign );
char const* get_axis_input_name( AxisInputs axis_input );
char const* get_axis_input_alias( AxisInputs axis_input );
AxisInputs get_axis_input_from_string( char const* axis_input );

SDL_GameControllerButton get_controller_button_from_string( const char* button_name );

typedef InputBind InputBind_T;
typedef InputBind_T InputsConfig[Inputs::NUM_INPUTS];
