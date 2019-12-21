
#include "input.h"
#include "assert.h"

#include <cstring>

namespace
{
    struct AxisInputsNames
    { 
        char const* name; 
        char const* alias; 
    };

    AxisInputsNames const AXIS_INPUT_NAMES[] = { { "L_STICK_Y_NEG", "L_STICK_UP" },
                                                 { "L_STICK_Y_POS", "L_STICK_DOWN" },
                                                 { "L_STICK_X_NEG", "L_STICK_LEFT" },
                                                 { "L_STICK_X_POS", "L_STICK_RIGHT" },
                                                 { "R_STICK_Y_NEG", "R_STICK_UP" },
                                                 { "R_STICK_Y_POS", "R_STICK_DOWN" },
                                                 { "R_STICK_X_NEG", "R_STICK_LEFT" },
                                                 { "R_STICK_X_POS", "R_STICK_RIGHT" },
                                                 { "L_TRIGGER_POS", "L_TRIGGER" },
                                                 { "R_TRIGGER_POS", "R_TRIGGER" } };

    // We need this to distinguish button literals (a,b,x and y) from the keys.
    struct FaceButtonTranslation
    {
        char const* name;
        SDL_GameControllerButton button;
    };
    u32 const NUM_FACE_BUTTONS = 4;
    FaceButtonTranslation FACE_BUTTON_TRANSLATION_TABLE[NUM_FACE_BUTTONS] = { { "ba", SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_A },
                                                                              { "bb", SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_B }, 
                                                                              { "by", SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_Y }, 
                                                                              { "bx", SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_Y } };
}

void translate_from_axis_input( AxisInputs axis_input, SDL_GameControllerAxis& sdl_axis, s32& sign )
{
    switch( axis_input )
    {
    case AxisInputs::L_STICK_Y_NEG: sign = -1;  sdl_axis = SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY;           break;
    case AxisInputs::L_STICK_Y_POS: sign = 1;   sdl_axis = SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY;           break;
    case AxisInputs::L_STICK_X_NEG: sign = -1;  sdl_axis = SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX;           break;
    case AxisInputs::L_STICK_X_POS: sign = 1;   sdl_axis = SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX;           break;

    case AxisInputs::R_STICK_Y_NEG: sign = -1;  sdl_axis = SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTY;          break;
    case AxisInputs::R_STICK_Y_POS: sign = 1;   sdl_axis = SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTY;          break;
    case AxisInputs::R_STICK_X_NEG: sign = -1;  sdl_axis = SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTX;          break;
    case AxisInputs::R_STICK_X_POS: sign = 1;   sdl_axis = SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTX;          break;

    case AxisInputs::L_TRIGGER:     sign = 1;   sdl_axis = SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_TRIGGERLEFT;     break;
    case AxisInputs::R_TRIGGER:     sign = 1;   sdl_axis = SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_TRIGGERRIGHT;    break;
    }
}

char const* get_axis_input_name( AxisInputs axis_input )
{
    ASSERT( axis_input < AxisInputs::NUM_AXIS_INPUTS );
    return AXIS_INPUT_NAMES[axis_input].name;
}

char const* get_axis_input_alias( AxisInputs axis_input )
{
    ASSERT( axis_input < AxisInputs::NUM_AXIS_INPUTS );
    return AXIS_INPUT_NAMES[axis_input].alias;
}

AxisInputs get_axis_input_from_string( const char* axis_input_name )
{
    // would be nice and faster to have this strings as hash names instead. Not big deal as is only while loading settings
    for( u32 i = 0; i < AxisInputs::NUM_AXIS_INPUTS; ++i )
    {
        if( ( strcmp( axis_input_name, AXIS_INPUT_NAMES[i].name ) == 0 ) ||
            ( strcmp( axis_input_name, AXIS_INPUT_NAMES[i].alias ) == 0 ) )
        {
            return static_cast<AxisInputs>( i );
        }
    }

    return AxisInputs::INVALID;
}

SDL_GameControllerButton get_controller_button_from_string( const char* button_name )
{
    for( u32 i = 0; i < NUM_FACE_BUTTONS; ++i )
        if( strcmp( button_name, FACE_BUTTON_TRANSLATION_TABLE[i].name ) == 0 )
            return FACE_BUTTON_TRANSLATION_TABLE[i].button;

    return SDL_GameControllerGetButtonFromString( button_name );
}
