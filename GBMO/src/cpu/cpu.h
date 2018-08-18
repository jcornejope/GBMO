#pragma once

#include "utils/types.h"
#include <functional>

#define DEFINE_REGISTER_16(HI, LO) \
union \
{ \
    struct \
    { \
        u8 LO; \
        u8 HI; \
    }; \
    u16 HI##LO; \
} \

class MemorySystem;

class CPU
{
    struct Registers
    {
        DEFINE_REGISTER_16( a, f );
        DEFINE_REGISTER_16( b, c );
        DEFINE_REGISTER_16( d, e );
        DEFINE_REGISTER_16( h, l );

        u16 sp;
        u16 pc;
    };

    enum Flags : u8
    {
        NONE        = 0x3,      // Not used( always zero )
        CARRY       = 1 << 4,
        HALF_CARRY  = 1 << 5,   // BCD
        ADD_SUB     = 1 << 6,   // BCD
        ZERO        = 1 << 7
    };

    static float const CPU_SPEED;
    static float const CPU_SPEED_CGB_DOUBLE;

public:
    CPU( MemorySystem& memory );

private:
    // Instruction set
    void _initialize_instruction_tables();
    // Transfer and I/O instructions
    void _ld( u8& lhs, u8 const rhs );
    void _ld( u16& lhs, u16 const rhs );
    void _ld_id( u16 lhs, u8 rhs, u8 inc );
    void _ld_id( u8 rhs, u16 lhs, u8 inc );
    void _push( u16 lhs );
    void _pop( u16 lhs );
    // Aritmethic
    void _add( u8 lhs, u8 rhs, bool carry );
    void _add( u8 lhs, u16 rhs, bool carry );
    void _add( u16 lhs, u16 rhs, bool carry );
    void _add( u16 lhs, s8 rhs, bool carry );
    void _sub( u8 lhs, u8 rhs, bool carry );
    void _sub( u8 lhs, u16 rhs, bool carry );
    void _inc_dec( u8 lhs, u8 inc );
    void _inc_dec( u16 lhs, u8 inc );
    void _decimal_adjust_acc();
    void _complement();
    // Logical (all these uses register A)
    void _and( u8 rhs );
    void _xor( u8 rhs );
    void _or( u8 rhs );
    void _cmp( u8 rhs );
    // Rotate Shift
    void _rl( u8 lhs, bool carry );
    void _rr( u8 lhs, bool carry );
    void _shift_l( u8 lhs );
    void _shift_r( u8 lhs );
    void _shift_r_logical( u8 lhs );
    void _swap( u8 lhs );
    // Bit
    void _test_bit( u8 lhs );
    void _set_bit( u8 lhs );
    void _reset_bit( u8 lhs );
    // Jumps
    void _jump( u16 address );
    void _jump( s8 relative_address );
    bool _conditional_jump( u16 addres );
    bool _conditional_jump( s8 relative_addres );
    // Call and Return
    void _call( u16 address );
    bool _conditional_call( u16 address );
    void _call_routine( u8 routine_address );
    void _ret( bool enable_interruptions );
    bool _conditional_ret();
    // CPU Control
    void _nop();
    void _set_carry();
    void _halt();
    void _stop();
    void _set_interrupts( bool enable );

    typedef std::function<u32( void )> Instruction;
    Instruction m_base_instruction[0xFF];
    Instruction m_cb_prefix_instruction[0xFF];

    Registers m_registers;
    MemorySystem& m_memory;
};

