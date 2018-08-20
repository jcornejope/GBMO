
#include "cpu/cpu.h"
#include "memory/memory_system.h"

#include <cassert>

float const CPU::CPU_SPEED              = 4.194304f;
float const CPU::CPU_SPEED_CGB_DOUBLE   = 8.4f;

CPU::CPU( MemorySystem& memory )
    : m_memory( memory )
{
    m_registers.a = 0x0F;
    m_registers.b = 0xFF;

    _initialize_instruction_tables();
    
    m_base_instruction[0x47]();
    m_base_instruction[0x47]();

    // TESTS - WOULD BE A GOOD IDEA TO CREATE SOME UNIT TESTS TO CHECK THE INSTRUCTIONS AUTOMATICALLY.

    m_registers.a = 0x3A;
    m_registers.b = 0xC6;

    m_base_instruction[0x80](); // add 0x00 -> F:B0
    assert( m_registers.af == 0x00B0 );

    m_registers.a = 0x0F;
    m_registers.b = 0x01;

    m_base_instruction[0x80](); // add 0x10 -> F:20
    assert( m_registers.af == 0x1020 );

    m_registers.a = 0xE1;
    m_registers.b = 0x0F;
    _set_flag( Flags::CARRY );

    m_base_instruction[0x88](); // addc 0xF1 -> F:20
    assert( m_registers.af == 0xF120 );

    m_registers.a = 0x3E;
    m_registers.b = 0x40;

    m_base_instruction[0x90](); // sub 0xFE -> F:50
    assert( m_registers.af == 0xFE50 );

    m_registers.a = 0x3B;
    m_registers.b = 0x2A;
    _set_flag( Flags::CARRY );

    m_base_instruction[0x98](); // sbc 0x10 -> F:40
    assert( m_registers.af == 0x1040 );

    // DAA test
    m_registers.a = 0x45;
    m_registers.b = 0x38;
    m_base_instruction[0x80](); // add 0x7D -> F:00
    assert( m_registers.af == 0x7D00 );
    m_base_instruction[0x27](); // daa 0x83 -> F:00
    assert( m_registers.af == 0x8300 );
    m_base_instruction[0x90](); // sub 0x4B -> F:60
    assert( m_registers.af == 0x4B60 );
    m_base_instruction[0x27](); // daa 0x45 -> F:40
    assert( m_registers.af == 0x4540 );

    m_base_instruction[0xC6]();
}

void CPU::_process_zero_flag()
{
    _process_zero_flag( m_registers.a ); 
}

void CPU::_process_zero_flag( u8 const reg )
{
    if( reg == 0 )
        _set_flag( Flags::ZERO );
    else
        _reset_flag( Flags::ZERO );
}

void CPU::_process_carry_flag_8( u16 const value )
{
    if( value > 0xFF )
        _set_flag( Flags::CARRY );
    else
        _reset_flag( Flags::CARRY );
}

void CPU::_process_carry_flag_16( u32 const value )
{
    if( value > 0xFFFF )
        _set_flag( Flags::CARRY );
    else
        _reset_flag( Flags::CARRY );
}

void CPU::_process_half_carry_flag( u8 const value, u8 const carry, bool const is_addition )
{
    _process_half_carry_flag( m_registers.a, value, carry, is_addition );
}

void CPU::_process_half_carry_flag( u8 const reg, u8 const value, u8 const carry, bool const is_addition )
{
    assert( carry == 0 || carry == 1 );

    if( ( is_addition  && ( ( ( reg & 0x0F ) + ( value & 0x0F ) + carry ) > 0x0F ) ) ||
        ( !is_addition && ( ( ( reg & 0x0F ) - ( value & 0x0F ) - carry ) < 0x00 ) ) )
        _set_flag( Flags::HALF_CARRY );
    else
        _reset_flag( Flags::HALF_CARRY );
}

void CPU::_process_half_carry_flag( u16 const reg, u16 const value )
{
    // TODO: BUG? Following the documentation it says that the half carry for 16bit is 
    // bit 11 (even with examples) but the code for other 3 emulators I checked uses bit 3 :S
    if( ( reg & 0x0FFF ) + ( value & 0x0FFF ) > 0x0FFF )
        _set_flag( Flags::HALF_CARRY );
    else
        _reset_flag( Flags::HALF_CARRY );
}

void CPU::_set_flag( Flags const flag )
{
    assert( flag >= Flags::CARRY && flag <= Flags::ZERO );

    m_registers.f |= flag;
}

void CPU::_reset_flag( Flags const flag )
{
    assert( flag >= Flags::CARRY && flag <= Flags::ZERO );

    m_registers.f &= ~flag;
}

bool CPU::_is_flag_set( Flags const flag )
{
    assert( flag >= Flags::CARRY && flag <= Flags::ZERO );

    return ( m_registers.f & flag ) != 0;
}
