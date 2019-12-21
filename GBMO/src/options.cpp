
#include "options.h"

#include <INIReader.h>
#include <SDL.h>

#include <fstream>

namespace
{
    char const* DEFAULT_SETTINGS_FILE = ".\\settings.ini";

    char const* OPTIONS_SECTION = "options";
    char const* CONTROLS_SECTION = "controls";
    char const* MISC_SECTION = "misc";

    char const* VOLUME_ATTR = "volume";
    char const* PALETTE_IDX_ATTR = "palette";
    char const* RESOLUTION_SCALE_ATTR = "scale_mult";
    char const* INIT_POS_X_ATTR = "initial_pos_x";
    char const* INIT_POS_Y_ATTR = "initial_pos_y";
    char const* FULLSCREEN_ATTR = "fullscreen";
    char const* KEEP_ASPECT_RATIO_ATTR = "keep_aspect_ratio";

    char const* ZIP_MASTER_PASSWORD = "zip_master_password";
    char const* RAM_SAVE_ENABLED = "ram_save_load_enabled";

    char const* GAME_CONTROLLER_DEAD_ZONE = "game_controller_dead_zone";
    char const* INPUT_ATTR[Inputs::NUM_INPUTS] = { "right",
                                                   "left",
                                                   "up",
                                                   "down",
                                                   "a",
                                                   "b",
                                                   "select",
                                                   "start"};
}

bool Options::load_from_file()
{
    return load_from_file( DEFAULT_SETTINGS_FILE );
}

bool Options::load_from_file( char const* file_name )
{
    // NOTE: I'm not totally sold on this lib. It creates std::string everywhere just because.
    // TODO: Evaluate refactoring it to use <char const*> instead. Is not in a critical path so it will do for now.
    INIReader reader( file_name );
    if( reader.ParseError() )
        return false;

    Options def;
    m_volume = reader.GetFloat( OPTIONS_SECTION, VOLUME_ATTR, def.m_volume );
    m_display_options.m_palette_index = reader.GetInteger( OPTIONS_SECTION, PALETTE_IDX_ATTR, def.m_display_options.m_palette_index );
    m_display_options.m_resolution_scale = reader.GetInteger( OPTIONS_SECTION, RESOLUTION_SCALE_ATTR, def.m_display_options.m_resolution_scale );
    m_display_options.m_init_pos_x = reader.GetInteger( OPTIONS_SECTION, INIT_POS_X_ATTR, def.m_display_options.m_init_pos_x );
    m_display_options.m_init_pos_y = reader.GetInteger( OPTIONS_SECTION, INIT_POS_Y_ATTR, def.m_display_options.m_init_pos_y );
    m_display_options.m_fullscreen = reader.GetBoolean( OPTIONS_SECTION, FULLSCREEN_ATTR, def.m_display_options.m_fullscreen );
    m_display_options.m_fullscreen_keep_aspect_ratio = reader.GetBoolean( OPTIONS_SECTION, KEEP_ASPECT_RATIO_ATTR, def.m_display_options.m_fullscreen_keep_aspect_ratio );

    for( int input = 0; input < Inputs::NUM_INPUTS; ++input )
    {
        std::string const input_name = reader.Get( CONTROLS_SECTION, INPUT_ATTR[input], SDL_GetKeyName( def.m_inputs[input].m_input_bind.key_code ) );

        m_inputs[input] = SDL_GetKeyFromName( input_name.c_str() );
        if( m_inputs[input].m_input_bind.key_code == SDLK_UNKNOWN )
        {
            m_inputs[input] = get_axis_input_from_string( input_name.c_str() );
            if( m_inputs[input].m_input_bind.controller_axis == AxisInputs::INVALID )
            {
                m_inputs[input] = get_controller_button_from_string( input_name.c_str() );
                if( m_inputs[input].m_input_bind.controller_button == SDL_CONTROLLER_BUTTON_INVALID )
                {
                    m_inputs[input] = def.m_inputs[input].m_input_bind.key_code;
                }
            }
        }
    }
    m_controller_dead_zone = static_cast<u16>( abs( reader.GetInteger( CONTROLS_SECTION, GAME_CONTROLLER_DEAD_ZONE, def.m_controller_dead_zone ) ) );

    m_zip_password = reader.Get( MISC_SECTION, ZIP_MASTER_PASSWORD, def.m_zip_password );
    m_ram_save_enabled = reader.GetBoolean( MISC_SECTION, RAM_SAVE_ENABLED, def.m_ram_save_enabled );

    if( reader.ParseError() )
        return false;

    return true;
}

bool Options::save_to_file() const
{
    return save_to_file( DEFAULT_SETTINGS_FILE );
}

bool Options::save_to_file( const char* file_path ) const
{
    return _save_options( file_path, *this );
}

bool Options::save_default()
{
    return save_default( DEFAULT_SETTINGS_FILE );
}

bool Options::save_default( const char* file_path )
{
    return _save_options( file_path, Options{} );
}

bool Options::_save_options( char const* file_path, Options const& options )
{
    std::ofstream file( file_path, std::ios::out | std::ios::trunc );
    if( !file.is_open() )
        return false;

    file << ";" << std::endl;
    file << "; GBMO config file" << std::endl;
    file << ";" << std::endl;
    file << std::endl;

    file << "[" << OPTIONS_SECTION << "]" << std::endl;
    file << PALETTE_IDX_ATTR << " = " << options.m_display_options.m_palette_index;
    file << "\t\t\t\t\t; 0:PALE_GREEN, 1:GREEN, 2:B/W" << std::endl;
    file << RESOLUTION_SCALE_ATTR << " = " << options.m_display_options.m_resolution_scale;
    file << "\t\t\t\t; Resolution X and Y multiplier" << std::endl;
    file << INIT_POS_X_ATTR << " = " << options.m_display_options.m_init_pos_x;
    file << "\t\t\t; top-left corner horizontal position in pixels. -1 will let the system decide" << std::endl;
    file << INIT_POS_Y_ATTR << " = " << options.m_display_options.m_init_pos_y;
    file << "\t\t\t; top-left corner vertical position in pixels. -1 will let the system decide" << std::endl;
    file << FULLSCREEN_ATTR << " = " << std::boolalpha << options.m_display_options.m_fullscreen;
    file << "\t\t\t; true/false" << std::endl;
    file << KEEP_ASPECT_RATIO_ATTR << " = " << options.m_display_options.m_fullscreen_keep_aspect_ratio;
    file << "\t; Keeps the aspect ratio in fullscreen adding vertical bands to the side." << std::endl;
    file << VOLUME_ATTR << " = " << options.m_volume;
    file << "\t\t\t\t\t; Audio volume - NOT IMPLEMENTED YET!!" << std::endl;
    file << std::endl;

    file << ";" << std::endl;
    file << "; Game Controller binding options:" << std::endl;
    file << ";" << std::endl;
    file << "; Axes= " << get_axis_input_name( static_cast<AxisInputs>( 0 ) );
    for( int i = 1; i < AxisInputs::NUM_AXIS_INPUTS; ++i )
        file << ", " << get_axis_input_name( static_cast<AxisInputs>( i ) );
    file << std::endl;
    file << "; Axes Alias= " << get_axis_input_alias( static_cast<AxisInputs>( 0 ) );
    for( int i = 1; i < AxisInputs::NUM_AXIS_INPUTS; ++i )
        file << ", " << get_axis_input_alias( static_cast<AxisInputs>( i ) );
    file << std::endl;
    file << "; GameController Buttons= dpup, dpright, dpleft, dpdown, ba, bb, by, bx, ";
    file << "leftshoulder, rightshoulder, leftstick, rightstick, start, back, guide" << std::endl;
    file << ";" << std::endl;

    file << "[" << CONTROLS_SECTION << "]" << std::endl;
    for( int input = 0; input < Inputs::NUM_INPUTS; ++input )
    {
        file << INPUT_ATTR[input] << " = ";
        switch( options.m_inputs[input].m_type )
        {
        case InputBindType::KEY:    file << SDL_GetKeyName( options.m_inputs[input].m_input_bind.key_code );   break;
        case InputBindType::AXIS:   file << get_axis_input_name( options.m_inputs[input].m_input_bind.controller_axis );   break;
        case InputBindType::BUTTON: file << SDL_GameControllerGetStringForButton( options.m_inputs[input].m_input_bind.controller_button );   break;
        }
        file << std::endl;
    }
    file << std::endl;
    file << GAME_CONTROLLER_DEAD_ZONE << " = " << options.m_controller_dead_zone;
    file << "\t; 0 - 32767" << std::endl;
    file << std::endl;

    file << "[" << MISC_SECTION << "]" << std::endl;
    file << ZIP_MASTER_PASSWORD << " = " << options.m_zip_password << std::endl;
    file << RAM_SAVE_ENABLED << " = " << options.m_ram_save_enabled;
    file << "\t\t; true/false" << std::endl;
    file << std::endl;

    // both close and flush will be automatically called when the ofstream is destroyed
    //file.close();

    return true;
}
