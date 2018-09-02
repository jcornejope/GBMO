
/* 
Table 1: Base opcode map
    0	        1	        2	        3	        4	        5	        6	        7	        8	        9	        A	        B	    C	        D	    E	        F
0x 	NOP 	    LD BC,nn 	LD (BC),A 	INC BC 	    INC B 	    DEC B 	    LD B,n 	    RLC A 	    LD (nn),SP 	ADD HL,BC 	LD A,(BC) 	DEC BC 	INC C 	    DEC C 	LD C,n 	    RRC A
1x 	STOP 	    LD DE,nn 	LD (DE),A 	INC DE 	    INC D 	    DEC D 	    LD D,n 	    RL A 	    JR n 	    ADD HL,DE 	LD A,(DE) 	DEC DE 	INC E 	    DEC E 	LD E,n 	    RR A
2x 	JR NZ,n 	LD HL,nn 	LDI (HL),A 	INC HL 	    INC H 	    DEC H 	    LD H,n 	    DAA 	    JR Z,n 	    ADD HL,HL 	LDI A,(HL) 	DEC HL 	INC L 	    DEC L 	LD L,n 	    CPL
3x 	JR NC,n 	LD SP,nn 	LDD (HL),A 	INC SP 	    INC (HL) 	DEC (HL) 	LD (HL),n 	SCF 	    JR C,n 	    ADD HL,SP 	LDD A,(HL) 	DEC SP 	INC A 	    DEC A 	LD A,n 	    CCF
4x 	LD B,B 	    LD B,C 	    LD B,D 	    LD B,E 	    LD B,H 	    LD B,L 	    LD B,(HL) 	LD B,A 	    LD C,B 	    LD C,C 	    LD C,D 	    LD C,E 	LD C,H 	    LD C,L 	LD C,(HL) 	LD C,A
5x 	LD D,B 	    LD D,C 	    LD D,D 	    LD D,E 	    LD D,H 	    LD D,L 	    LD D,(HL) 	LD D,A 	    LD E,B 	    LD E,C 	    LD E,D 	    LD E,E 	LD E,H 	    LD E,L 	LD E,(HL) 	LD E,A
6x 	LD H,B 	    LD H,C 	    LD H,D 	    LD H,E 	    LD H,H 	    LD H,L 	    LD H,(HL) 	LD H,A 	    LD L,B 	    LD L,C 	    LD L,D 	    LD L,E 	LD L,H 	    LD L,L 	LD L,(HL) 	LD L,A
7x 	LD (HL),B 	LD (HL),C 	LD (HL),D 	LD (HL),E 	LD (HL),H 	LD (HL),L 	HALT 	    LD (HL),A 	LD A,B 	    LD A,C 	    LD A,D 	    LD A,E 	LD A,H 	    LD A,L 	LD A,(HL) 	LD A,A
8x 	ADD A,B 	ADD A,C 	ADD A,D 	ADD A,E 	ADD A,H 	ADD A,L 	ADD A,(HL) 	ADD A,A 	ADC A,B 	ADC A,C 	ADC A,D 	ADC A,E ADC A,H     ADC A,L ADC A,(HL) 	ADC A,A
9x 	SUB A,B 	SUB A,C 	SUB A,D 	SUB A,E 	SUB A,H 	SUB A,L 	SUB A,(HL) 	SUB A,A 	SBC A,B 	SBC A,C 	SBC A,D 	SBC A,E SBC A,H     SBC A,L SBC A,(HL) 	SBC A,A
Ax 	AND B 	    AND C 	    AND D 	    AND E 	    AND H 	    AND L 	    AND (HL) 	AND A 	    XOR B 	    XOR C 	    XOR D 	    XOR E 	XOR H 	    XOR L 	XOR (HL) 	XOR A
Bx 	OR B 	    OR C 	    OR D 	    OR E 	    OR H 	    OR L 	    OR (HL) 	OR A 	    CP B 	    CP C 	    CP D 	    CP E 	CP H 	    CP L 	CP (HL) 	CP A
Cx 	RET NZ 	    POP BC 	    JP NZ,nn 	JP nn 	    CALL NZ,nn 	PUSH BC 	ADD A,n 	RST 0 	    RET Z 	    RET 	    JP Z,nn 	Ext ops CALL Z,nn 	CALL nn	ADC A,n 	RST 8
Dx 	RET NC 	    POP DE 	    JP NC,nn 	XX 	        CALL NC,nn 	PUSH DE 	SUB A,n 	RST 10 	    RET C 	    RETI 	    JP C,nn 	XX 	    CALL C,nn 	XX 	    SBC A,n 	RST 18
Ex 	LD (n),A 	POP HL 	    LD (C),A 	XX 	        XX 	        PUSH HL 	AND n 	    RST 20 	    ADD SP,d 	JP (HL) 	LD (nn),A 	XX 	    XX 	        XX 	    XOR n 	    RST 28
Fx 	LD A,(n) 	POP AF 	    LD A,(C)    DI 	        XX 	        PUSH AF 	OR n 	    RST 30 	    LDHL SP,d 	LD SP,HL 	LD A,(nn) 	EI 	    XX 	        XX 	    CP n 	    RST 38

Table 2: CB-prefix opcode map
    0	        1	        2	        3	        4	        5	        6	        7	        8	        9	        A	        B	    C	        D	    E	        F
0x 	RLC B 	    RLC C 	    RLC D 	    RLC E 	    RLC H 	    RLC L 	    RLC (HL) 	RLC A 	    RRC B 	    RRC C 	    RRC D 	    RRC E 	RRC H 	    RRC L 	RRC (HL) 	RRC A
1x 	RL B 	    RL C 	    RL D 	    RL E 	    RL H 	    RL L 	    RL (HL) 	RL A 	    RR B 	    RR C 	    RR D 	    RR E 	RR H 	    RR L 	RR (HL) 	RR A
2x 	SLA B 	    SLA C 	    SLA D 	    SLA E 	    SLA H 	    SLA L 	    SLA (HL) 	SLA A 	    SRA B 	    SRA C 	    SRA D 	    SRA E 	SRA H 	    SRA L 	SRA (HL) 	SRA A
3x 	SWAP B 	    SWAP C 	    SWAP D 	    SWAP E 	    SWAP H 	    SWAP L 	    SWAP (HL) 	SWAP A 	    SRL B 	    SRL C 	    SRL D 	    SRL E 	SRL H 	    SRL L 	SRL (HL) 	SRL A
4x 	BIT 0,B     BIT 0,C     BIT 0,D     BIT 0,E     BIT 0,H     BIT 0,L     BIT 0,(HL) 	BIT 0,A     BIT 1,B     BIT 1,C     BIT 1,D     BIT 1,E BIT 1,H     BIT 1,L BIT 1,(HL) 	BIT 1,A
5x 	BIT 2,B     BIT 2,C     BIT 2,D     BIT 2,E     BIT 2,H     BIT 2,L     BIT 2,(HL) 	BIT 2,A     BIT 3,B     BIT 3,C     BIT 3,D     BIT 3,E BIT 3,H     BIT 3,L BIT 3,(HL) 	BIT 3,A
6x 	BIT 4,B     BIT 4,C     BIT 4,D     BIT 4,E     BIT 4,H     BIT 4,L     BIT 4,(HL) 	BIT 4,A     BIT 5,B     BIT 5,C     BIT 5,D     BIT 5,E BIT 5,H     BIT 5,L BIT 5,(HL) 	BIT 5,A
7x 	BIT 6,B     BIT 6,C     BIT 6,D     BIT 6,E     BIT 6,H     BIT 6,L     BIT 6,(HL) 	BIT 6,A     BIT 7,B     BIT 7,C     BIT 7,D     BIT 7,E BIT 7,H     BIT 7,L BIT 7,(HL) 	BIT 7,A
8x 	RES 0,B     RES 0,C     RES 0,D     RES 0,E     RES 0,H     RES 0,L     RES 0,(HL) 	RES 0,A     RES 1,B     RES 1,C     RES 1,D     RES 1,E RES 1,H     RES 1,L RES 1,(HL) 	RES 1,A
9x 	RES 2,B     RES 2,C     RES 2,D     RES 2,E     RES 2,H     RES 2,L     RES 2,(HL) 	RES 2,A     RES 3,B     RES 3,C     RES 3,D     RES 3,E RES 3,H     RES 3,L RES 3,(HL) 	RES 3,A
Ax 	RES 4,B     RES 4,C     RES 4,D     RES 4,E     RES 4,H     RES 4,L     RES 4,(HL) 	RES 4,A     RES 5,B     RES 5,C     RES 5,D     RES 5,E RES 5,H     RES 5,L RES 5,(HL) 	RES 5,A
Bx 	RES 6,B     RES 6,C     RES 6,D     RES 6,E     RES 6,H     RES 6,L     RES 6,(HL) 	RES 6,A     RES 7,B     RES 7,C     RES 7,D     RES 7,E RES 7,H     RES 7,L RES 7,(HL) 	RES 7,A
Cx 	SET 0,B     SET 0,C     SET 0,D     SET 0,E     SET 0,H     SET 0,L     SET 0,(HL) 	SET 0,A     SET 1,B     SET 1,C     SET 1,D     SET 1,E SET 1,H     SET 1,L SET 1,(HL) 	SET 1,A
Dx 	SET 2,B     SET 2,C     SET 2,D     SET 2,E     SET 2,H     SET 2,L     SET 2,(HL) 	SET 2,A     SET 3,B     SET 3,C     SET 3,D     SET 3,E SET 3,H     SET 3,L SET 3,(HL) 	SET 3,A
Ex 	SET 4,B     SET 4,C     SET 4,D     SET 4,E     SET 4,H     SET 4,L     SET 4,(HL) 	SET 4,A     SET 5,B     SET 5,C     SET 5,D     SET 5,E SET 5,H     SET 5,L SET 5,(HL) 	SET 5,A
Fx 	SET 6,B     SET 6,C     SET 6,D     SET 6,E     SET 6,H     SET 6,L     SET 6,(HL) 	SET 6,A     SET 7,B     SET 7,C     SET 7,D     SET 7,E SET 7,H     SET 7,L SET 7,(HL) 	SET 7,A
*/

#include "cpu.h"
#include "memory/memory_system.h"

#include <cassert>

// Instruction set
void CPU::_initialize_instruction_tables()
{
    using namespace std;

    m_base_instruction[0x00] = [this]() { ++m_registers.pc; return 4; };
    m_base_instruction[0x01] = bind( &CPU::_ld_rr_nn, this, ref( m_registers.bc ) );
    m_base_instruction[0x02] = [this]() { m_memory.write( m_registers.bc, m_registers.a ); return 8; };
    m_base_instruction[0x03] = bind( &CPU::_inc_dec, this, ref( m_registers.bc ), true );
    m_base_instruction[0x04] = bind( &CPU::_inc_r, this, ref( m_registers.b ) );
    m_base_instruction[0x05] = bind( &CPU::_dec_r, this, ref( m_registers.b ) );
    m_base_instruction[0x06] = bind( &CPU::_ld_r_n, this, ref( m_registers.b ) );
    m_base_instruction[0x07] = bind( &CPU::_rla_rlca, this, true );
    m_base_instruction[0x08] = bind( &CPU::_ld_nn_sp, this );
    m_base_instruction[0x09] = bind( &CPU::_add_hl, this, cref( m_registers.bc ) );
    m_base_instruction[0x0A] = bind( &CPU::_ld_a_mem, this, cref( m_registers.bc ) );
    m_base_instruction[0x0B] = bind( &CPU::_inc_dec, this, ref( m_registers.bc ), false );
    m_base_instruction[0x0C] = bind( &CPU::_inc_r, this, ref( m_registers.c ) );
    m_base_instruction[0x0D] = bind( &CPU::_dec_r, this, ref( m_registers.c ) );
    m_base_instruction[0x0E] = bind( &CPU::_ld_r_n, this, ref( m_registers.c ) );
    m_base_instruction[0x0F] = bind( &CPU::_rra_rrca, this, false );
    m_base_instruction[0x10] = [this]() { assert( false ); m_registers.pc++; return 0; }; // STOP - IMPLEMENT THIS!!
    m_base_instruction[0x11] = bind( &CPU::_ld_rr_nn, this, ref( m_registers.de ) );
    m_base_instruction[0x12] = [this]() { m_memory.write( m_registers.de, m_registers.a ); return 8; };
    m_base_instruction[0x13] = bind( &CPU::_inc_dec, this, ref( m_registers.de ), true );
    m_base_instruction[0x14] = bind( &CPU::_inc_r, this, ref( m_registers.d ) );
    m_base_instruction[0x15] = bind( &CPU::_dec_r, this, ref( m_registers.d ) );
    m_base_instruction[0x16] = bind( &CPU::_ld_r_n, this, ref( m_registers.d ) );
    m_base_instruction[0x17] = bind( &CPU::_rla_rlca, this, false );
    m_base_instruction[0x18] = bind( &CPU::_jump_relative, this, JumpCondition::NO_CONDITION );
    m_base_instruction[0x19] = bind( &CPU::_add_hl, this, cref( m_registers.de ) );
    m_base_instruction[0x1A] = bind( &CPU::_ld_a_mem, this, cref( m_registers.de ) );
    m_base_instruction[0x1B] = bind( &CPU::_inc_dec, this, ref( m_registers.de ), false );
    m_base_instruction[0x1C] = bind( &CPU::_inc_r, this, ref( m_registers.e ) );
    m_base_instruction[0x1D] = bind( &CPU::_dec_r, this, ref( m_registers.e ) );
    m_base_instruction[0x1E] = bind( &CPU::_ld_r_n, this, ref( m_registers.e ) );
    m_base_instruction[0x1F] = bind( &CPU::_rra_rrca, this, true );
    m_base_instruction[0x20] = bind( &CPU::_jump_relative, this, JumpCondition::NO_ZERO );
    m_base_instruction[0x21] = bind( &CPU::_ld_rr_nn, this, ref( m_registers.hl ) );
    m_base_instruction[0x22] = bind( &CPU::_ld_inc_dec_hl_a, this, s8( 1 ) );
    m_base_instruction[0x23] = bind( &CPU::_inc_dec, this, ref( m_registers.hl ), true );
    m_base_instruction[0x24] = bind( &CPU::_inc_r, this, ref( m_registers.h ) );
    m_base_instruction[0x25] = bind( &CPU::_dec_r, this, ref( m_registers.h ) );
    m_base_instruction[0x26] = bind( &CPU::_ld_r_n, this, ref( m_registers.h ) );
    m_base_instruction[0x27] = bind( &CPU::_decimal_adjust_acc, this );
    m_base_instruction[0x28] = bind( &CPU::_jump_relative, this, JumpCondition::ZERO );
    m_base_instruction[0x29] = bind( &CPU::_add_hl, this, cref( m_registers.hl ) );
    m_base_instruction[0x2A] = bind( &CPU::_ld_inc_dec_a_hl, this, s8( 1 ) );
    m_base_instruction[0x2B] = bind( &CPU::_inc_dec, this, ref( m_registers.hl ), false );
    m_base_instruction[0x2C] = bind( &CPU::_inc_r, this, ref( m_registers.l ) );
    m_base_instruction[0x2D] = bind( &CPU::_dec_r, this, ref( m_registers.l ) );
    m_base_instruction[0x2E] = bind( &CPU::_ld_r_n, this, ref( m_registers.l ) );
    m_base_instruction[0x2F] = bind( &CPU::_complement, this );
    m_base_instruction[0x30] = bind( &CPU::_jump_relative, this, JumpCondition::NO_CARRY );
    m_base_instruction[0x31] = bind( &CPU::_ld_rr_nn, this, ref( m_registers.sp ) );
    m_base_instruction[0x32] = bind( &CPU::_ld_inc_dec_hl_a, this, s8( -1 ) );
    m_base_instruction[0x33] = bind( &CPU::_inc_dec, this, ref( m_registers.sp ), true );
    m_base_instruction[0x34] = bind( &CPU::_inc_hl, this );
    m_base_instruction[0x35] = bind( &CPU::_dec_hl, this );
    m_base_instruction[0x36] = bind( &CPU::_ld_hl_n, this );
    m_base_instruction[0x37] = bind( &CPU::_scf, this );
    m_base_instruction[0x38] = bind( &CPU::_jump_relative, this, JumpCondition::CARRY );
    m_base_instruction[0x39] = bind( &CPU::_add_hl, this, cref( m_registers.sp ) );
    m_base_instruction[0x3A] = bind( &CPU::_ld_inc_dec_a_hl, this, s8( -1 ) );
    m_base_instruction[0x3B] = bind( &CPU::_inc_dec, this, ref( m_registers.sp ), false );
    m_base_instruction[0x3C] = bind( &CPU::_inc_r, this, ref( m_registers.a ) );
    m_base_instruction[0x3D] = bind( &CPU::_dec_r, this, ref( m_registers.a ) );
    m_base_instruction[0x3E] = bind( &CPU::_ld_r_n, this, ref( m_registers.a ) );
    m_base_instruction[0x3F] = bind( &CPU::_ccf, this );
    m_base_instruction[0x40] = [this]() { m_registers.b = m_registers.b; return 4; }; //_ld_r_r
    m_base_instruction[0x41] = [this]() { m_registers.b = m_registers.c; return 4; };
    m_base_instruction[0x42] = [this]() { m_registers.b = m_registers.d; return 4; };
    m_base_instruction[0x43] = [this]() { m_registers.b = m_registers.e; return 4; };
    m_base_instruction[0x44] = [this]() { m_registers.b = m_registers.h; return 4; };
    m_base_instruction[0x45] = [this]() { m_registers.b = m_registers.l; return 4; };
    m_base_instruction[0x46] = bind( &CPU::_ld_r_hl, this, ref( m_registers.b ) );
    m_base_instruction[0x47] = [this]() { m_registers.b = m_registers.a; return 4; };
    m_base_instruction[0x48] = [this]() { m_registers.c = m_registers.b; return 4; };
    m_base_instruction[0x49] = [this]() { m_registers.c = m_registers.c; return 4; };
    m_base_instruction[0x4A] = [this]() { m_registers.c = m_registers.d; return 4; };
    m_base_instruction[0x4B] = [this]() { m_registers.c = m_registers.e; return 4; };
    m_base_instruction[0x4C] = [this]() { m_registers.c = m_registers.h; return 4; };
    m_base_instruction[0x4D] = [this]() { m_registers.c = m_registers.l; return 4; };
    m_base_instruction[0x4E] = bind( &CPU::_ld_r_hl, this, ref( m_registers.c ) );
    m_base_instruction[0x4F] = [this]() { m_registers.c = m_registers.a; return 4; };
    m_base_instruction[0x50] = [this]() { m_registers.d = m_registers.b; return 4; };
    m_base_instruction[0x51] = [this]() { m_registers.d = m_registers.c; return 4; };
    m_base_instruction[0x52] = [this]() { m_registers.d = m_registers.d; return 4; };
    m_base_instruction[0x53] = [this]() { m_registers.d = m_registers.e; return 4; };
    m_base_instruction[0x54] = [this]() { m_registers.d = m_registers.h; return 4; };
    m_base_instruction[0x55] = [this]() { m_registers.d = m_registers.l; return 4; };
    m_base_instruction[0x56] = bind( &CPU::_ld_r_hl, this, ref( m_registers.d ) );
    m_base_instruction[0x57] = [this]() { m_registers.d = m_registers.a; return 4; };
    m_base_instruction[0x58] = [this]() { m_registers.e = m_registers.b; return 4; };
    m_base_instruction[0x59] = [this]() { m_registers.e = m_registers.c; return 4; };
    m_base_instruction[0x5A] = [this]() { m_registers.e = m_registers.d; return 4; };
    m_base_instruction[0x5B] = [this]() { m_registers.e = m_registers.e; return 4; };
    m_base_instruction[0x5C] = [this]() { m_registers.e = m_registers.h; return 4; };
    m_base_instruction[0x5D] = [this]() { m_registers.e = m_registers.l; return 4; };
    m_base_instruction[0x5E] = bind( &CPU::_ld_r_hl, this, ref( m_registers.e ) );
    m_base_instruction[0x5F] = [this]() { m_registers.e = m_registers.a; return 4; };
    m_base_instruction[0x60] = [this]() { m_registers.h = m_registers.b; return 4; };
    m_base_instruction[0x61] = [this]() { m_registers.h = m_registers.c; return 4; };
    m_base_instruction[0x62] = [this]() { m_registers.h = m_registers.d; return 4; };
    m_base_instruction[0x63] = [this]() { m_registers.h = m_registers.e; return 4; };
    m_base_instruction[0x64] = [this]() { m_registers.h = m_registers.h; return 4; };
    m_base_instruction[0x65] = [this]() { m_registers.h = m_registers.l; return 4; };
    m_base_instruction[0x66] = bind( &CPU::_ld_r_hl, this, ref( m_registers.h ) );
    m_base_instruction[0x67] = [this]() { m_registers.h = m_registers.a; return 4; };
    m_base_instruction[0x68] = [this]() { m_registers.l = m_registers.b; return 4; };
    m_base_instruction[0x69] = [this]() { m_registers.l = m_registers.c; return 4; };
    m_base_instruction[0x6A] = [this]() { m_registers.l = m_registers.d; return 4; };
    m_base_instruction[0x6B] = [this]() { m_registers.l = m_registers.e; return 4; };
    m_base_instruction[0x6C] = [this]() { m_registers.l = m_registers.h; return 4; };
    m_base_instruction[0x6D] = [this]() { m_registers.l = m_registers.l; return 4; };
    m_base_instruction[0x6E] = bind( &CPU::_ld_r_hl, this, ref( m_registers.l ) );
    m_base_instruction[0x6F] = [this]() { m_registers.l = m_registers.a; return 4; };
    m_base_instruction[0x70] = bind( &CPU::_ld_hl_r, this, cref( m_registers.b ) );
    m_base_instruction[0x71] = bind( &CPU::_ld_hl_r, this, cref( m_registers.c ) );
    m_base_instruction[0x72] = bind( &CPU::_ld_hl_r, this, cref( m_registers.d ) );
    m_base_instruction[0x73] = bind( &CPU::_ld_hl_r, this, cref( m_registers.e ) );
    m_base_instruction[0x74] = bind( &CPU::_ld_hl_r, this, cref( m_registers.h ) );
    m_base_instruction[0x75] = bind( &CPU::_ld_hl_r, this, cref( m_registers.l ) );
    m_base_instruction[0x76] = [this]() { assert( false ); m_registers.pc++; return 0; }; // HALT - IMPLEMENT THIS!!
    m_base_instruction[0x77] = bind( &CPU::_ld_hl_r, this, cref( m_registers.a ) );
    m_base_instruction[0x78] = [this]() { m_registers.a = m_registers.b; return 4; };
    m_base_instruction[0x79] = [this]() { m_registers.a = m_registers.c; return 4; };
    m_base_instruction[0x7A] = [this]() { m_registers.a = m_registers.d; return 4; };
    m_base_instruction[0x7B] = [this]() { m_registers.a = m_registers.e; return 4; };
    m_base_instruction[0x7C] = [this]() { m_registers.a = m_registers.h; return 4; };
    m_base_instruction[0x7D] = [this]() { m_registers.a = m_registers.l; return 4; };
    m_base_instruction[0x7E] = bind( &CPU::_ld_r_hl, this, ref( m_registers.a ) );
    m_base_instruction[0x7F] = [this]() { m_registers.a = m_registers.a; return 4; };
    m_base_instruction[0x80] = [this]() { _add( m_registers.b, false ); return 4; };
    m_base_instruction[0x81] = [this]() { _add( m_registers.c, false ); return 4; };
    m_base_instruction[0x82] = [this]() { _add( m_registers.d, false ); return 4; };
    m_base_instruction[0x83] = [this]() { _add( m_registers.e, false ); return 4; };
    m_base_instruction[0x84] = [this]() { _add( m_registers.h, false ); return 4; };
    m_base_instruction[0x85] = [this]() { _add( m_registers.l, false ); return 4; };
    m_base_instruction[0x86] = [this]() { _add( m_memory.read_8( m_registers.hl ), false ); return 8; };
    m_base_instruction[0x87] = [this]() { _add( m_registers.a, false ); return 4; };
    m_base_instruction[0x88] = [this]() { _add( m_registers.b, true ); return 4; };
    m_base_instruction[0x89] = [this]() { _add( m_registers.c, true ); return 4; };
    m_base_instruction[0x8A] = [this]() { _add( m_registers.d, true ); return 4; };
    m_base_instruction[0x8B] = [this]() { _add( m_registers.e, true ); return 4; };
    m_base_instruction[0x8C] = [this]() { _add( m_registers.h, true ); return 4; };
    m_base_instruction[0x8D] = [this]() { _add( m_registers.l, true ); return 4; };
    m_base_instruction[0x8E] = [this]() { _add( m_memory.read_8( m_registers.hl ), true ); return 8; };
    m_base_instruction[0x8F] = [this]() { _add( m_registers.a, true ); return 4; };
    m_base_instruction[0x90] = [this]() { _sub( m_registers.b, false ); return 4; };
    m_base_instruction[0x91] = [this]() { _sub( m_registers.c, false ); return 4; };
    m_base_instruction[0x92] = [this]() { _sub( m_registers.d, false ); return 4; };
    m_base_instruction[0x93] = [this]() { _sub( m_registers.e, false ); return 4; };
    m_base_instruction[0x94] = [this]() { _sub( m_registers.h, false ); return 4; };
    m_base_instruction[0x95] = [this]() { _sub( m_registers.l, false ); return 4; };
    m_base_instruction[0x96] = [this]() { _sub( m_memory.read_8( m_registers.hl ), false ); return 8; };
    m_base_instruction[0x97] = [this]() { _sub( m_registers.a, false ); return 4; };
    m_base_instruction[0x98] = [this]() { _sub( m_registers.b, true ); return 4; };
    m_base_instruction[0x99] = [this]() { _sub( m_registers.c, true ); return 4; };
    m_base_instruction[0x9A] = [this]() { _sub( m_registers.d, true ); return 4; };
    m_base_instruction[0x9B] = [this]() { _sub( m_registers.e, true ); return 4; };
    m_base_instruction[0x9C] = [this]() { _sub( m_registers.h, true ); return 4; };
    m_base_instruction[0x9D] = [this]() { _sub( m_registers.l, true ); return 4; };
    m_base_instruction[0x9E] = [this]() { _sub( m_memory.read_8( m_registers.hl ), true ); return 8; };
    m_base_instruction[0x9F] = [this]() { _sub( m_registers.a, true ); return 4; };
    m_base_instruction[0xA0] = [this]() { _and( m_registers.b ); return 4; };
    m_base_instruction[0xA1] = [this]() { _and( m_registers.c ); return 4; };
    m_base_instruction[0xA2] = [this]() { _and( m_registers.d ); return 4; };
    m_base_instruction[0xA3] = [this]() { _and( m_registers.e ); return 4; };
    m_base_instruction[0xA4] = [this]() { _and( m_registers.h ); return 4; };
    m_base_instruction[0xA5] = [this]() { _and( m_registers.l ); return 4; };
    m_base_instruction[0xA6] = [this]() { _and( m_memory.read_8( m_registers.hl ) ); return 8; };
    m_base_instruction[0xA7] = [this]() { _and( m_registers.a ); return 4; };
    m_base_instruction[0xA8] = [this]() { _xor( m_registers.b ); return 4; };
    m_base_instruction[0xA9] = [this]() { _xor( m_registers.c ); return 4; };
    m_base_instruction[0xAA] = [this]() { _xor( m_registers.d ); return 4; };
    m_base_instruction[0xAB] = [this]() { _xor( m_registers.e ); return 4; };
    m_base_instruction[0xAC] = [this]() { _xor( m_registers.h ); return 4; };
    m_base_instruction[0xAD] = [this]() { _xor( m_registers.l ); return 4; };
    m_base_instruction[0xAE] = [this]() { _xor( m_memory.read_8( m_registers.hl ) ); return 8; };
    m_base_instruction[0xAF] = [this]() { _xor( m_registers.a ); return 4; };
    m_base_instruction[0xB0] = [this]() { _or( m_registers.b ); return 4; };
    m_base_instruction[0xB1] = [this]() { _or( m_registers.c ); return 4; };
    m_base_instruction[0xB2] = [this]() { _or( m_registers.d ); return 4; };
    m_base_instruction[0xB3] = [this]() { _or( m_registers.e ); return 4; };
    m_base_instruction[0xB4] = [this]() { _or( m_registers.h ); return 4; };
    m_base_instruction[0xB5] = [this]() { _or( m_registers.l ); return 4; };
    m_base_instruction[0xB6] = [this]() { _or( m_memory.read_8( m_registers.hl ) ); return 8; };
    m_base_instruction[0xB7] = [this]() { _or( m_registers.a ); return 4; };
    m_base_instruction[0xB8] = [this]() { _cmp( m_registers.b ); return 4; };
    m_base_instruction[0xB9] = [this]() { _cmp( m_registers.c ); return 4; };
    m_base_instruction[0xBA] = [this]() { _cmp( m_registers.d ); return 4; };
    m_base_instruction[0xBB] = [this]() { _cmp( m_registers.e ); return 4; };
    m_base_instruction[0xBC] = [this]() { _cmp( m_registers.h ); return 4; };
    m_base_instruction[0xBD] = [this]() { _cmp( m_registers.l ); return 4; };
    m_base_instruction[0xBE] = [this]() { _cmp( m_memory.read_8( m_registers.hl ) ); return 8; };
    m_base_instruction[0xBF] = [this]() { _cmp( m_registers.a ); return 4; };
    m_base_instruction[0xC0] = bind( &CPU::_ret, this, JumpCondition::NO_ZERO );
    m_base_instruction[0xC1] = bind( &CPU::_pop, this, ref( m_registers.bc ) );
    m_base_instruction[0xC2] = bind( &CPU::_jump, this, JumpCondition::NO_ZERO );
    m_base_instruction[0xC3] = bind( &CPU::_jump, this, JumpCondition::NO_CONDITION );
    m_base_instruction[0xC4] = bind( &CPU::_call, this, JumpCondition::NO_ZERO );
    m_base_instruction[0xC5] = bind( &CPU::_push, this, ref( m_registers.bc ) );
    m_base_instruction[0xC6] = [this]() { _add( m_memory.read_8( m_registers.pc++ ), false ); return 8; };
    m_base_instruction[0xC7] = bind( &CPU::_call_routine, this, u8( 0x00 ) );
    m_base_instruction[0xC8] = bind( &CPU::_ret, this, JumpCondition::ZERO );
    m_base_instruction[0xC9] = bind( &CPU::_ret, this, JumpCondition::NO_CONDITION );
    m_base_instruction[0xCA] = bind( &CPU::_jump, this, JumpCondition::ZERO );
    m_base_instruction[0xCB] = bind( &CPU::_reroute_to_cb_table, this ); // Re-route to ext instructions table.
    m_base_instruction[0xCC] = bind( &CPU::_call, this, JumpCondition::ZERO );
    m_base_instruction[0xCD] = bind( &CPU::_call, this, JumpCondition::NO_CONDITION );
    m_base_instruction[0xCE] = [this]() { _add( m_memory.read_8( m_registers.pc++ ), true ); return 8; };
    m_base_instruction[0xCF] = bind( &CPU::_call_routine, this, u8( 0x08 ) );
    m_base_instruction[0xD0] = bind( &CPU::_ret, this, JumpCondition::NO_CARRY );
    m_base_instruction[0xD1] = bind( &CPU::_pop, this, ref( m_registers.de ) );
    m_base_instruction[0xD2] = bind( &CPU::_jump, this, JumpCondition::NO_CARRY );
    m_base_instruction[0xD3] = nullptr; // NO INSTRUCTION
    m_base_instruction[0xD4] = bind( &CPU::_call, this, JumpCondition::NO_CARRY );
    m_base_instruction[0xD5] = bind( &CPU::_push, this, ref( m_registers.bc ) );
    m_base_instruction[0xD6] = [this]() { _sub( m_memory.read_8( m_registers.pc++ ), false ); return 8; };
    m_base_instruction[0xD7] = bind( &CPU::_call_routine, this, u8( 0x10 ) );
    m_base_instruction[0xD8] = bind( &CPU::_ret, this, JumpCondition::CARRY );
    m_base_instruction[0xD9] = bind( &CPU::_reti, this );
    m_base_instruction[0xDA] = bind( &CPU::_jump, this, JumpCondition::CARRY );
    m_base_instruction[0xDB] = nullptr; // NO INSTRUCTION
    m_base_instruction[0xDC] = bind( &CPU::_call, this, JumpCondition::CARRY );
    m_base_instruction[0xDD] = nullptr; // NO INSTRUCTION
    m_base_instruction[0xDE] = [this]() { _sub( m_memory.read_8( m_registers.pc++ ), true ); return 8; };
    m_base_instruction[0xDF] = bind( &CPU::_call_routine, this, u8( 0x18 ) );
    m_base_instruction[0xE0] = bind( &CPU::_ld_io_n_a, this );
    m_base_instruction[0xE1] = bind( &CPU::_pop, this, ref( m_registers.hl ) );
    m_base_instruction[0xE2] = bind( &CPU::_ld_io_c_a, this );
    m_base_instruction[0xE3] = nullptr; // NO INSTRUCTION
    m_base_instruction[0xE4] = nullptr; // NO INSTRUCTION
    m_base_instruction[0xE5] = bind( &CPU::_push, this, ref( m_registers.hl ) );
    m_base_instruction[0xE6] = [this]() { _and( m_memory.read_8( m_registers.pc++ ) ); return 8; };
    m_base_instruction[0xE7] = bind( &CPU::_call_routine, this, u8( 0x20 ) );
    m_base_instruction[0xE8] = bind( &CPU::_add_sp, this );
    m_base_instruction[0xE9] = bind( &CPU::_jump_hl, this );
    m_base_instruction[0xEA] = bind( &CPU::_ld_nn_a, this );
    m_base_instruction[0xEB] = nullptr; // NO INSTRUCTION
    m_base_instruction[0xEC] = nullptr; // NO INSTRUCTION
    m_base_instruction[0xED] = nullptr; // NO INSTRUCTION
    m_base_instruction[0xEE] = [this]() { _xor( m_memory.read_8( m_registers.pc++ ) ); return 8; };
    m_base_instruction[0xEF] = bind( &CPU::_call_routine, this, u8( 0x28 ) );
    m_base_instruction[0xF0] = bind( &CPU::_ld_a_io_n, this );
    m_base_instruction[0xF1] = bind( &CPU::_pop, this, ref( m_registers.af ) );
    m_base_instruction[0xF2] = bind( &CPU::_ld_a_io_c, this );
    m_base_instruction[0xF3] = [this]() { m_ime = false; return 4; }; // TODO: Review DI implementation once interrupts are implemented
    m_base_instruction[0xF4] = nullptr; // NO INSTRUCTION
    m_base_instruction[0xF5] = bind( &CPU::_push, this, ref( m_registers.af ) );
    m_base_instruction[0xF6] = [this]() { _or( m_memory.read_8( m_registers.pc++ ) ); return 8; };
    m_base_instruction[0xF7] = bind( &CPU::_call_routine, this, u8( 0x30 ) );
    m_base_instruction[0xF8] = bind( &CPU::_ldhl, this );
    m_base_instruction[0xF9] = bind( &CPU::_ld_sp_hl, this );
    m_base_instruction[0xFA] = bind( &CPU::_ld_a_nn, this );
    m_base_instruction[0xFB] = [this]() { m_ime = true; return 4; }; // TODO: Review EI implementation once interrupts are implemented 
    m_base_instruction[0xFC] = nullptr; // NO INSTRUCTION
    m_base_instruction[0xFD] = nullptr; // NO INSTRUCTION
    m_base_instruction[0xFE] = [this]() { _cmp( m_memory.read_8( m_registers.pc++ ) ); return 8; };
    m_base_instruction[0xFF] = bind( &CPU::_call_routine, this, u8( 0x38 ) );

    m_cb_prefix_instruction[0x00] = [this]() { _rl_rlc( m_registers.b, true ); return 8; };
    m_cb_prefix_instruction[0x01] = [this]() { _rl_rlc( m_registers.c, true ); return 8; };
    m_cb_prefix_instruction[0x02] = [this]() { _rl_rlc( m_registers.d, true ); return 8; };
    m_cb_prefix_instruction[0x03] = [this]() { _rl_rlc( m_registers.e, true ); return 8; };
    m_cb_prefix_instruction[0x04] = [this]() { _rl_rlc( m_registers.h, true ); return 8; };
    m_cb_prefix_instruction[0x05] = [this]() { _rl_rlc( m_registers.l, true ); return 8; };
    m_cb_prefix_instruction[0x06] = bind( &CPU::_rl_rlc_hl, this, true );
    m_cb_prefix_instruction[0x07] = [this]() { _rl_rlc( m_registers.a, true ); return 8; };
    m_cb_prefix_instruction[0x08] = [this]() { _rr_rrc( m_registers.b, true ); return 8; };
    m_cb_prefix_instruction[0x09] = [this]() { _rr_rrc( m_registers.c, true ); return 8; };
    m_cb_prefix_instruction[0x0A] = [this]() { _rr_rrc( m_registers.d, true ); return 8; };
    m_cb_prefix_instruction[0x0B] = [this]() { _rr_rrc( m_registers.e, true ); return 8; };
    m_cb_prefix_instruction[0x0C] = [this]() { _rr_rrc( m_registers.h, true ); return 8; };
    m_cb_prefix_instruction[0x0D] = [this]() { _rr_rrc( m_registers.l, true ); return 8; };
    m_cb_prefix_instruction[0x0E] = bind( &CPU::_rr_rrc_hl, this, true );
    m_cb_prefix_instruction[0x0F] = [this]() { _rr_rrc( m_registers.a, true ); return 8; };
    m_cb_prefix_instruction[0x10] = [this]() { _rl_rlc( m_registers.b, false ); return 8; };
    m_cb_prefix_instruction[0x11] = [this]() { _rl_rlc( m_registers.c, false ); return 8; };
    m_cb_prefix_instruction[0x12] = [this]() { _rl_rlc( m_registers.d, false ); return 8; };
    m_cb_prefix_instruction[0x13] = [this]() { _rl_rlc( m_registers.e, false ); return 8; };
    m_cb_prefix_instruction[0x14] = [this]() { _rl_rlc( m_registers.h, false ); return 8; };
    m_cb_prefix_instruction[0x15] = [this]() { _rl_rlc( m_registers.l, false ); return 8; };
    m_cb_prefix_instruction[0x16] = bind( &CPU::_rl_rlc_hl, this, false );
    m_cb_prefix_instruction[0x17] = [this]() { _rl_rlc( m_registers.a, false ); return 8; };
    m_cb_prefix_instruction[0x18] = [this]() { _rr_rrc( m_registers.b, false ); return 8; };
    m_cb_prefix_instruction[0x19] = [this]() { _rr_rrc( m_registers.c, false ); return 8; };
    m_cb_prefix_instruction[0x1A] = [this]() { _rr_rrc( m_registers.d, false ); return 8; };
    m_cb_prefix_instruction[0x1B] = [this]() { _rr_rrc( m_registers.e, false ); return 8; };
    m_cb_prefix_instruction[0x1C] = [this]() { _rr_rrc( m_registers.h, false ); return 8; };
    m_cb_prefix_instruction[0x1D] = [this]() { _rr_rrc( m_registers.l, false ); return 8; };
    m_cb_prefix_instruction[0x1E] = bind( &CPU::_rr_rrc_hl, this, false );
    m_cb_prefix_instruction[0x1F] = [this]() { _rr_rrc( m_registers.a, false ); return 8; };
    m_cb_prefix_instruction[0x20] = [this]() { _shift_l( m_registers.b ); return 8; };
    m_cb_prefix_instruction[0x21] = [this]() { _shift_l( m_registers.c ); return 8; };
    m_cb_prefix_instruction[0x22] = [this]() { _shift_l( m_registers.d ); return 8; };
    m_cb_prefix_instruction[0x23] = [this]() { _shift_l( m_registers.e ); return 8; };
    m_cb_prefix_instruction[0x24] = [this]() { _shift_l( m_registers.h ); return 8; };
    m_cb_prefix_instruction[0x25] = [this]() { _shift_l( m_registers.l ); return 8; };
    m_cb_prefix_instruction[0x26] = bind( &CPU::_shift_l_hl, this );
    m_cb_prefix_instruction[0x27] = [this]() { _shift_l( m_registers.a ); return 8; };
    m_cb_prefix_instruction[0x28] = [this]() { _shift_r( m_registers.b, false ); return 8; };
    m_cb_prefix_instruction[0x29] = [this]() { _shift_r( m_registers.c, false ); return 8; };
    m_cb_prefix_instruction[0x2A] = [this]() { _shift_r( m_registers.d, false ); return 8; };
    m_cb_prefix_instruction[0x2B] = [this]() { _shift_r( m_registers.e, false ); return 8; };
    m_cb_prefix_instruction[0x2C] = [this]() { _shift_r( m_registers.h, false ); return 8; };
    m_cb_prefix_instruction[0x2D] = [this]() { _shift_r( m_registers.l, false ); return 8; };
    m_cb_prefix_instruction[0x2E] = bind( &CPU::_shift_r_hl, this, false );
    m_cb_prefix_instruction[0x2F] = [this]() { _shift_r( m_registers.a, false ); return 8; };
    m_cb_prefix_instruction[0x30] = [this]() { _swap( m_registers.b ); return 8; };
    m_cb_prefix_instruction[0x31] = [this]() { _swap( m_registers.c ); return 8; };
    m_cb_prefix_instruction[0x32] = [this]() { _swap( m_registers.d ); return 8; };
    m_cb_prefix_instruction[0x33] = [this]() { _swap( m_registers.e ); return 8; };
    m_cb_prefix_instruction[0x34] = [this]() { _swap( m_registers.h ); return 8; };
    m_cb_prefix_instruction[0x35] = [this]() { _swap( m_registers.l ); return 8; };
    m_cb_prefix_instruction[0x36] = bind( &CPU::_swap_hl, this );
    m_cb_prefix_instruction[0x37] = [this]() { _swap( m_registers.a ); return 8; };
    m_cb_prefix_instruction[0x38] = [this]() { _shift_r( m_registers.b, true ); return 8; };
    m_cb_prefix_instruction[0x39] = [this]() { _shift_r( m_registers.c, true ); return 8; };
    m_cb_prefix_instruction[0x3A] = [this]() { _shift_r( m_registers.d, true ); return 8; };
    m_cb_prefix_instruction[0x3B] = [this]() { _shift_r( m_registers.e, true ); return 8; };
    m_cb_prefix_instruction[0x3C] = [this]() { _shift_r( m_registers.h, true ); return 8; };
    m_cb_prefix_instruction[0x3D] = [this]() { _shift_r( m_registers.l, true ); return 8; };
    m_cb_prefix_instruction[0x3E] = bind( &CPU::_shift_r_hl, this, true );
    m_cb_prefix_instruction[0x3F] = [this]() { _shift_r( m_registers.a, true ); return 8; };
    m_cb_prefix_instruction[0x40] = [this]() { _test_bit( m_registers.b, u8( 0 ) ); return 8; };
    m_cb_prefix_instruction[0x41] = [this]() { _test_bit( m_registers.c, u8( 0 ) ); return 8; };
    m_cb_prefix_instruction[0x42] = [this]() { _test_bit( m_registers.d, u8( 0 ) ); return 8; };
    m_cb_prefix_instruction[0x43] = [this]() { _test_bit( m_registers.e, u8( 0 ) ); return 8; };
    m_cb_prefix_instruction[0x44] = [this]() { _test_bit( m_registers.h, u8( 0 ) ); return 8; };
    m_cb_prefix_instruction[0x45] = [this]() { _test_bit( m_registers.l, u8( 0 ) ); return 8; };
    m_cb_prefix_instruction[0x46] = [this]() { _test_bit( m_memory.read_8( m_registers.hl ), u8( 0 ) ); return 12; };
    m_cb_prefix_instruction[0x47] = [this]() { _test_bit( m_registers.a, u8( 0 ) ); return 8; };
    m_cb_prefix_instruction[0x48] = [this]() { _test_bit( m_registers.b, u8( 1 ) ); return 8; };
    m_cb_prefix_instruction[0x49] = [this]() { _test_bit( m_registers.c, u8( 1 ) ); return 8; };
    m_cb_prefix_instruction[0x4A] = [this]() { _test_bit( m_registers.d, u8( 1 ) ); return 8; };
    m_cb_prefix_instruction[0x4B] = [this]() { _test_bit( m_registers.e, u8( 1 ) ); return 8; };
    m_cb_prefix_instruction[0x4C] = [this]() { _test_bit( m_registers.h, u8( 1 ) ); return 8; };
    m_cb_prefix_instruction[0x4D] = [this]() { _test_bit( m_registers.l, u8( 1 ) ); return 8; };
    m_cb_prefix_instruction[0x4E] = [this]() { _test_bit( m_memory.read_8( m_registers.hl ), 1 ); return 12; };
    m_cb_prefix_instruction[0x4F] = [this]() { _test_bit( m_registers.a, u8( 1 ) ); return 8; };
    m_cb_prefix_instruction[0x50] = [this]() { _test_bit( m_registers.b, u8( 2 ) ); return 8; };
    m_cb_prefix_instruction[0x51] = [this]() { _test_bit( m_registers.c, u8( 2 ) ); return 8; };
    m_cb_prefix_instruction[0x52] = [this]() { _test_bit( m_registers.d, u8( 2 ) ); return 8; };
    m_cb_prefix_instruction[0x53] = [this]() { _test_bit( m_registers.e, u8( 2 ) ); return 8; };
    m_cb_prefix_instruction[0x54] = [this]() { _test_bit( m_registers.h, u8( 2 ) ); return 8; };
    m_cb_prefix_instruction[0x55] = [this]() { _test_bit( m_registers.l, u8( 2 ) ); return 8; };
    m_cb_prefix_instruction[0x56] = [this]() { _test_bit( m_memory.read_8( m_registers.hl ), 2 ); return 12; };
    m_cb_prefix_instruction[0x57] = [this]() { _test_bit( m_registers.a, u8( 2 ) ); return 8; };
    m_cb_prefix_instruction[0x58] = [this]() { _test_bit( m_registers.b, u8( 3 ) ); return 8; };
    m_cb_prefix_instruction[0x59] = [this]() { _test_bit( m_registers.c, u8( 3 ) ); return 8; };
    m_cb_prefix_instruction[0x5A] = [this]() { _test_bit( m_registers.d, u8( 3 ) ); return 8; };
    m_cb_prefix_instruction[0x5B] = [this]() { _test_bit( m_registers.e, u8( 3 ) ); return 8; };
    m_cb_prefix_instruction[0x5C] = [this]() { _test_bit( m_registers.h, u8( 3 ) ); return 8; };
    m_cb_prefix_instruction[0x5D] = [this]() { _test_bit( m_registers.l, u8( 3 ) ); return 8; };
    m_cb_prefix_instruction[0x5E] = [this]() { _test_bit( m_memory.read_8( m_registers.hl ), 3 ); return 12; };
    m_cb_prefix_instruction[0x5F] = [this]() { _test_bit( m_registers.a, u8( 3 ) ); return 8; };
    m_cb_prefix_instruction[0x60] = [this]() { _test_bit( m_registers.b, u8( 4 ) ); return 8; };
    m_cb_prefix_instruction[0x61] = [this]() { _test_bit( m_registers.c, u8( 4 ) ); return 8; };
    m_cb_prefix_instruction[0x62] = [this]() { _test_bit( m_registers.d, u8( 4 ) ); return 8; };
    m_cb_prefix_instruction[0x63] = [this]() { _test_bit( m_registers.e, u8( 4 ) ); return 8; };
    m_cb_prefix_instruction[0x64] = [this]() { _test_bit( m_registers.h, u8( 4 ) ); return 8; };
    m_cb_prefix_instruction[0x65] = [this]() { _test_bit( m_registers.l, u8( 4 ) ); return 8; };
    m_cb_prefix_instruction[0x66] = [this]() { _test_bit( m_memory.read_8( m_registers.hl ), 4 ); return 12; };
    m_cb_prefix_instruction[0x67] = [this]() { _test_bit( m_registers.a, u8( 4 ) ); return 8; };
    m_cb_prefix_instruction[0x68] = [this]() { _test_bit( m_registers.b, u8( 5 ) ); return 8; };
    m_cb_prefix_instruction[0x69] = [this]() { _test_bit( m_registers.c, u8( 5 ) ); return 8; };
    m_cb_prefix_instruction[0x6A] = [this]() { _test_bit( m_registers.d, u8( 5 ) ); return 8; };
    m_cb_prefix_instruction[0x6B] = [this]() { _test_bit( m_registers.e, u8( 5 ) ); return 8; };
    m_cb_prefix_instruction[0x6C] = [this]() { _test_bit( m_registers.h, u8( 5 ) ); return 8; };
    m_cb_prefix_instruction[0x6D] = [this]() { _test_bit( m_registers.l, u8( 5 ) ); return 8; };
    m_cb_prefix_instruction[0x6E] = [this]() { _test_bit( m_memory.read_8( m_registers.hl ), 5 ); return 12; };
    m_cb_prefix_instruction[0x6F] = [this]() { _test_bit( m_registers.a, u8( 5 ) ); return 8; };
    m_cb_prefix_instruction[0x70] = [this]() { _test_bit( m_registers.b, u8( 6 ) ); return 8; };
    m_cb_prefix_instruction[0x71] = [this]() { _test_bit( m_registers.c, u8( 6 ) ); return 8; };
    m_cb_prefix_instruction[0x72] = [this]() { _test_bit( m_registers.d, u8( 6 ) ); return 8; };
    m_cb_prefix_instruction[0x73] = [this]() { _test_bit( m_registers.e, u8( 6 ) ); return 8; };
    m_cb_prefix_instruction[0x74] = [this]() { _test_bit( m_registers.h, u8( 6 ) ); return 8; };
    m_cb_prefix_instruction[0x75] = [this]() { _test_bit( m_registers.l, u8( 6 ) ); return 8; };
    m_cb_prefix_instruction[0x76] = [this]() { _test_bit( m_memory.read_8( m_registers.hl ), 6 ); return 12; };
    m_cb_prefix_instruction[0x77] = [this]() { _test_bit( m_registers.a, u8( 6 ) ); return 8; };
    m_cb_prefix_instruction[0x78] = [this]() { _test_bit( m_registers.b, u8( 7 ) ); return 8; };
    m_cb_prefix_instruction[0x79] = [this]() { _test_bit( m_registers.c, u8( 7 ) ); return 8; };
    m_cb_prefix_instruction[0x7A] = [this]() { _test_bit( m_registers.d, u8( 7 ) ); return 8; };
    m_cb_prefix_instruction[0x7B] = [this]() { _test_bit( m_registers.e, u8( 7 ) ); return 8; };
    m_cb_prefix_instruction[0x7C] = [this]() { _test_bit( m_registers.h, u8( 7 ) ); return 8; };
    m_cb_prefix_instruction[0x7D] = [this]() { _test_bit( m_registers.l, u8( 7 ) ); return 8; };
    m_cb_prefix_instruction[0x7E] = [this]() { _test_bit( m_memory.read_8( m_registers.hl ), 7 ); return 12; };
    m_cb_prefix_instruction[0x7F] = [this]() { _test_bit( m_registers.a, u8( 7 ) ); return 8; };
    m_cb_prefix_instruction[0x80] = [this]() { _set_bit( m_registers.b, u8( 0 ) ); return 8; };
    m_cb_prefix_instruction[0x81] = [this]() { _set_bit( m_registers.c, u8( 0 ) ); return 8; };
    m_cb_prefix_instruction[0x82] = [this]() { _set_bit( m_registers.d, u8( 0 ) ); return 8; };
    m_cb_prefix_instruction[0x83] = [this]() { _set_bit( m_registers.e, u8( 0 ) ); return 8; };
    m_cb_prefix_instruction[0x84] = [this]() { _set_bit( m_registers.h, u8( 0 ) ); return 8; };
    m_cb_prefix_instruction[0x85] = [this]() { _set_bit( m_registers.l, u8( 0 ) ); return 8; };
    m_cb_prefix_instruction[0x86] = bind( &CPU::_set_bit_hl, this, u8( 0 ) );
    m_cb_prefix_instruction[0x87] = [this]() { _set_bit( m_registers.a, u8( 0 ) ); return 8; };
    m_cb_prefix_instruction[0x88] = [this]() { _set_bit( m_registers.b, u8( 1 ) ); return 8; };
    m_cb_prefix_instruction[0x89] = [this]() { _set_bit( m_registers.c, u8( 1 ) ); return 8; };
    m_cb_prefix_instruction[0x8A] = [this]() { _set_bit( m_registers.d, u8( 1 ) ); return 8; };
    m_cb_prefix_instruction[0x8B] = [this]() { _set_bit( m_registers.e, u8( 1 ) ); return 8; };
    m_cb_prefix_instruction[0x8C] = [this]() { _set_bit( m_registers.h, u8( 1 ) ); return 8; };
    m_cb_prefix_instruction[0x8D] = [this]() { _set_bit( m_registers.l, u8( 1 ) ); return 8; };
    m_cb_prefix_instruction[0x8E] = bind( &CPU::_set_bit_hl, this, u8( 1 ) );
    m_cb_prefix_instruction[0x8F] = [this]() { _set_bit( m_registers.a, u8( 1 ) ); return 8; };
    m_cb_prefix_instruction[0x90] = [this]() { _set_bit( m_registers.b, u8( 2 ) ); return 8; };
    m_cb_prefix_instruction[0x91] = [this]() { _set_bit( m_registers.c, u8( 2 ) ); return 8; };
    m_cb_prefix_instruction[0x92] = [this]() { _set_bit( m_registers.d, u8( 2 ) ); return 8; };
    m_cb_prefix_instruction[0x93] = [this]() { _set_bit( m_registers.e, u8( 2 ) ); return 8; };
    m_cb_prefix_instruction[0x94] = [this]() { _set_bit( m_registers.h, u8( 2 ) ); return 8; };
    m_cb_prefix_instruction[0x95] = [this]() { _set_bit( m_registers.l, u8( 2 ) ); return 8; };
    m_cb_prefix_instruction[0x96] = bind( &CPU::_set_bit_hl, this, u8( 2 ) );
    m_cb_prefix_instruction[0x97] = [this]() { _set_bit( m_registers.a, u8( 2 ) ); return 8; };
    m_cb_prefix_instruction[0x98] = [this]() { _set_bit( m_registers.b, u8( 3 ) ); return 8; };
    m_cb_prefix_instruction[0x99] = [this]() { _set_bit( m_registers.c, u8( 3 ) ); return 8; };
    m_cb_prefix_instruction[0x9A] = [this]() { _set_bit( m_registers.d, u8( 3 ) ); return 8; };
    m_cb_prefix_instruction[0x9B] = [this]() { _set_bit( m_registers.e, u8( 3 ) ); return 8; };
    m_cb_prefix_instruction[0x9C] = [this]() { _set_bit( m_registers.h, u8( 3 ) ); return 8; };
    m_cb_prefix_instruction[0x9D] = [this]() { _set_bit( m_registers.l, u8( 3 ) ); return 8; };
    m_cb_prefix_instruction[0x9E] = bind( &CPU::_set_bit_hl, this, u8( 3 ) );
    m_cb_prefix_instruction[0x9F] = [this]() { _set_bit( m_registers.a, u8( 3 ) ); return 8; };
    m_cb_prefix_instruction[0xA0] = [this]() { _set_bit( m_registers.b, u8( 4 ) ); return 8; };
    m_cb_prefix_instruction[0xA1] = [this]() { _set_bit( m_registers.c, u8( 4 ) ); return 8; };
    m_cb_prefix_instruction[0xA2] = [this]() { _set_bit( m_registers.d, u8( 4 ) ); return 8; };
    m_cb_prefix_instruction[0xA3] = [this]() { _set_bit( m_registers.e, u8( 4 ) ); return 8; };
    m_cb_prefix_instruction[0xA4] = [this]() { _set_bit( m_registers.h, u8( 4 ) ); return 8; };
    m_cb_prefix_instruction[0xA5] = [this]() { _set_bit( m_registers.l, u8( 4 ) ); return 8; };
    m_cb_prefix_instruction[0xA6] = bind( &CPU::_set_bit_hl, this, u8( 4 ) );
    m_cb_prefix_instruction[0xA7] = [this]() { _set_bit( m_registers.a, u8( 4 ) ); return 8; };
    m_cb_prefix_instruction[0xA8] = [this]() { _set_bit( m_registers.b, u8( 5 ) ); return 8; };
    m_cb_prefix_instruction[0xA9] = [this]() { _set_bit( m_registers.c, u8( 5 ) ); return 8; };
    m_cb_prefix_instruction[0xAA] = [this]() { _set_bit( m_registers.d, u8( 5 ) ); return 8; };
    m_cb_prefix_instruction[0xAB] = [this]() { _set_bit( m_registers.e, u8( 5 ) ); return 8; };
    m_cb_prefix_instruction[0xAC] = [this]() { _set_bit( m_registers.h, u8( 5 ) ); return 8; };
    m_cb_prefix_instruction[0xAD] = [this]() { _set_bit( m_registers.l, u8( 5 ) ); return 8; };
    m_cb_prefix_instruction[0xAE] = bind( &CPU::_set_bit_hl, this, u8( 5 ) );
    m_cb_prefix_instruction[0xAF] = [this]() { _set_bit( m_registers.a, u8( 5 ) ); return 8; };
    m_cb_prefix_instruction[0xB0] = [this]() { _set_bit( m_registers.b, u8( 6 ) ); return 8; };
    m_cb_prefix_instruction[0xB1] = [this]() { _set_bit( m_registers.c, u8( 6 ) ); return 8; };
    m_cb_prefix_instruction[0xB2] = [this]() { _set_bit( m_registers.d, u8( 6 ) ); return 8; };
    m_cb_prefix_instruction[0xB3] = [this]() { _set_bit( m_registers.e, u8( 6 ) ); return 8; };
    m_cb_prefix_instruction[0xB4] = [this]() { _set_bit( m_registers.h, u8( 6 ) ); return 8; };
    m_cb_prefix_instruction[0xB5] = [this]() { _set_bit( m_registers.l, u8( 6 ) ); return 8; };
    m_cb_prefix_instruction[0xB6] = bind( &CPU::_set_bit_hl, this, u8( 6 ) );
    m_cb_prefix_instruction[0xB7] = [this]() { _set_bit( m_registers.a, u8( 6 ) ); return 8; };
    m_cb_prefix_instruction[0xB8] = [this]() { _set_bit( m_registers.b, u8( 7 ) ); return 8; };
    m_cb_prefix_instruction[0xB9] = [this]() { _set_bit( m_registers.c, u8( 7 ) ); return 8; };
    m_cb_prefix_instruction[0xBA] = [this]() { _set_bit( m_registers.d, u8( 7 ) ); return 8; };
    m_cb_prefix_instruction[0xBB] = [this]() { _set_bit( m_registers.e, u8( 7 ) ); return 8; };
    m_cb_prefix_instruction[0xBC] = [this]() { _set_bit( m_registers.h, u8( 7 ) ); return 8; };
    m_cb_prefix_instruction[0xBD] = [this]() { _set_bit( m_registers.l, u8( 7 ) ); return 8; };
    m_cb_prefix_instruction[0xBE] = bind( &CPU::_set_bit_hl, this, u8( 7 ) );
    m_cb_prefix_instruction[0xBF] = [this]() { _set_bit( m_registers.a, u8( 7 ) ); return 8; };
    m_cb_prefix_instruction[0xC0] = [this]() { _reset_bit( m_registers.b, u8( 0 ) ); return 8; };
    m_cb_prefix_instruction[0xC1] = [this]() { _reset_bit( m_registers.c, u8( 0 ) ); return 8; };
    m_cb_prefix_instruction[0xC2] = [this]() { _reset_bit( m_registers.d, u8( 0 ) ); return 8; };
    m_cb_prefix_instruction[0xC3] = [this]() { _reset_bit( m_registers.e, u8( 0 ) ); return 8; };
    m_cb_prefix_instruction[0xC4] = [this]() { _reset_bit( m_registers.h, u8( 0 ) ); return 8; };
    m_cb_prefix_instruction[0xC5] = [this]() { _reset_bit( m_registers.l, u8( 0 ) ); return 8; };
    m_cb_prefix_instruction[0xC6] = bind( &CPU::_reset_bit_hl, this, u8( 0 ) );
    m_cb_prefix_instruction[0xC7] = [this]() { _reset_bit( m_registers.a, u8( 0 ) ); return 8; };
    m_cb_prefix_instruction[0xC8] = [this]() { _reset_bit( m_registers.b, u8( 1 ) ); return 8; };
    m_cb_prefix_instruction[0xC9] = [this]() { _reset_bit( m_registers.c, u8( 1 ) ); return 8; };
    m_cb_prefix_instruction[0xCA] = [this]() { _reset_bit( m_registers.d, u8( 1 ) ); return 8; };
    m_cb_prefix_instruction[0xCB] = [this]() { _reset_bit( m_registers.e, u8( 1 ) ); return 8; };
    m_cb_prefix_instruction[0xCC] = [this]() { _reset_bit( m_registers.h, u8( 1 ) ); return 8; };
    m_cb_prefix_instruction[0xCD] = [this]() { _reset_bit( m_registers.l, u8( 1 ) ); return 8; };
    m_cb_prefix_instruction[0xCE] = bind( &CPU::_reset_bit_hl, this, u8( 1 ) );
    m_cb_prefix_instruction[0xCF] = [this]() { _reset_bit( m_registers.a, u8( 1 ) ); return 8; };
    m_cb_prefix_instruction[0xD0] = [this]() { _reset_bit( m_registers.b, u8( 2 ) ); return 8; };
    m_cb_prefix_instruction[0xD1] = [this]() { _reset_bit( m_registers.c, u8( 2 ) ); return 8; };
    m_cb_prefix_instruction[0xD2] = [this]() { _reset_bit( m_registers.d, u8( 2 ) ); return 8; };
    m_cb_prefix_instruction[0xD3] = [this]() { _reset_bit( m_registers.e, u8( 2 ) ); return 8; };
    m_cb_prefix_instruction[0xD4] = [this]() { _reset_bit( m_registers.h, u8( 2 ) ); return 8; };
    m_cb_prefix_instruction[0xD5] = [this]() { _reset_bit( m_registers.l, u8( 2 ) ); return 8; };
    m_cb_prefix_instruction[0xD6] = bind( &CPU::_reset_bit_hl, this, u8( 2 ) );
    m_cb_prefix_instruction[0xD7] = [this]() { _reset_bit( m_registers.a, u8( 2 ) ); return 8; };
    m_cb_prefix_instruction[0xD8] = [this]() { _reset_bit( m_registers.b, u8( 3 ) ); return 8; };
    m_cb_prefix_instruction[0xD9] = [this]() { _reset_bit( m_registers.c, u8( 3 ) ); return 8; };
    m_cb_prefix_instruction[0xDA] = [this]() { _reset_bit( m_registers.d, u8( 3 ) ); return 8; };
    m_cb_prefix_instruction[0xDB] = [this]() { _reset_bit( m_registers.e, u8( 3 ) ); return 8; };
    m_cb_prefix_instruction[0xDC] = [this]() { _reset_bit( m_registers.h, u8( 3 ) ); return 8; };
    m_cb_prefix_instruction[0xDD] = [this]() { _reset_bit( m_registers.l, u8( 3 ) ); return 8; };
    m_cb_prefix_instruction[0xDE] = bind( &CPU::_reset_bit_hl, this, u8( 3 ) );
    m_cb_prefix_instruction[0xDF] = [this]() { _reset_bit( m_registers.a, u8( 3 ) ); return 8; };
    m_cb_prefix_instruction[0xE0] = [this]() { _reset_bit( m_registers.b, u8( 4 ) ); return 8; };
    m_cb_prefix_instruction[0xE1] = [this]() { _reset_bit( m_registers.c, u8( 4 ) ); return 8; };
    m_cb_prefix_instruction[0xE2] = [this]() { _reset_bit( m_registers.d, u8( 4 ) ); return 8; };
    m_cb_prefix_instruction[0xE3] = [this]() { _reset_bit( m_registers.e, u8( 4 ) ); return 8; };
    m_cb_prefix_instruction[0xE4] = [this]() { _reset_bit( m_registers.h, u8( 4 ) ); return 8; };
    m_cb_prefix_instruction[0xE5] = [this]() { _reset_bit( m_registers.l, u8( 4 ) ); return 8; };
    m_cb_prefix_instruction[0xE6] = bind( &CPU::_reset_bit_hl, this, u8( 4 ) );
    m_cb_prefix_instruction[0xE7] = [this]() { _reset_bit( m_registers.a, u8( 4 ) ); return 8; };
    m_cb_prefix_instruction[0xE8] = [this]() { _reset_bit( m_registers.b, u8( 5 ) ); return 8; };
    m_cb_prefix_instruction[0xE9] = [this]() { _reset_bit( m_registers.c, u8( 5 ) ); return 8; };
    m_cb_prefix_instruction[0xEA] = [this]() { _reset_bit( m_registers.d, u8( 5 ) ); return 8; };
    m_cb_prefix_instruction[0xEB] = [this]() { _reset_bit( m_registers.e, u8( 5 ) ); return 8; };
    m_cb_prefix_instruction[0xEC] = [this]() { _reset_bit( m_registers.h, u8( 5 ) ); return 8; };
    m_cb_prefix_instruction[0xED] = [this]() { _reset_bit( m_registers.l, u8( 5 ) ); return 8; };
    m_cb_prefix_instruction[0xEE] = bind( &CPU::_reset_bit_hl, this, u8( 5 ) );
    m_cb_prefix_instruction[0xEF] = [this]() { _reset_bit( m_registers.a, u8( 5 ) ); return 8; };
    m_cb_prefix_instruction[0xF0] = [this]() { _reset_bit( m_registers.b, u8( 6 ) ); return 8; };
    m_cb_prefix_instruction[0xF1] = [this]() { _reset_bit( m_registers.c, u8( 6 ) ); return 8; };
    m_cb_prefix_instruction[0xF2] = [this]() { _reset_bit( m_registers.d, u8( 6 ) ); return 8; };
    m_cb_prefix_instruction[0xF3] = [this]() { _reset_bit( m_registers.e, u8( 6 ) ); return 8; };
    m_cb_prefix_instruction[0xF4] = [this]() { _reset_bit( m_registers.h, u8( 6 ) ); return 8; };
    m_cb_prefix_instruction[0xF5] = [this]() { _reset_bit( m_registers.l, u8( 6 ) ); return 8; };
    m_cb_prefix_instruction[0xF6] = bind( &CPU::_reset_bit_hl, this, u8( 6 ) );
    m_cb_prefix_instruction[0xF7] = [this]() { _reset_bit( m_registers.a, u8( 6 ) ); return 8; };
    m_cb_prefix_instruction[0xF8] = [this]() { _reset_bit( m_registers.b, u8( 7 ) ); return 8; };
    m_cb_prefix_instruction[0xF9] = [this]() { _reset_bit( m_registers.c, u8( 7 ) ); return 8; };
    m_cb_prefix_instruction[0xFA] = [this]() { _reset_bit( m_registers.d, u8( 7 ) ); return 8; };
    m_cb_prefix_instruction[0xFB] = [this]() { _reset_bit( m_registers.e, u8( 7 ) ); return 8; };
    m_cb_prefix_instruction[0xFC] = [this]() { _reset_bit( m_registers.h, u8( 7 ) ); return 8; };
    m_cb_prefix_instruction[0xFD] = [this]() { _reset_bit( m_registers.l, u8( 7 ) ); return 8; };
    m_cb_prefix_instruction[0xFE] = bind( &CPU::_reset_bit_hl, this, u8( 7 ) );
    m_cb_prefix_instruction[0xFF] = [this]() { _reset_bit( m_registers.a, u8( 7 ) ); return 8; };
}

u32 CPU::_reroute_to_cb_table()
{
    u8 opcode = m_memory.read_8( m_registers.pc++ );
    return m_cb_prefix_instruction[opcode]();
}

// 8Bit Transfer
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
    m_registers.sp -= 2;
    m_memory.write( m_registers.sp, reg );
    
    return 16;
}

u32 CPU::_pop( u16& reg )
{
    reg = m_memory.read_16( m_registers.sp );
    m_registers.sp += 2;

    return 12;
}

u32 CPU::_ldhl()
{
    u8 const mem_value = m_memory.read_8( m_registers.pc++ );

    _process_carry_flag_16( m_registers.sp + mem_value );
    _process_half_carry_flag( m_registers.sp, mem_value );

    m_registers.hl = m_registers.sp + mem_value;

    _reset_flag( Flags::ADD_SUB );
    _reset_flag( Flags::ZERO );

    return 12;
}

u32 CPU::_ld_nn_sp()
{
    u8 const mem_address = m_memory.read_8( m_registers.pc++ );
    m_memory.write( mem_address, m_registers.sp );

    return 20;
}

// Aritmethic
void CPU::_add( u8 const rhs, bool const carry )
{
    u8 const carry_value = carry && _is_flag_set( Flags::CARRY ) ? 1 : 0;

    _process_carry_flag_8( m_registers.a + rhs + carry_value );
    _process_half_carry_flag( rhs, carry_value, true );

    m_registers.a += rhs + carry_value;

    _process_zero_flag();
    _reset_flag( Flags::ADD_SUB );
}

void CPU::_sub( u8 const rhs, bool const carry )
{
    u8 const carry_value = carry && _is_flag_set( Flags::CARRY ) ? 1 : 0;

    _process_carry_flag_8( m_registers.a - rhs - carry_value );
    _process_half_carry_flag( rhs, carry_value, false );

    m_registers.a = m_registers.a - rhs - carry_value;

    _process_zero_flag();
    _set_flag( Flags::ADD_SUB );
}

u32 CPU::_inc_r( u8& reg )
{
    _process_half_carry_flag( reg, 1, 0, false );

    ++reg;

    _process_zero_flag( reg );
    _reset_flag( Flags::ADD_SUB );
    // ignore carry flag

    return 4;
}

u32 CPU::_inc_hl()
{
    u8 const mem_value = m_memory.read_8( m_registers.hl );
    u8 const inc_mem_value = mem_value + 1;

    m_memory.write( m_registers.hl, inc_mem_value );

    _process_zero_flag( inc_mem_value );
    _process_half_carry_flag( mem_value, 1, 0, false );
    _reset_flag( Flags::ADD_SUB );
    // ignore carry flag

    return 12;
}

u32 CPU::_dec_r( u8& reg )
{
    _process_half_carry_flag( reg, 1, 0, true );

    --reg;

    _process_zero_flag( reg );
    _set_flag( Flags::ADD_SUB );
    // ignore carry flag

    return 4;
}

u32 CPU::_dec_hl()
{
    u8 const mem_value = m_memory.read_8( m_registers.hl );
    u8 const dec_mem_value = mem_value - 1;

    m_memory.write( m_registers.hl, dec_mem_value );

    _process_zero_flag( dec_mem_value );
    _process_half_carry_flag( mem_value, 1, 0, true );
    _set_flag( Flags::ADD_SUB );
    // ignore carry flag

    return 12;
}

u32 CPU::_decimal_adjust_acc()
{
    if( _is_flag_set( Flags::ADD_SUB ) )
    {
        if( _is_flag_set( Flags::HALF_CARRY ) )
            m_registers.a += 0xFA;
        if( _is_flag_set( Flags::CARRY ) )
            m_registers.a += 0xA0;
    }
    else
    {
        // This impl looks like a simplified version of the table in the gb manual... 
        // I think there's some gaps that this is mistakenly modifying the A reg
        // (FI: With H: 0x94 - 0x9F && 0xF4 - 0xFF we are adding 6 when we shouldn't)
        // Maybe I'm missing something... ??

        u16 aux = m_registers.a;
        if( _is_flag_set( Flags::HALF_CARRY ) || ( aux & 0x0F ) > 0x09 )
            aux += 0x06;
        if( _is_flag_set( Flags::CARRY ) || ( aux > 0x9F ) )
            aux += 0x60;

        if( ( aux & 0x100 ) == 0x100 )
            _set_flag( Flags::CARRY );

        m_registers.a = static_cast<u8>( aux );
    }

    _process_zero_flag();
    _reset_flag( Flags::HALF_CARRY );

    return 4;
}

u32 CPU::_complement()
{
    m_registers.a ^= 0xFF;

    _set_flag( Flags::ADD_SUB );
    _set_flag( Flags::HALF_CARRY );

    return 4;
}

// Logical
void CPU::_and( u8 const rhs )
{  
    m_registers.a &= rhs;

    _process_zero_flag();
    _set_flag( Flags::HALF_CARRY );
    _reset_flag( Flags::ADD_SUB );
    _reset_flag( Flags::CARRY );
}

void CPU::_xor( u8 const rhs )
{
    m_registers.a ^= rhs;

    _process_zero_flag();
    _reset_flag( Flags::HALF_CARRY );
    _reset_flag( Flags::ADD_SUB );
    _reset_flag( Flags::CARRY );
}

void CPU::_or( u8 const rhs )
{
    m_registers.a |= rhs;

    _process_zero_flag();
    _reset_flag( Flags::HALF_CARRY );
    _reset_flag( Flags::ADD_SUB );
    _reset_flag( Flags::CARRY );
}

void CPU::_cmp( u8 const rhs )
{
    u8 const aux = m_registers.a - rhs;

    _process_zero_flag( aux );
    _process_half_carry_flag( rhs, 0, false );
    _process_carry_flag_8( aux );
    _set_flag( Flags::ADD_SUB );
}

// 16Bit Aritmethic
u32 CPU::_add_hl( u16 const reg )
{
    _process_half_carry_flag( m_registers.hl, reg );
    _process_carry_flag_16( m_registers.sp + reg );

    m_registers.hl += reg;

    _reset_flag( Flags::ADD_SUB );
    // ignore zero

    return 8;
}

u32 CPU::_add_sp()
{
    u8 value = m_memory.read_8( m_registers.pc++ );

    // Apparently this needs to be bit 3 not bit 11 for reg SP.
    _process_half_carry_flag( static_cast<u8>( m_registers.sp ), value );
    _process_carry_flag_16( m_registers.sp + value );

    m_registers.sp += value;

    _reset_flag( Flags::ADD_SUB );
    _reset_flag( Flags::ZERO );

    return 16;
}

u32 CPU::_inc_dec( u16& reg, bool inc )
{
    inc ? ++reg : --reg;

    return 8;
}

// Rotate Shift
u32 CPU::_rla_rlca( bool through_carry )
{
    u8 carry = ( m_registers.a & 0x80 ) >> 7;
    m_registers.a <<= 1;
    m_registers.a |= through_carry ? carry : _get_flag( Flags::CARRY );

    carry != 0 ? _set_flag( Flags::CARRY ) : _reset_flag( Flags::CARRY );
    _reset_flag( Flags::ADD_SUB );
    _reset_flag( Flags::HALF_CARRY );
    _reset_flag( Flags::ZERO );

    return 4;
}

void CPU::_rl_rlc( u8& reg, bool through_carry )
{
    u8 carry = ( reg & 0x80 ) >> 7;
    reg <<= 1;
    reg |= through_carry ? carry : _get_flag( Flags::CARRY );

    carry != 0 ? _set_flag( Flags::CARRY ) : _reset_flag( Flags::CARRY );
    _reset_flag( Flags::ADD_SUB );
    _reset_flag( Flags::HALF_CARRY );
    _process_zero_flag( reg );
}

u32 CPU::_rl_rlc_hl( bool through_carry )
{
    u8 mem_hl = m_memory.read_8( m_registers.hl );
    _rl_rlc( mem_hl, through_carry );
    m_memory.write( m_registers.hl, mem_hl );

    return 16;
}

u32 CPU::_rra_rrca( bool through_carry )
{
    u8 carry = (m_registers.a & 0x01) << 7;
    m_registers.a >>= 1;
    m_registers.a |= through_carry ? carry : _get_flag( Flags::CARRY ) << 7; // OR works cos is unsigned

    carry != 0 ? _set_flag( Flags::CARRY ) : _reset_flag( Flags::CARRY );
    _reset_flag( Flags::ADD_SUB );
    _reset_flag( Flags::HALF_CARRY );
    _reset_flag( Flags::ZERO );

    return 4;
}

void CPU::_rr_rrc( u8& reg, bool through_carry )
{
    u8 carry = ( m_registers.a & 0x01 ) << 7;
    reg >>= 1;
    reg |= through_carry ? carry : _get_flag( Flags::CARRY ) << 7;

    carry != 0 ? _set_flag( Flags::CARRY ) : _reset_flag( Flags::CARRY );
    _reset_flag( Flags::ADD_SUB );
    _reset_flag( Flags::HALF_CARRY );
    _process_zero_flag( reg );
}

u32 CPU::_rr_rrc_hl( bool through_carry )
{
    u8 mem_hl = m_memory.read_8( m_registers.hl );
    _rr_rrc( mem_hl, through_carry );
    m_memory.write( m_registers.hl, mem_hl );

    return 16;
}

void CPU::_shift_l( u8& reg )
{
    reg | 0x80 ? _set_flag( Flags::CARRY ) : _reset_flag( Flags::CARRY );
    reg <<= 1;

    _reset_flag( Flags::ADD_SUB );
    _reset_flag( Flags::HALF_CARRY );
    _process_zero_flag( reg );
}

void CPU::_shift_r( u8& reg, bool logical )
{
    reg | 0x01 ? _set_flag( Flags::CARRY ) : _reset_flag( Flags::CARRY );
    u8 bit7 = reg | 0x08;
    reg >>= 1;
    if( logical )
        reg |= bit7;

    _reset_flag( Flags::ADD_SUB );
    _reset_flag( Flags::HALF_CARRY );
    _process_zero_flag( reg );
}

u32 CPU::_shift_l_hl()
{
    u8 mem_hl = m_memory.read_8( m_registers.hl );
    _shift_l( mem_hl );
    m_memory.write( m_registers.hl, mem_hl );

    return 16;
}

u32 CPU::_shift_r_hl( bool logical )
{
    u8 mem_hl = m_memory.read_8( m_registers.hl );
    _shift_r( mem_hl, logical );
    m_memory.write( m_registers.hl, mem_hl );

    return 16;
}

void CPU::_swap( u8& reg )
{
    u8 hi = reg & 0xF0;
    reg = ( reg << 4 ) | ( hi >> 4 );

    _reset_flag( Flags::ADD_SUB );
    _reset_flag( Flags::CARRY );
    _reset_flag( Flags::HALF_CARRY );
    _process_zero_flag( reg );
}

u32 CPU::_swap_hl()
{
    u8 mem_hl = m_memory.read_8( m_registers.hl );
    _swap( mem_hl );
    m_memory.write( m_registers.hl, mem_hl );

    return 16;
}

// Bit Operations
void CPU::_test_bit( u8 const reg, u8 const bit )
{
    if( ( reg & ( 1 << bit ) ) != 0 )
        _set_flag( Flags::ZERO );
    else
        _reset_flag( Flags::ZERO );

    _set_flag( Flags::HALF_CARRY );
    _reset_flag( Flags::ADD_SUB );
}

void CPU::_set_bit( u8& reg, u8 const bit )
{
    reg |= ( 1 << bit );
}

u32 CPU::_set_bit_hl( u8 const bit )
{
    u8 mem_hl = m_memory.read_8( m_registers.hl );
    _set_bit( mem_hl, bit );
    m_memory.write( m_registers.hl, mem_hl );

    return 16;
}

void CPU::_reset_bit( u8& reg, u8 const bit )
{
    reg &= ~( 1 << bit );
}

u32 CPU::_reset_bit_hl( u8 const bit )
{
    u8 mem_hl = m_memory.read_8( m_registers.hl );
    _reset_bit( mem_hl, bit );
    m_memory.write( m_registers.hl, mem_hl );

    return 16;
}

// Jumps
bool CPU::_condition_passed( JumpCondition const condition ) const
{
    switch( condition )
    {
    case JumpCondition::CARRY:          return _is_flag_set( Flags::CARRY );    break;
    case JumpCondition::NO_CARRY:       return !_is_flag_set( Flags::CARRY );   break;
    case JumpCondition::ZERO:           return _is_flag_set( Flags::ZERO );     break;
    case JumpCondition::NO_ZERO:        return !_is_flag_set( Flags::ZERO );    break;
    case JumpCondition::NO_CONDITION:   return true;                            break;
    default:
        assert( false );
        break;
    }

    return false;
}

u32 CPU::_jump( JumpCondition const condition )
{
    if( _condition_passed( condition ) )
    {
        m_registers.pc = m_memory.read_16( m_registers.pc );

        return 16;
    }

    m_registers.pc += 2;

    return 12;
}

u32 CPU::_jump_relative( JumpCondition const condition )
{
    if( _condition_passed( condition ) )
    {
        //m_registers.pc = m_registers.pc + static_cast<s8>( m_memory.read_8( m_registers.pc ) );
        m_registers.pc = m_memory.read_8( m_registers.pc );
        ++m_registers.pc; // For some reason this needs to be done here too...

        return 12;
    }

    ++m_registers.pc;

    return 8;
}

u32 CPU::_jump_hl()
{
    m_registers.pc = m_registers.hl;

    return 4;
}

// Call and Returns
u32 CPU::_call( JumpCondition const condition )
{
    if( _condition_passed( condition ) )
    {
        _push( m_registers.pc );
        _jump();

        return 24;
    }

    m_registers.pc += 2;

    return 12;
}

u32 CPU::_ret( JumpCondition const condition )
{
    if( _condition_passed( condition ) )
    {
        _pop( m_registers.pc );

        return ( condition == JumpCondition::NO_CONDITION ) ? 16 : 20;
    }

    m_registers.pc += 2;

    return 8;
}

u32 CPU::_reti()
{
    _pop( m_registers.pc );
    m_ime = true;

    return 16;
}
u32 CPU::_call_routine( u8 const routine_address )
{
    assert( routine_address == 0x00 || routine_address == 0x08 ||
            routine_address == 0x10 || routine_address == 0x18 ||
            routine_address == 0x20 || routine_address == 0x28 ||
            routine_address == 0x30 || routine_address == 0x38 );

    _push( m_registers.pc );
    m_registers.pc = routine_address;

    return 16;
}

// CPU Control
u32 CPU::_ccf()
{
    if( _is_flag_set( Flags::CARRY ) )
        _reset_flag( Flags::CARRY );
    else
        _set_flag( Flags::CARRY );

    _reset_flag( Flags::ADD_SUB );
    _reset_flag( Flags::HALF_CARRY );

    return 4;
}

u32 CPU::_scf()
{
    _set_flag( Flags::CARRY );
    _reset_flag( Flags::ADD_SUB );
    _reset_flag( Flags::HALF_CARRY );

    return 4;
}
