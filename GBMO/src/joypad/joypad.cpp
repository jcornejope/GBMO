
#include "joypad/joypad.h"
#include "cpu/cpu.h"
#include "memory/memory_system.h"

Joypad::Joypad( CPU& cpu, MemorySystem& memory )
    : m_cpu( cpu )
    , m_memory( memory )
    , m_input_flags( 0xFF )
{
}

void Joypad::handle_input_event( SDL_Event & event )
{
    for( u32 i = 0; i < Inputs::NUM_INPUTS; ++i )
    {
        // TODO: Check if the input is key or gamepad button or gamepad axis.
        // assume key for now.
        if( event.key.keysym.sym == m_inputs[i] )
        {
            if( event.type == SDL_KEYDOWN && ( m_input_flags & i ) != 0 )
            {
                m_input_flags &= ~i; // 0 is pressed!
            }
            else if( event.type == SDL_KEYUP )
            {
                m_input_flags |= i;
            }
        }
    }

    // This will trigger the memory_system to request an update on the inputs and store in memory.
    m_memory.write( P1_JOYP_ADDR, m_memory.read_8( P1_JOYP_ADDR ) );
}

u8 Joypad::get_inputs_for_memory( u8 joyp )
{
    auto create_new_joyp_and_request_interrupt = [&joyp, this]( u8 const new_low_joyp )
    {
        if( ( new_low_joyp & ( new_low_joyp ^ ( joyp & 0x0F ) ) ) != 0 )
            m_cpu.request_interrupt( Interrupts::JOYPAD );

        joyp = ( joyp & 0xF0 ) | ( new_low_joyp );
    };

    if( ( joyp & ( 1 << 4 ) ) == 0 )
    {
        // Buttons
        create_new_joyp_and_request_interrupt( ( m_input_flags & 0xF0 ) >> 4 );
    }
    else if( ( joyp & ( 1 << 3 ) ) == 0 )
    {
        // Direction Keys
        create_new_joyp_and_request_interrupt( ( m_input_flags & 0x0F ) );
    }

    return joyp;
}

void Joypad::set_input_bindings( InputsConfig const& new_inputs )
{
    std::memcpy( m_inputs, new_inputs, Inputs::NUM_INPUTS );
}

