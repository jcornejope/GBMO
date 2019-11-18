
#include "options.h"

#include <INIReader.h>
#include <SDL.h>

#include <fstream>

namespace
{
    char const* DEFAULT_SETTINGS_FILE = ".\\settings.ini";

    char const* OPTIONS_SECTION = "options";
    char const* CONTROLS_SECTION = "controls";

    char const* VOLUME_ATTR = "volume";
    char const* PALETTE_IDX_ATTR = "palette";
    char const* RESOLUTION_SCALE_ATTR = "scale_mult";
    char const* INIT_POS_X_ATTR = "initial_pos_x";
    char const* INIT_POS_Y_ATTR = "initial_pos_y";
    char const* FULLSCREEN_ATTR = "fullscreen";
    char const* KEEP_ASPECT_RATIO_ATTR = "keep_aspect_ratio";

    char const* INPUT_UP = "up";
    char const* INPUT_DOWN = "down";
    char const* INPUT_LEFT = "left";
    char const* INPUT_RIGHT = "right";
    char const* INPUT_A = "a";
    char const* INPUT_B = "b";
    char const* INPUT_SELECT = "select";
    char const* INPUT_START = "start";
}

bool Options::load_from_file()
{
    return load_from_file( DEFAULT_SETTINGS_FILE );
}

bool Options::load_from_file( char const* file_name )
{
    // NOTE: I'm not totally sold on this lib. It creates std::string everywhere just because.
    // TODO: Evaluate refactoring it to use <char const*> instead.
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

    m_inputs[Inputs::UP] = SDL_GetKeyFromName( reader.Get( CONTROLS_SECTION, INPUT_UP, SDL_GetKeyName( def.m_inputs[Inputs::UP] ) ).c_str() );
    m_inputs[Inputs::DOWN] = SDL_GetKeyFromName( reader.Get( CONTROLS_SECTION, INPUT_DOWN, SDL_GetKeyName( def.m_inputs[Inputs::DOWN] ) ).c_str() );
    m_inputs[Inputs::LEFT] = SDL_GetKeyFromName( reader.Get( CONTROLS_SECTION, INPUT_LEFT, SDL_GetKeyName( def.m_inputs[Inputs::LEFT] ) ).c_str() );
    m_inputs[Inputs::RIGHT] = SDL_GetKeyFromName( reader.Get( CONTROLS_SECTION, INPUT_RIGHT, SDL_GetKeyName( def.m_inputs[Inputs::RIGHT] ) ).c_str() );
    m_inputs[Inputs::A] = SDL_GetKeyFromName( reader.Get( CONTROLS_SECTION, INPUT_A, SDL_GetKeyName( def.m_inputs[Inputs::A] ) ).c_str() );
    m_inputs[Inputs::B] = SDL_GetKeyFromName( reader.Get( CONTROLS_SECTION, INPUT_B, SDL_GetKeyName( def.m_inputs[Inputs::B] ) ).c_str() );
    m_inputs[Inputs::START] = SDL_GetKeyFromName( reader.Get( CONTROLS_SECTION, INPUT_START, SDL_GetKeyName( def.m_inputs[Inputs::START] ) ).c_str() );
    m_inputs[Inputs::SELECT] = SDL_GetKeyFromName( reader.Get( CONTROLS_SECTION, INPUT_SELECT, SDL_GetKeyName( def.m_inputs[Inputs::SELECT] ) ).c_str() );

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

    file << "[" << CONTROLS_SECTION << "]" << std::endl;
    file << INPUT_UP << " = " << SDL_GetKeyName( options.m_inputs[Inputs::UP] ) << std::endl;
    file << INPUT_DOWN << " = " << SDL_GetKeyName( options.m_inputs[Inputs::DOWN] ) << std::endl;
    file << INPUT_LEFT << " = " << SDL_GetKeyName( options.m_inputs[Inputs::LEFT] ) << std::endl;
    file << INPUT_RIGHT << " = " << SDL_GetKeyName( options.m_inputs[Inputs::RIGHT] ) << std::endl;
    file << INPUT_A << " = " << SDL_GetKeyName( options.m_inputs[Inputs::A] ) << std::endl;
    file << INPUT_B << " = " << SDL_GetKeyName( options.m_inputs[Inputs::B] ) << std::endl;
    file << INPUT_START << " = " << SDL_GetKeyName( options.m_inputs[Inputs::START] ) << std::endl;
    file << INPUT_SELECT << " = " << SDL_GetKeyName( options.m_inputs[Inputs::SELECT] ) << std::endl;
    file << std::endl;

    // both close and flush will be automatically called when the ofstream is destroyed
    //file.close();

    return true;
}
