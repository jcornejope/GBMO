#include "cpu.h"

// Instruction set
void CPU::_initialize_instruction_tables()
{

}

// Transfer and I/O instructions
void CPU::_ld( u8& lhs, u8 const rhs )
{
    lhs = rhs;
}

void CPU::_ld( u16& lhs, u16 const rhs ){ }
void CPU::_ld_id( u16 lhs, u8 rhs, u8 inc ){ }
void CPU::_ld_id( u8 rhs, u16 lhs, u8 inc ){ }
void CPU::_push( u16 lhs ){ }
void CPU::_pop( u16 lhs ){ }
// Aritmethic
void CPU::_add( u8 lhs, u8 rhs, bool carry ){ }
void CPU::_add( u8 lhs, u16 rhs, bool carry ){ }
void CPU::_add( u16 lhs, u16 rhs, bool carry ){ }
void CPU::_add( u16 lhs, s8 rhs, bool carry ){ }
void CPU::_sub( u8 lhs, u8 rhs, bool carry ){ }
void CPU::_sub( u8 lhs, u16 rhs, bool carry ){ }
void CPU::_inc_dec( u8 lhs, u8 inc ){ }
void CPU::_inc_dec( u16 lhs, u8 inc ){ }
void CPU::_decimal_adjust_acc(){ }
void CPU::_complement(){ }
// Logical (all these uses register A)
void CPU::_and( u8 rhs ){ }
void CPU::_xor( u8 rhs ){ }
void CPU::_or( u8 rhs ){ }
void CPU::_cmp( u8 rhs ){ }
// Rotate Shift
void CPU::_rl( u8 lhs, bool carry ){ }
void CPU::_rr( u8 lhs, bool carry ){ }
void CPU::_shift_l( u8 lhs ){ }
void CPU::_shift_r( u8 lhs ){ }
void CPU::_shift_r_logical( u8 lhs ){ }
void CPU::_swap( u8 lhs ){ }
// Bit
void CPU::_test_bit( u8 lhs ){ }
void CPU::_set_bit( u8 lhs ){ }
void CPU::_reset_bit( u8 lhs ){ }
// Jumps
void CPU::_jump( u16 address ){ }
void CPU::_jump( s8 relative_address ){ }
bool CPU::_conditional_jump( u16 addres ){ return false; }
bool CPU::_conditional_jump( s8 relative_addres ){ return false; }
// Call and Return
void CPU::_call( u16 address ){ }
bool CPU::_conditional_call( u16 address ) { return false; }
void CPU::_call_routine( u8 routine_address ){ }
void CPU::_ret( bool enable_interruptions ){ }
bool CPU::_conditional_ret(){ return false; }
// CPU Control
void CPU::_nop(){ }
void CPU::_set_carry(){ }
void CPU::_halt(){ }
void CPU::_stop(){ }
void CPU::_set_interrupts( bool enable ){ }
