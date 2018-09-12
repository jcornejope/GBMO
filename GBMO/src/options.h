#pragma once

#include "utils/types.h"
#include <string>
//#include <variant>

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
};

//typedef std::variant<SDL_Keycode, SDL_GameControllerAxis, SDL_GameControllerButton> InputBind;
//union InputBind
//{ 
//    SDL_Keycode key_code; 
//    SDL_GameControllerAxis controller_axis; 
//    SDL_GameControllerButton controller_button; 
//};

// TODO: Support controller
typedef SDL_Keycode InputBind;

typedef InputBind InputsConfig[Inputs::NUM_INPUTS];

static InputsConfig const default_inputs = { SDLK_RIGHT, SDLK_LEFT, SDLK_UP, SDLK_DOWN, SDLK_z, SDLK_x, SDLK_LSHIFT, SDLK_RETURN };

struct Options
{
    Options() 
        : m_resolution_scale ( 1 ) 
        , m_volume( 0.f )
        , m_log( true )
    {
        std::memcpy( m_inputs, default_inputs, Inputs::NUM_INPUTS );
    }

    std::string m_rom_path;

    InputsConfig m_inputs;
    u32 m_resolution_scale;
    float m_volume;
    bool m_log;
};
