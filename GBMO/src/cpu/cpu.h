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
        NONE        = 0x0F,     // Not used( always zero )
        CARRY       = 1 << 4,
        HALF_CARRY  = 1 << 5,   // BCD
        ADD_SUB     = 1 << 6,   // BCD
        ZERO        = 1 << 7
    };

    enum class JumpCondition : u8
    {
        NO_ZERO     = 0,
        ZERO        = 1,
        NO_CARRY    = 2,
        CARRY       = 3,

        NO_CONDITION = 0xFF,
    };

    enum class CPUMode : u8
    {
        NORMAL,     // Normal cpu operations
        STOP,       // stop mode active: switch the gameboy into VERY low power standby mode. The STOP state is terminated by interrupt events - in this case this would be commonly a joypad interrupt
        HALT,       // halt mode active: stops the system clock reducing the power consumption of both the CPU and ROM. The CPU will remain suspended until an interrupt occurs at which point the interrupt is serviced and then the instruction immediately following the HALT is executed.
        LOCKED      // something went wrong and the cpu locks itself up (for instance executing one of the non-implemented instructions like D3).
    };

    static u32 const CPU_SPEED;
    static u32 const CPU_SPEED_CGB_DOUBLE;

public:
    CPU( MemorySystem& memory );

    void reset();
    u32 update();
    u32 process_interrupts();
    void update_timer_registers( u32 const cycles );
    void update_divider_register( u32 const cycles );

    void request_interrupt( Interrupts const interrupt ) const;

private:
    // Flags manipulation
    void _process_zero_flag();
    void _process_zero_flag( u8 const reg );
    void _process_carry_flag_8( u16 const value );
    void _process_carry_flag_16( u32 const value );
    void _process_half_carry_flag( u8 const value, u8 const carry, bool const is_addition );
    void _process_half_carry_flag( u8 const reg, u8 const value, u8 const carry, bool const is_addition );
    void _process_half_carry_flag( u16 const reg, u16 const value, u16 const mask_to_test );
    void _set_flag( Flags const flag );
    u8   _get_flag( Flags const flag ) const;
    void _reset_flag( Flags const flag );
    bool _is_flag_set( Flags const flag ) const;

    // Helper functions
    bool _condition_passed( JumpCondition const condition ) const;
    u8 _get_interrupt_jump_vector_address( u8 const bit_index ) const;

    // Instruction set
    void _initialize_instruction_tables();
    u32 _reroute_to_cb_table();
    // 8Bit Transfer
    u32 _ld_r_n( u8& reg );
    u32 _ld_r_hl( u8& reg );
    u32 _ld_hl_r( u8 const reg );
    u32 _ld_hl_n();
    u32 _ld_a_mem( u16 const address );
    u32 _ld_a_nn();
    u32 _ld_mem_a( u16 const address );
    u32 _ld_nn_a();
    u32 _ld_inc_dec_hl_a( s8 const inc );
    u32 _ld_inc_dec_a_hl( s8 const inc );
    // I/O instructions
    u32 _ld_a_io_n(); // read from io
    u32 _ld_a_io_c(); // read from io
    u32 _ld_io_n_a(); // write to io
    u32 _ld_io_c_a(); // write to io
    // 16Bit Transfer
    u32 _ld_rr_nn( u16& reg );
    u32 _ld_sp_hl();
    u32 _push( u16 const reg );
    u32 _pop( u16& reg );
    u32 _ldhl();
    u32 _ld_nn_sp();
    // 8Bit Aritmethic
    void _add( u8 const rhs, bool const carry );
    void _sub( u8 const rhs, bool const carry );
    u32 _inc_r( u8& reg );
    u32 _inc_hl();
    u32 _dec_r( u8& reg );
    u32 _dec_hl();
    u32 _decimal_adjust_acc();
    u32 _complement();
    // Logical
    void _and( u8 const rhs );
    void _xor( u8 const rhs );
    void _or( u8 const rhs );
    void _cmp( u8 const rhs );
    // 16Bit Aritmethic
    u32 _add_hl( u16 const reg );
    u32 _add_sp();
    u32 _inc_dec( u16& reg, s8 const inc );
    // Rotate Shift
    u32 _rla_rlca( bool through_carry );
    void _rl_rlc( u8& reg, bool through_carry );
    u32 _rl_rlc_hl( bool through_carry );
    u32 _rra_rrca( bool through_carry );
    void _rr_rrc( u8& reg, bool through_carry );
    u32 _rr_rrc_hl( bool through_carry );
    void _shift_l( u8& reg );
    void _shift_r( u8& reg, bool logical );
    u32 _shift_l_hl();
    u32 _shift_r_hl( bool logical );
    void _swap( u8& reg );
    u32 _swap_hl();
    // Bit Operations
    void _test_bit( u8 const reg, u8 const bit );
    void _set_bit( u8& reg, u8 const bit );
    u32 _set_bit_hl( u8 const bit );
    void _reset_bit( u8& reg, u8 const bit );
    u32 _reset_bit_hl( u8 const bit );
    // Jumps
    u32 _jump( JumpCondition const condition = JumpCondition::NO_CONDITION );
    u32 _jump_relative( JumpCondition const condition = JumpCondition::NO_CONDITION );
    u32 _jump_hl();
    // Call and Returns
    u32 _call( JumpCondition const condition = JumpCondition::NO_CONDITION );
    u32 _ret( JumpCondition const condition = JumpCondition::NO_CONDITION );
    u32 _reti();
    u32 _call_routine( u8 const routine_address );
    // CPU Control
    u32 _ccf();
    u32 _scf();

    typedef std::function<u32( void )> Instruction;
    Instruction m_base_instruction[0xFF + 1];
    Instruction m_cb_prefix_instruction[0xFF + 1];

    Registers m_registers;
    MemorySystem& m_memory;

    CPUMode m_mode;

    u32 m_div_cycle_counter;
    u32 m_tima_cycle_counter;

    bool m_ime;
};
