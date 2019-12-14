#include "input.h"

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
