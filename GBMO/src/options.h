#pragma once

#include "utils/types.h"

#include <SDL_keycode.h>
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

namespace
{
    InputsConfig const default_inputs = { SDLK_RIGHT, SDLK_LEFT, SDLK_UP, SDLK_DOWN, SDLK_x, SDLK_z, SDLK_RSHIFT, SDLK_RETURN };
};

struct Options
{
    Options() 
        : m_log_path( ".\\log.txt" )
        , m_palette_index( 0 )
        , m_resolution_scale ( 1 )
        , m_init_pos_x( -1 )
        , m_init_pos_y( -1 )
        , m_volume( 0.f )
        , m_fullscreen( false )
        , m_fullscreen_keep_aspect_ratio( false )
    {
        std::memcpy( m_inputs, default_inputs, sizeof( InputBind ) * Inputs::NUM_INPUTS );
    }

    std::string m_rom_path;
    std::string m_log_path;

    InputsConfig m_inputs;
    u32 m_palette_index;
    u32 m_resolution_scale;
    s32 m_init_pos_x;
    s32 m_init_pos_y;
    float m_volume;
    bool m_fullscreen;
    bool m_fullscreen_keep_aspect_ratio;
};
