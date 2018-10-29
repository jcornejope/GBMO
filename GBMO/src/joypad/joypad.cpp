
#include "joypad/joypad.h"
#include "cpu/cpu.h"
#include "memory/memory_system.h"

Joypad::Joypad( CPU& cpu, MemorySystem& memory )
    : m_cpu( cpu )
    , m_memory( memory )
    , m_input_flags( 0xFF )
{
    m_memory.write( P1_JOYP_ADDR, u8( 0xFF ) );
}

void Joypad::handle_input_event( SDL_Event & event )
{
    // Don't care about repeats so early exit
    if( event.key.repeat != 0 )
        return;

    u8 joyp = m_memory.read_8( P1_JOYP_ADDR );
    for( u32 i = 0; i < Inputs::NUM_INPUTS; ++i )
    {
        // TODO: Check if the input is key or gamepad button or gamepad axis.
        // assume key for now.
        u8 bit = ( 1 << i );
        if( event.key.keysym.sym == m_inputs[i] )
        {
            if( event.type == SDL_KEYDOWN && ( m_input_flags & bit ) != 0 )
            {
                m_input_flags &= ~bit; // 0 is pressed!

                if( ( i < 4 && _are_buttons_enabled( joyp ) ) ||
                    ( i > 3 && _are_directions_enabled( joyp ) ) )
                    m_cpu.request_interrupt( Interrupts::JOYPAD );

                break;
            }
            else if( event.type == SDL_KEYUP )
            {
                m_input_flags |= bit;
                break;
            }
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

