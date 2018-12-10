
#include "cpu/cpu.h"
#include "memory/memory_system.h"
#include "utils/assert.h"
#include "utils/logger.h"

//#define LOG_CPU_INSTRUCTIONS

u32 const CPU::CPU_SPEED              = 4194304;
u32 const CPU::CPU_SPEED_CGB_DOUBLE   = 8400000;

CPU::CPU( MemorySystem& memory )
    : m_memory( memory )
    , m_mode( CPUMode::NORMAL )
    , m_div_cycle_counter( 0 )
    , m_tima_cycle_counter( 0 )
    , m_ime( false )
{
#ifndef NDEBUG
    std::memset(m_pc_history, 0xFF, NUM_PC_HISTORY * sizeof(u16));
    m_pc_history_index = 0;
#endif

    _initialize_instruction_tables();

    reset();
}

void CPU::reset()
{
    m_mode = CPUMode::NORMAL;

    // TODO: This is set manually to 100 by now - change this when implementing the bootstrap.
    m_registers.pc = 0x0100;

    m_registers.af = 0x01B0;
    m_registers.bc = 0x0013;
    m_registers.de = 0x00D8;
    m_registers.hl = 0x014D;
    m_registers.sp = 0xFFFE;

    // CGB 
    //m_registers.af = 0x1180;
    //m_registers.bc = 0x0000;
    //m_registers.de = 0xFF56;
    //m_registers.hl = 0x000D;
    //m_registers.sp = 0xFFFE;

    m_memory.write( 0xFF05, static_cast<u8>( 0x00 ) ); // TIMA
    m_memory.write( 0xFF06, static_cast<u8>( 0x00 ) ); // TMA
    m_memory.write( 0xFF07, static_cast<u8>( 0x00 ) ); // TAC
    m_memory.write( 0xFF10, static_cast<u8>( 0x80 ) ); // NR10
    m_memory.write( 0xFF11, static_cast<u8>( 0xBF ) ); // NR11
    m_memory.write( 0xFF12, static_cast<u8>( 0xF3 ) ); // NR12
    m_memory.write( 0xFF14, static_cast<u8>( 0xBF ) ); // NR14
    m_memory.write( 0xFF16, static_cast<u8>( 0x3F ) ); // NR21
    m_memory.write( 0xFF17, static_cast<u8>( 0x00 ) ); // NR22
    m_memory.write( 0xFF19, static_cast<u8>( 0xBF ) ); // NR24
    m_memory.write( 0xFF1A, static_cast<u8>( 0x7F ) ); // NR30
    m_memory.write( 0xFF1B, static_cast<u8>( 0xFF ) ); // NR31
    m_memory.write( 0xFF1C, static_cast<u8>( 0x9F ) ); // NR32
    m_memory.write( 0xFF1E, static_cast<u8>( 0xBF ) ); // NR33
    m_memory.write( 0xFF20, static_cast<u8>( 0xFF ) ); // NR41
    m_memory.write( 0xFF21, static_cast<u8>( 0x00 ) ); // NR42
    m_memory.write( 0xFF22, static_cast<u8>( 0x00 ) ); // NR43
    m_memory.write( 0xFF23, static_cast<u8>( 0xBF ) ); // NR30
    m_memory.write( 0xFF24, static_cast<u8>( 0x77 ) ); // NR50
    m_memory.write( 0xFF25, static_cast<u8>( 0xF3 ) ); // NR51
    m_memory.write( 0xFF26, static_cast<u8>( 0xF1 ) ); // NR52 // $F1 - GB, $F0 - SGB
    m_memory.write( 0xFF40, static_cast<u8>( 0x91 ) ); // LCDC
    m_memory.write( 0xFF42, static_cast<u8>( 0x00 ) ); // SCY
    m_memory.write( 0xFF43, static_cast<u8>( 0x00 ) ); // SCX
    m_memory.write( 0xFF45, static_cast<u8>( 0x00 ) ); // LYC
    m_memory.write( 0xFF47, static_cast<u8>( 0xFC ) ); // BGP
    m_memory.write( 0xFF48, static_cast<u8>( 0xFF ) ); // OBP0
    m_memory.write( 0xFF49, static_cast<u8>( 0xFF ) ); // OBP1
    m_memory.write( 0xFF4A, static_cast<u8>( 0x00 ) ); // WY
    m_memory.write( 0xFF4B, static_cast<u8>( 0x00 ) ); // WX
    m_memory.write( 0xFFFF, static_cast<u8>( 0x00 ) ); // IE
}

u32 CPU::update()
{
    switch( m_mode )
    {
    case CPUMode::NORMAL:
    {
#ifndef NDEBUG
        m_pc_history[m_pc_history_index] = m_registers.pc;
        m_pc_history_index++;
        if( m_pc_history_index == NUM_PC_HISTORY )
            m_pc_history_index = 0;
#endif

        u8 opcode = m_memory.read_8( m_registers.pc++ );
        if( m_base_instruction[opcode] == nullptr )
        {
            ASSERT( false );
            m_mode = CPUMode::LOCKED;
            return 0;
        }
#ifdef LOG_CPU_INSTRUCTIONS
        LOG( "CPU", "[%#06x] %x\tR[AF:%#06x|BC:%#06x|DE:%#06x|HL:%#06x|SP:%#06x][ime:%c]"
            , m_registers.pc - 1, opcode
            , m_registers.af, m_registers.bc, m_registers.de, m_registers.hl, m_registers.sp
            , (m_ime) ? 'E' : 'D');
#endif
        return m_base_instruction[opcode]();

        break;
    }
    case CPUMode::HALT:     return 4;   break;
    case CPUMode::STOP:     return 0;   break;
    case CPUMode::LOCKED:   return 0;   break;
    }

    ERROR_MSG( "Invalid CPU Mode [%d]", static_cast<int>( m_mode ) );
    return 0;
}

u32 CPU::process_interrupts()
{
    if( m_mode == CPUMode::LOCKED )
        return 0;

    u8 if_register = m_memory.read_8( IF_ADDR );
    if( if_register != 0 && m_mode != CPUMode::NORMAL )
        m_mode = CPUMode::NORMAL;

    if( m_ime == true )
    {
        u8 ie_register = m_memory.read_8( IE_ADDR );

        for( u8 bit = 0; bit < 5; ++bit )
        { 
            u8 bitmask = ( 1 << bit );
            if( ( if_register & bitmask ) != 0 &&
                ( ie_register & bitmask ) != 0 )
            {
                _call_routine( _get_interrupt_jump_vector_address( bit ) );

                m_ime = false;
                if_register &= ~bitmask;
                m_memory.write( IF_ADDR, if_register );

                // Back to normal if we serviced an interrupt and we were on halt or stop mode.
                if( m_mode != CPUMode::NORMAL )
                    m_mode = CPUMode::NORMAL;

                return 20; // TODO DOUBLECHECK THIS!: Z80 is supposed to consume 5 cycles here (2 NOP, 2 PUSH, 1 PC LOAD)
            }
        }
    }

    return 0;
}

void CPU::update_timer_registers( u32 const cycles )
{
    // TODO CGB: DOUBLE SPEED - Do we need to change cycles_to_increment to 8400000/Freq ? (2050.78;32;128;512.69)

    u8 tac = m_memory.read_8( TAC_ADDR );
    if( ( tac & 0x4 ) != 0 )
    {
        m_tima_cycle_counter += cycles;
        u32 cycles_to_increment = 0;
        switch( tac & 0x3 )
        {
        case 0: cycles_to_increment = 1024u;  break;  // 4096 Hz    (4194304/4096)
        case 1: cycles_to_increment = 16u;    break;  // 262144 Hz
        case 2: cycles_to_increment = 64u;    break;  // 65536 Hz
        case 3: cycles_to_increment = 256u;   break;  // 16384 Hz
        }

        if( m_tima_cycle_counter >= cycles_to_increment )
        {
            m_tima_cycle_counter -= cycles_to_increment;

            u8 tima = m_memory.read_8( TIMA_ADDR ) + 1;
            if( tima == 0 )
            {
                tima = m_memory.read_8( TMA_ADDR );
                
                request_interrupt( Interrupts::TIMER );
            }

            m_memory.write( TIMA_ADDR, tima );
        }
    }
}

void CPU::update_divider_register( u32 const cycles )
{
    // DMG                  CPU_SPEED / 16384 = 256
    // CGB DOUBLE SPEED     CPU_SPEED_CGB_DOUBLE / 32768 = 256
    m_div_cycle_counter += cycles;
    if( m_div_cycle_counter >= 256 )
    {
        m_div_cycle_counter -= 256;
        u8 div_register = m_memory.read_8( DIV_ADDR ) + 1;
        m_memory.non_protected_write( DIV_ADDR, div_register );
    }
}

u8 CPU::_get_interrupt_jump_vector_address( u8 const bit_index ) const
{
    ASSERT_MSG( bit_index >= 0 && bit_index < 5, "Bit index out of range on [_get_interrupt_jump_vector_address]" );

    return static_cast<u8>( 0x40 + ( 0x08 * bit_index ) );
}

void CPU::request_interrupt( Interrupts const interrupt ) const
{
    u8 if_register = m_memory.read_8( IF_ADDR );
    if_register |= interrupt;
    m_memory.write( IF_ADDR, if_register );
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

void CPU::_process_carry_flag_8( u16 const value, bool const is_addition )
{
    if( ( is_addition && value > 0xFF ) ||
        ( !is_addition && value & 0x8000 ) )
        _set_flag( Flags::CARRY );
    else
        _reset_flag( Flags::CARRY );
}

void CPU::_process_carry_flag_16( u32 const value, bool const is_addition )
{
    if( ( is_addition && value > 0xFFFF ) ||
        ( !is_addition && value & 0x80000000 ) )
        _set_flag( Flags::CARRY );
    else
        _reset_flag( Flags::CARRY );
}

void CPU::_process_half_carry_flag_8( u8 const value, u8 const carry, bool const is_addition )
{
    _process_half_carry_flag_8( m_registers.a, value, carry, is_addition );
}

void CPU::_process_half_carry_flag_8( u8 const reg, u8 const value, u8 const carry, bool const is_addition )
{
    ASSERT( carry == 0 || carry == 1 );

    if( ( is_addition  && ( ( ( reg & 0x0F ) + ( value & 0x0F ) + carry ) > 0x0F ) ) ||
        ( !is_addition && ( ( ( reg & 0x0F ) - ( value & 0x0F ) - carry ) < 0x00 ) ) )
        _set_flag( Flags::HALF_CARRY );
    else
        _reset_flag( Flags::HALF_CARRY );
}

void CPU::_process_half_carry_flag_16( u16 const reg, u16 const value )
{
    if( ( reg & 0x0FFF ) + ( value & 0x0FFF ) > 0x0FFF )
        _set_flag( Flags::HALF_CARRY );
    else
        _reset_flag( Flags::HALF_CARRY );
}

void CPU::_set_flag( Flags const flag )
{
    ASSERT_MSG( flag >= Flags::CARRY && flag <= Flags::ZERO, "flag [%d] is not valid", flag );

    m_registers.f |= flag;
}

u8 CPU::_get_flag( Flags const flag ) const
{
    ASSERT_MSG( flag >= Flags::CARRY && flag <= Flags::ZERO, "flag [%d] is not valid", flag );

    return m_registers.f & flag;
}

void CPU::_reset_flag( Flags const flag )
{
    ASSERT_MSG( flag >= Flags::CARRY && flag <= Flags::ZERO, "flag [%d] is not valid", flag );

    m_registers.f &= ~flag;
}

bool CPU::_is_flag_set( Flags const flag ) const
{
    ASSERT_MSG( flag >= Flags::CARRY && flag <= Flags::ZERO, "flag [%d] is not valid", flag );

    return ( m_registers.f & flag ) != 0;
}
