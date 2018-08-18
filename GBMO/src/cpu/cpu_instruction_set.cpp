
#include "cpu.h"
#include "memory/memory_system.h"

#include <cassert>

// Instruction set
void CPU::_initialize_instruction_tables()
{
    //m_base_instruction[0x00] = std::bind( &CPU::_noop, this );
    m_base_instruction[0x00] = [this]() { ++m_registers.pc; return 4; };
    m_base_instruction[0x02] = [this]() { m_memory.write( m_registers.bc, m_registers.a ); return 8; };

    m_base_instruction[0x47] = std::bind( &CPU::_ld_r_r, this, std::ref( m_registers.b ), std::cref( m_registers.a ) );
}

// 8Bit Transfer
u32 CPU::_ld_r_r( u8& lhs, u8 const rhs )
{
    lhs = rhs;
    return 4;
}

u32 CPU::_ld_r_n( u8& reg )
{
    reg = m_memory.read_8( m_registers.pc++ );
    return 8;
}

u32 CPU::_ld_r_hl( u8& reg )
{
    reg = m_memory.read_8( m_registers.hl );
    return 8;
}

u32 CPU::_ld_hl_r( u8 const reg )
{
    m_memory.write( m_registers.hl, reg ); 
    return 8;
}

u32 CPU::_ld_hl_n()
{
    u8 const data = m_memory.read_8( m_registers.pc++ );
    m_memory.write( m_registers.hl, data );

    return 12;
}

u32 CPU::_ld_a_mem( u16 const address )
{
    m_registers.a = m_memory.read_8( address );
    return 8;
}

u32 CPU::_ld_a_nn()
{
    u16 const address = m_memory.read_16( m_registers.pc );
    m_registers.pc += 2;
    m_registers.a = m_memory.read_8( address );

    return 16;
}

u32 CPU::_ld_mem_a( u16 const address )
{
    m_memory.write( address, m_registers.a );
    return 8;
}

u32 CPU::_ld_nn_a()
{
    u16 const address = m_memory.read_16( m_registers.pc );
    m_registers.pc += 2;
    m_memory.write( address, m_registers.a );

    return 8;
}

u32 CPU::_ld_inc_dec_hl_a( s8 inc )
{
    assert( inc == 1 || inc == -1 );
    m_memory.write( m_registers.hl, m_registers.a );
    m_registers.hl += inc;

    return 8;
}

u32 CPU::_ld_inc_dec_a_hl( s8 inc )
{
    assert( inc == 1 || inc == -1 );
    m_registers.a = m_memory.read_8( m_registers.hl );
    m_registers.hl += inc;

    return 8;
}

// I/O instructions
u32 CPU::_ld_a_io_n()
{
    u8 const address_offset = m_memory.read_8( m_registers.pc++ );
    m_registers.a = m_memory.read_8( m_memory.IO_ADDRESS_START + address_offset );

    return 12;
}

u32 CPU::_ld_a_io_c()
{
    m_registers.a = m_memory.read_8( m_memory.IO_ADDRESS_START + m_registers.c );
    return 8;
}

u32 CPU::_ld_io_n_a()
{
    u8 const address_offset = m_memory.read_8( m_registers.pc++ );
    m_memory.write( m_memory.IO_ADDRESS_START + address_offset, m_registers.a );

    return 12;
}

u32 CPU::_ld_io_c_a()
{
    m_memory.write( m_memory.IO_ADDRESS_START + m_registers.c, m_registers.a );
    return 8;
}

// 16Bit Transfer
u32 CPU::_ld_rr_nn( u16& reg )
{
    reg = m_memory.read_16( m_registers.pc );
    m_registers.pc += 2;

    return 12;
}

u32 CPU::_ld_sp_hl()
{
    m_registers.sp = m_registers.hl;
    return 8;
}

u32 CPU::_push( u16 const reg )
{
    //u8 const hi = static_cast<u8>( reg >> 8 );
    //u8 const lo = static_cast<u8>( reg );
    //m_memory.write( m_registers.sp - 1, hi );
    //m_memory.write( m_registers.sp - 2, lo );

    word aux = { reg };
    m_memory.write( m_registers.sp - 1, aux.hi );
    m_memory.write( m_registers.sp - 2, aux.lo );
    m_registers.sp -= 2;

    return 16;
}

u32 CPU::_pop( u16& reg )
{
    //word aux = { { .lo = m_memory.read_8( m_registers.sp ), .hi = m_memory.read_8( m_registers.sp + 1 ) } };
    word aux;
    aux.lo = m_memory.read_8( m_registers.sp );
    aux.hi = m_memory.read_8( m_registers.sp + 1 );
    reg = aux.data;
    m_registers.sp += 2;

    return 12;
}

////////////////////////

// Aritmethic
void CPU::_add( u8 lhs, u8 rhs, bool carry ){ assert( false ); /* NOT IMPLEMENTED */ }
void CPU::_add( u8 lhs, u16 rhs, bool carry ){ assert( false ); /* NOT IMPLEMENTED */ }
void CPU::_add( u16 lhs, u16 rhs, bool carry ){ assert( false ); /* NOT IMPLEMENTED */ }
void CPU::_add( u16 lhs, s8 rhs, bool carry ){ assert( false ); /* NOT IMPLEMENTED */ }
void CPU::_sub( u8 lhs, u8 rhs, bool carry ){ assert( false ); /* NOT IMPLEMENTED */ }
void CPU::_sub( u8 lhs, u16 rhs, bool carry ){ assert( false ); /* NOT IMPLEMENTED */ }
void CPU::_inc_dec( u8 lhs, u8 inc ){ assert( false ); /* NOT IMPLEMENTED */ }
void CPU::_inc_dec( u16 lhs, u8 inc ){ assert( false ); /* NOT IMPLEMENTED */ }
void CPU::_decimal_adjust_acc(){ assert( false ); /* NOT IMPLEMENTED */ }
void CPU::_complement(){ assert( false ); /* NOT IMPLEMENTED */ }
// Logical (all these uses register A)
void CPU::_and( u8 rhs ){ assert( false ); /* NOT IMPLEMENTED */ }
void CPU::_xor( u8 rhs ){ assert( false ); /* NOT IMPLEMENTED */ }
void CPU::_or( u8 rhs ){ assert( false ); /* NOT IMPLEMENTED */ }
void CPU::_cmp( u8 rhs ){ assert( false ); /* NOT IMPLEMENTED */ }
// Rotate Shift
void CPU::_rl( u8 lhs, bool carry ){ assert( false ); /* NOT IMPLEMENTED */ }
void CPU::_rr( u8 lhs, bool carry ){ assert( false ); /* NOT IMPLEMENTED */ }
void CPU::_shift_l( u8 lhs ){ assert( false ); /* NOT IMPLEMENTED */ }
void CPU::_shift_r( u8 lhs ){ assert( false ); /* NOT IMPLEMENTED */ }
void CPU::_shift_r_logical( u8 lhs ){ assert( false ); /* NOT IMPLEMENTED */ }
void CPU::_swap( u8 lhs ){ assert( false ); /* NOT IMPLEMENTED */ }
// Bit
void CPU::_test_bit( u8 lhs ){ assert( false ); /* NOT IMPLEMENTED */ }
void CPU::_set_bit( u8 lhs ){ assert( false ); /* NOT IMPLEMENTED */ }
void CPU::_reset_bit( u8 lhs ){ assert( false ); /* NOT IMPLEMENTED */ }
// Jumps
void CPU::_jump( u16 address ){ assert( false ); /* NOT IMPLEMENTED */ }
void CPU::_jump( s8 relative_address ){ assert( false ); /* NOT IMPLEMENTED */ }
bool CPU::_conditional_jump( u16 addres ){ return false; }
bool CPU::_conditional_jump( s8 relative_addres ){ return false; }
// Call and Return
void CPU::_call( u16 address ){ assert( false ); /* NOT IMPLEMENTED */ }
bool CPU::_conditional_call( u16 address ) { return false; }
void CPU::_call_routine( u8 routine_address ){ assert( false ); /* NOT IMPLEMENTED */ }
void CPU::_ret( bool enable_interruptions ){ assert( false ); /* NOT IMPLEMENTED */ }
bool CPU::_conditional_ret(){ return false; }
// CPU Control
u32 CPU::_noop()
{
    ++m_registers.pc;
    return 4;
}

void CPU::_set_carry(){ assert( false ); /* NOT IMPLEMENTED */ }
void CPU::_halt(){ assert( false ); /* NOT IMPLEMENTED */ }
void CPU::_stop(){ assert( false ); /* NOT IMPLEMENTED */ }
void CPU::_set_interrupts( bool enable ){ assert( false ); /* NOT IMPLEMENTED */ }
