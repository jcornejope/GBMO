
#include "joypad/joypad.h"
#include "cpu/cpu.h"
#include "memory/memory_system.h"
#include "utils/logger.h"
#include "utils/utils.h"

Joypad::Joypad( CPU& cpu, MemorySystem& memory )
    : m_cpu( cpu )
    , m_memory( memory )
    , m_game_controller( nullptr )
    , m_joystick_id( -1 )
    , m_input_flags( 0xFF )
{
    m_memory.write( P1_JOYP_ADDR, u8( 0xFF ) );
}

void Joypad::init()
{
    for( int i = 0; i < SDL_NumJoysticks(); ++i )
    {
        if( SDL_IsGameController( i ) )
        {
            m_game_controller = SDL_GameControllerOpen( i );
            if( m_game_controller )
            {
                SDL_Joystick* joystick = SDL_GameControllerGetJoystick( m_game_controller );
                m_joystick_id = SDL_JoystickInstanceID( joystick );

                LOG( LogCat::SYSTEM, "Controller found! Using controller [%d] with joystick ID[%d][%s]", 
                     i, m_joystick_id, SDL_GameControllerName( m_game_controller ) );
                break;
            }
        }
    }
}

void Joypad::deinit()
{
    if( m_game_controller )
    {
        SDL_GameControllerClose( m_game_controller );
        LOG( LogCat::SYSTEM, "Controller released!" );

        m_game_controller = nullptr;
        m_joystick_id = -1;
    }
}

bool Joypad::wants_to_handle_input_event( u32 event_type ) const
{
    return ( event_type == SDL_KEYDOWN || event_type == SDL_KEYUP ||
           ( event_type >= SDL_CONTROLLERAXISMOTION && event_type <= SDL_CONTROLLERDEVICEREMAPPED ) );
}

void Joypad::handle_input_event( SDL_Event & event )
{
    bool input_processed = false;
    u8 joyp = m_memory.read_8( P1_JOYP_ADDR );
    for( u32 i = 0; i < Inputs::NUM_INPUTS && !input_processed; ++i )
    {
        switch( event.type )
        {
        case SDL_KEYDOWN:
        case SDL_KEYUP:
        {
            // Don't care about repeats so early exit
            if( event.key.repeat != 0 )
                continue;

            if( m_inputs[i].m_type != InputBindType::KEY )
                continue;

            if( event.key.keysym.sym == m_inputs[i].m_input_bind.key_code )
            {
                input_processed = _handle_input_flag( event.type == SDL_KEYDOWN, i, joyp );
            }
        }
            break;

        case SDL_CONTROLLERAXISMOTION:
        {
            if( m_inputs[i].m_type != InputBindType::AXIS )
                continue;

            s32 sign;
            SDL_GameControllerAxis axis;
            translate_from_axis_input( m_inputs[i].m_input_bind.controller_axis, axis, sign );

            static s16 const DEAD_ZONE = 10000;
            u8 const bit = ( 1 << i );
            if( event.caxis.axis == axis )
            {
                // Need to clear the axis opposite direction so we need to process other possible entries. 
                // Don't back out with "input_processed" for CONTROLLERAXISMOTION events.
                _handle_input_flag( ( ( event.caxis.value * sign ) > DEAD_ZONE ), i, joyp );
            }
        }
            break;

        case SDL_CONTROLLERBUTTONDOWN:
        case SDL_CONTROLLERBUTTONUP:
        {
            if( m_inputs[i].m_type != InputBindType::BUTTON )
                continue;

            u8 const bit = ( 1 << i );
            if( event.cbutton.button == m_inputs[i].m_input_bind.controller_button )
            {
                input_processed = _handle_input_flag( event.type == SDL_CONTROLLERBUTTONDOWN, i, joyp );
            }
        }
            break;
        case SDL_CONTROLLERDEVICEADDED:
        {
            if( !m_game_controller )
                init();

            input_processed = true;
        }
            break;
        case SDL_CONTROLLERDEVICEREMOVED:
        {
            if( m_game_controller && event.cdevice.which == m_joystick_id )
                deinit();

            input_processed = true;
        }
            break;
        }
    }

    // This will trigger the memory_system to request an update on the inputs and store in memory.
    m_memory.write( P1_JOYP_ADDR, joyp );
}

u8 Joypad::get_inputs_for_memory( u8 joyp )
{
    auto create_new_joyp_and_request_interrupt = [&joyp, this]( u8 const new_low_joyp )
    {
        if( ( new_low_joyp & ( new_low_joyp ^ ( joyp & 0x0F ) ) ) != 0 )
            m_cpu.request_interrupt( Interrupts::JOYPAD );

        joyp = 0xC0 | ( joyp & 0x30 ) | ( new_low_joyp & 0x0F );
    };

    if( _are_directions_enabled( joyp ) )
    {
        create_new_joyp_and_request_interrupt( ( m_input_flags & 0x0F ) );
    }
    else if( _are_buttons_enabled( joyp ) )
    {
        create_new_joyp_and_request_interrupt( ( m_input_flags & 0xF0 ) >> 4 );
    }
    else
    {
        joyp = 0xFF;
    }

    return joyp;
}

void Joypad::set_input_bindings( InputsConfig const& new_inputs )
{
    std::memcpy( m_inputs, new_inputs, sizeof( InputBind ) * Inputs::NUM_INPUTS );
}

bool Joypad::_handle_input_flag( bool const pressed, u32 const bit_index, u8 const joyp )
{
    u8 const bit = ( 1 << bit_index );
    if( pressed )
    {
        if( m_input_flags & bit )
        {
            m_input_flags &= ~bit; // 0 is pressed!

            // TODO: IS THIS CORRECT? input is direction but we check buttons are enabled?
            if( ( bit_index < Inputs::BUTTONS_START && _are_buttons_enabled( joyp ) ) ||
                ( bit_index > Inputs::DIRECTIONS_END && _are_directions_enabled( joyp ) ) )
                m_cpu.request_interrupt( Interrupts::JOYPAD );

            return true;
        }
    }
    else
    {
        m_input_flags |= bit;
        return true;
    }

    return false;
}

