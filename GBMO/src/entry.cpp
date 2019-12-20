
#include <SDL.h>

#include "gbmo.h"
#include "options.h"
#include "utils/logger.h"
#include "utils/utils.h"

#include <cstdlib>
#include <iostream>

void parse_args( int argc, char* argv[], Options &options );

int main( int argc, char* argv[] )
{
    Options options;
    if( !options.load_from_file() )
        Options::save_default();

    Options in_game_options{ options };
    parse_args( argc, argv, in_game_options );

    Logger::create_instance( in_game_options.m_log_path );

    LOG( LogCat::SYSTEM, "GBMO - GameBoy emulator [%s] started", Version::to_string().c_str() );

    {
        GBMO emulator( in_game_options );

        bool emulator_running = emulator.init();
        emulator_running &= emulator.get_display().init( in_game_options );

        while( emulator_running )
        {
            emulator_running = emulator.update();
        }

        emulator.deinit();
    }

    Logger::destroy_instance();

    options.save_to_file();

    return 0;
}

void parse_args( int argc, char* argv[], Options &options )
{
    for( int i = 0; i < argc; ++i )
    {
        char* arg = argv[i];
        if( strlen( arg ) < 2 )
            continue;

        if( arg[0] == '-' )
        {
            switch( arg[1] )
            {
            case 'd':
            case 'D':
                // RAM Load/Save enabled off: ( -d ) Disables load and save of the RAM for cartridges with battery capabilities.
                options.m_ram_save_enabled = false;
                break;
            case 'F':
                // FullScreen Keep Aspect Ratio: ( -F ) Starts the emulator in fullscreen mode adding black bars to the side to keep the original aspect ratio.
                options.m_display_options.m_fullscreen_keep_aspect_ratio = true;
            case 'f':
                // FullScreen: ( -f ) Starts the emulator in fullscreen mode stretching the image to fit the screen.
                options.m_display_options.m_fullscreen = true;
                break;
            case 'l':
            case 'L':
                // Log: ( -l <log_file> ) An empty log file means no log. No option will use the default file (".\log.txt").
                if( i + 1 < argc )
                {
                    options.m_log_path = argv[++i];
                }
                break;
            case 'p':
                // Position: ( -p <x> <y> ) Window position when starting the application. Negative values will center the screen.
                if( i + 1 < argc )
                {
                    char* arg_param = argv[++i];
                    int x = atoi( arg_param );
                    if( x >= 1 )
                        options.m_display_options.m_init_pos_x = x;
                }

                if( i + 1 < argc )
                {
                    char* arg_param = argv[++i];
                    int y = atoi( arg_param );
                    if( y >= 1 )
                        options.m_display_options.m_init_pos_y = y;
                }
                break;
            case 'P':
                // Palette index: ( -P <palette_index> ) Index of the palette to use at startup.
                if( i + 1 < argc )
                {
                    char* arg_param = argv[++i];
                    int idx = atoi( arg_param );
                    idx %= Display::NUM_SYSTEM_PALETTES;
                    options.m_display_options.m_palette_index = idx;
                }
                break;
            case 's':
            case 'S':
                // Screen scale: ( -s <screen_scale> ) Integer value for the screen scalar.
                if( i + 1 < argc )
                {
                    char* arg_param = argv[++i];
                    int scale = atoi( arg_param );
                    if( scale >= 1 )
                        options.m_display_options.m_resolution_scale = scale;
                }
                break;
            case 'r':
            case 'R':
                // Rom: ( -r <rom_path> )
                if( i + 1 < argc )
                {
                    options.m_rom_path = argv[++i];
                }
                break;
            case 'v':
            case 'V':
                // Volume: ( -v <volume> ) Float value defining the volume.
                if( i + 1 < argc )
                {
                    char* arg_param = argv[++i];
                    float volume = static_cast<float>( atof( arg_param ) );
                    // TODO: Check for valid volume values ( 0 to 1 ?? )
                    options.m_volume = volume;
                }
                break;
            case 'z':
            case 'Z':
                // Zip master password: ( -v <password> ) string defining the master password for the zip files
                if( i + 1 < argc )
                {
                    options.m_zip_password = argv[++i];
                }
                break;
            }
        }        
    }
}