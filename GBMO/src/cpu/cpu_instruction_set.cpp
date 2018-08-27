
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
Ex 	LDH (n),A 	POP HL 	    LDH (C),A 	XX 	        XX 	        PUSH HL 	AND n 	    RST 20 	    ADD SP,d 	JP (HL) 	LD (nn),A 	XX 	    XX 	        XX 	    XOR n 	    RST 28
Fx 	LDH A,(n) 	POP AF 	    XX 	        DI 	        XX 	        PUSH AF 	OR n 	    RST 30 	    LDHL SP,d 	LD SP,HL 	LD A,(nn) 	EI 	    XX 	        XX 	    CP n 	    RST 38

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
    m_base_instruction[0x01] = nullptr;
    m_base_instruction[0x02] = [this]() { m_memory.write( m_registers.bc, m_registers.a ); return 8; };
    m_base_instruction[0x03] = bind( &CPU::_inc_dec, this, ref( m_registers.bc ), true );
    m_base_instruction[0x04] = nullptr;
    m_base_instruction[0x05] = nullptr;
    m_base_instruction[0x06] = nullptr;
    m_base_instruction[0x07] = bind( &CPU::_rla_rlca, this, true );
    m_base_instruction[0x08] = bind( &CPU::_ld_nn_sp, this );
    m_base_instruction[0x09] = bind( &CPU::_add_hl, this, cref( m_registers.bc ) );
    m_base_instruction[0x0A] = nullptr;
    m_base_instruction[0x0B] = bind( &CPU::_inc_dec, this, ref( m_registers.bc ), false );
    m_base_instruction[0x0C] = nullptr;
    m_base_instruction[0x0D] = nullptr;
    m_base_instruction[0x0E] = nullptr;
    m_base_instruction[0x0F] = nullptr;
    m_base_instruction[0x10] = nullptr;
    m_base_instruction[0x11] = nullptr;
    m_base_instruction[0x12] = nullptr;
    m_base_instruction[0x13] = bind( &CPU::_inc_dec, this, ref( m_registers.de ), true );
    m_base_instruction[0x14] = nullptr;
    m_base_instruction[0x15] = nullptr;
    m_base_instruction[0x16] = nullptr;
    m_base_instruction[0x17] = bind( &CPU::_rla_rlca, this, false );
    m_base_instruction[0x18] = nullptr;
    m_base_instruction[0x19] = bind( &CPU::_add_hl, this, cref( m_registers.de ) );
    m_base_instruction[0x1A] = nullptr;
    m_base_instruction[0x1B] = bind( &CPU::_inc_dec, this, ref( m_registers.de ), false );
    m_base_instruction[0x1C] = nullptr;
    m_base_instruction[0x1D] = nullptr;
    m_base_instruction[0x1E] = nullptr;
    m_base_instruction[0x1F] = nullptr;
    m_base_instruction[0x20] = nullptr;
    m_base_instruction[0x21] = nullptr;
    m_base_instruction[0x22] = nullptr;
    m_base_instruction[0x23] = bind( &CPU::_inc_dec, this, ref( m_registers.hl ), true );
    m_base_instruction[0x24] = nullptr;
    m_base_instruction[0x25] = nullptr;
    m_base_instruction[0x26] = nullptr;
    m_base_instruction[0x27] = bind( &CPU::_decimal_adjust_acc, this );
    m_base_instruction[0x28] = nullptr;
    m_base_instruction[0x29] = bind( &CPU::_add_hl, this, cref( m_registers.hl ) );
    m_base_instruction[0x2A] = nullptr;
    m_base_instruction[0x2B] = bind( &CPU::_inc_dec, this, ref( m_registers.hl ), false );
    m_base_instruction[0x2C] = nullptr;
    m_base_instruction[0x2D] = nullptr;
    m_base_instruction[0x2E] = nullptr;
    m_base_instruction[0x2F] = nullptr;
    m_base_instruction[0x30] = nullptr;
    m_base_instruction[0x31] = nullptr;
    m_base_instruction[0x32] = nullptr;
    m_base_instruction[0x33] = bind( &CPU::_inc_dec, this, ref( m_registers.sp ), true );
    m_base_instruction[0x34] = nullptr;
    m_base_instruction[0x35] = nullptr;
    m_base_instruction[0x36] = nullptr;
    m_base_instruction[0x37] = nullptr;
    m_base_instruction[0x38] = nullptr;
    m_base_instruction[0x39] = bind( &CPU::_add_hl, this, cref( m_registers.sp ) );
    m_base_instruction[0x3A] = nullptr;
    m_base_instruction[0x3B] = bind( &CPU::_inc_dec, this, ref( m_registers.sp ), false );
    m_base_instruction[0x3C] = nullptr;
    m_base_instruction[0x3D] = nullptr;
    m_base_instruction[0x3E] = nullptr;
    m_base_instruction[0x3F] = nullptr;
    m_base_instruction[0x40] = nullptr;
    m_base_instruction[0x41] = nullptr;
    m_base_instruction[0x42] = nullptr;
    m_base_instruction[0x43] = nullptr;
    m_base_instruction[0x44] = nullptr;
    m_base_instruction[0x45] = nullptr;
    m_base_instruction[0x46] = nullptr;
    m_base_instruction[0x47] = bind( &CPU::_ld_r_r, this, ref( m_registers.b ), cref( m_registers.a ) );
    m_base_instruction[0x48] = nullptr;
    m_base_instruction[0x49] = nullptr;
    m_base_instruction[0x4A] = nullptr;
    m_base_instruction[0x4B] = nullptr;
    m_base_instruction[0x4C] = nullptr;
    m_base_instruction[0x4D] = nullptr;
    m_base_instruction[0x4E] = nullptr;
    m_base_instruction[0x4F] = nullptr;
    m_base_instruction[0x50] = nullptr;
    m_base_instruction[0x51] = nullptr;
    m_base_instruction[0x52] = nullptr;
    m_base_instruction[0x53] = nullptr;
    m_base_instruction[0x54] = nullptr;
    m_base_instruction[0x55] = nullptr;
    m_base_instruction[0x56] = nullptr;
    m_base_instruction[0x57] = nullptr;
    m_base_instruction[0x58] = nullptr;
    m_base_instruction[0x59] = nullptr;
    m_base_instruction[0x5A] = nullptr;
    m_base_instruction[0x5B] = nullptr;
    m_base_instruction[0x5C] = nullptr;
    m_base_instruction[0x5D] = nullptr;
    m_base_instruction[0x5E] = nullptr;
    m_base_instruction[0x5F] = nullptr;
    m_base_instruction[0x60] = nullptr;
    m_base_instruction[0x61] = nullptr;
    m_base_instruction[0x62] = nullptr;
    m_base_instruction[0x63] = nullptr;
    m_base_instruction[0x64] = nullptr;
    m_base_instruction[0x65] = nullptr;
    m_base_instruction[0x66] = nullptr;
    m_base_instruction[0x67] = nullptr;
    m_base_instruction[0x68] = nullptr;
    m_base_instruction[0x69] = nullptr;
    m_base_instruction[0x6A] = nullptr;
    m_base_instruction[0x6B] = nullptr;
    m_base_instruction[0x6C] = nullptr;
    m_base_instruction[0x6D] = nullptr;
    m_base_instruction[0x6E] = nullptr;
    m_base_instruction[0x6F] = nullptr;
    m_base_instruction[0x70] = nullptr;
    m_base_instruction[0x71] = nullptr;
    m_base_instruction[0x72] = nullptr;
    m_base_instruction[0x73] = nullptr;
    m_base_instruction[0x74] = nullptr;
    m_base_instruction[0x75] = nullptr;
    m_base_instruction[0x76] = nullptr;
    m_base_instruction[0x77] = nullptr;
    m_base_instruction[0x78] = nullptr;
    m_base_instruction[0x79] = nullptr;
    m_base_instruction[0x7A] = nullptr;
    m_base_instruction[0x7B] = nullptr;
    m_base_instruction[0x7C] = nullptr;
    m_base_instruction[0x7D] = nullptr;
    m_base_instruction[0x7E] = nullptr;
    m_base_instruction[0x7F] = nullptr;
    m_base_instruction[0x80] = [this]() { _add( m_registers.b, false ); return 4; };
    m_base_instruction[0x81] = nullptr;
    m_base_instruction[0x82] = nullptr;
    m_base_instruction[0x83] = nullptr;
    m_base_instruction[0x84] = nullptr;
    m_base_instruction[0x85] = nullptr;
    m_base_instruction[0x86] = [this]() { _add( m_memory.read_8( m_registers.hl ), false ); return 8; };
    m_base_instruction[0x87] = nullptr;
    m_base_instruction[0x88] = [this]() { _add( m_registers.b, true ); return 4; };
    m_base_instruction[0x89] = nullptr;
    m_base_instruction[0x8A] = nullptr;
    m_base_instruction[0x8B] = nullptr;
    m_base_instruction[0x8C] = nullptr;
    m_base_instruction[0x8D] = nullptr;
    m_base_instruction[0x8E] = nullptr;
    m_base_instruction[0x8F] = nullptr;
    m_base_instruction[0x90] = [this]() { _sub( m_registers.b, false ); return 4; };
    m_base_instruction[0x91] = nullptr;
    m_base_instruction[0x92] = nullptr;
    m_base_instruction[0x93] = nullptr;
    m_base_instruction[0x94] = nullptr;
    m_base_instruction[0x95] = nullptr;
    m_base_instruction[0x96] = nullptr;
    m_base_instruction[0x97] = nullptr;
    m_base_instruction[0x98] = [this]() { _sub( m_registers.b, true ); return 4; };
    m_base_instruction[0x99] = nullptr;
    m_base_instruction[0x9A] = nullptr;
    m_base_instruction[0x9B] = nullptr;
    m_base_instruction[0x9C] = nullptr;
    m_base_instruction[0x9D] = nullptr;
    m_base_instruction[0x9E] = nullptr;
    m_base_instruction[0x9F] = nullptr;
    m_base_instruction[0xA0] = nullptr;
    m_base_instruction[0xA1] = nullptr;
    m_base_instruction[0xA2] = nullptr;
    m_base_instruction[0xA3] = nullptr;
    m_base_instruction[0xA4] = nullptr;
    m_base_instruction[0xA5] = nullptr;
    m_base_instruction[0xA6] = nullptr;
    m_base_instruction[0xA7] = nullptr;
    m_base_instruction[0xA8] = nullptr;
    m_base_instruction[0xA9] = nullptr;
    m_base_instruction[0xAA] = nullptr;
    m_base_instruction[0xAB] = nullptr;
    m_base_instruction[0xAC] = nullptr;
    m_base_instruction[0xAD] = nullptr;
    m_base_instruction[0xAE] = nullptr;
    m_base_instruction[0xAF] = nullptr;
    m_base_instruction[0xB0] = nullptr;
    m_base_instruction[0xB1] = nullptr;
    m_base_instruction[0xB2] = nullptr;
    m_base_instruction[0xB3] = nullptr;
    m_base_instruction[0xB4] = nullptr;
    m_base_instruction[0xB5] = nullptr;
    m_base_instruction[0xB6] = nullptr;
    m_base_instruction[0xB7] = nullptr;
    m_base_instruction[0xB8] = nullptr;
    m_base_instruction[0xB9] = nullptr;
    m_base_instruction[0xBA] = nullptr;
    m_base_instruction[0xBB] = nullptr;
    m_base_instruction[0xBC] = nullptr;
    m_base_instruction[0xBD] = nullptr;
    m_base_instruction[0xBE] = nullptr;
    m_base_instruction[0xBF] = nullptr;
    m_base_instruction[0xC0] = nullptr;
    m_base_instruction[0xC1] = bind( &CPU::_pop, this, ref( m_registers.bc ) );
    m_base_instruction[0xC2] = nullptr;
    m_base_instruction[0xC3] = nullptr;
    m_base_instruction[0xC4] = nullptr;
    m_base_instruction[0xC5] = bind( &CPU::_push, this, ref( m_registers.bc ) );
    m_base_instruction[0xC6] = [this]() { _add( m_memory.read_8( m_registers.pc++ ), false ); return 8; };
    m_base_instruction[0xC7] = nullptr;
    m_base_instruction[0xC8] = nullptr;
    m_base_instruction[0xC9] = nullptr;
    m_base_instruction[0xCA] = nullptr;
    m_base_instruction[0xCB] = nullptr;
    m_base_instruction[0xCC] = nullptr;
    m_base_instruction[0xCD] = nullptr;
    m_base_instruction[0xCE] = nullptr;
    m_base_instruction[0xCF] = nullptr;
    m_base_instruction[0xD0] = nullptr;
    m_base_instruction[0xD1] = bind( &CPU::_pop, this, ref( m_registers.de ) );
    m_base_instruction[0xD2] = nullptr;
    m_base_instruction[0xD3] = nullptr;
    m_base_instruction[0xD4] = nullptr;
    m_base_instruction[0xD5] = bind( &CPU::_push, this, ref( m_registers.bc ) );
    m_base_instruction[0xD6] = nullptr;
    m_base_instruction[0xD7] = nullptr;
    m_base_instruction[0xD8] = nullptr;
    m_base_instruction[0xD9] = nullptr;
    m_base_instruction[0xDA] = nullptr;
    m_base_instruction[0xDB] = nullptr;
    m_base_instruction[0xDC] = nullptr;
    m_base_instruction[0xDD] = nullptr;
    m_base_instruction[0xDE] = nullptr;
    m_base_instruction[0xDF] = nullptr;
    m_base_instruction[0xE0] = nullptr;
    m_base_instruction[0xE1] = bind( &CPU::_pop, this, ref( m_registers.hl ) );
    m_base_instruction[0xE2] = nullptr;
    m_base_instruction[0xE3] = nullptr;
    m_base_instruction[0xE4] = nullptr;
    m_base_instruction[0xE5] = bind( &CPU::_push, this, ref( m_registers.hl ) );
    m_base_instruction[0xE6] = nullptr;
    m_base_instruction[0xE7] = nullptr; 
    m_base_instruction[0xE8] = bind( &CPU::_add_sp, this );
    m_base_instruction[0xE9] = nullptr;
    m_base_instruction[0xEA] = nullptr;
    m_base_instruction[0xEB] = nullptr;
    m_base_instruction[0xEC] = nullptr;
    m_base_instruction[0xED] = nullptr;
    m_base_instruction[0xEE] = nullptr;
    m_base_instruction[0xEF] = nullptr;
    m_base_instruction[0xF0] = nullptr;
    m_base_instruction[0xF1] = bind( &CPU::_pop, this, ref( m_registers.af ) );
    m_base_instruction[0xF2] = nullptr;
    m_base_instruction[0xF3] = nullptr;
    m_base_instruction[0xF4] = nullptr;
    m_base_instruction[0xF5] = bind( &CPU::_push, this, ref( m_registers.af ) );
    m_base_instruction[0xF6] = nullptr;
    m_base_instruction[0xF7] = nullptr;
    m_base_instruction[0xF8] = bind( &CPU::_ldhl, this );
    m_base_instruction[0xF9] = nullptr;
    m_base_instruction[0xFA] = nullptr;
    m_base_instruction[0xFB] = nullptr;
    m_base_instruction[0xFC] = nullptr;
    m_base_instruction[0xFD] = nullptr;
    m_base_instruction[0xFE] = nullptr;
    m_base_instruction[0xFF] = nullptr;

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
    m_cb_prefix_instruction[0x30] = nullptr;
    m_cb_prefix_instruction[0x31] = nullptr;
    m_cb_prefix_instruction[0x32] = nullptr;
    m_cb_prefix_instruction[0x33] = nullptr;
    m_cb_prefix_instruction[0x34] = nullptr;
    m_cb_prefix_instruction[0x35] = nullptr;
    m_cb_prefix_instruction[0x36] = nullptr;
    m_cb_prefix_instruction[0x37] = nullptr;
    m_cb_prefix_instruction[0x38] = [this]() { _shift_r( m_registers.b, true ); return 8; };
    m_cb_prefix_instruction[0x39] = [this]() { _shift_r( m_registers.c, true ); return 8; };
    m_cb_prefix_instruction[0x3A] = [this]() { _shift_r( m_registers.d, true ); return 8; };
    m_cb_prefix_instruction[0x3B] = [this]() { _shift_r( m_registers.e, true ); return 8; };
    m_cb_prefix_instruction[0x3C] = [this]() { _shift_r( m_registers.h, true ); return 8; };
    m_cb_prefix_instruction[0x3D] = [this]() { _shift_r( m_registers.l, true ); return 8; };
    m_cb_prefix_instruction[0x3E] = bind( &CPU::_shift_r_hl, this, true );
    m_cb_prefix_instruction[0x3F] = [this]() { _shift_r( m_registers.a, true ); return 8; };
    m_cb_prefix_instruction[0x40] = nullptr;
    m_cb_prefix_instruction[0x41] = nullptr;
    m_cb_prefix_instruction[0x42] = nullptr;
    m_cb_prefix_instruction[0x43] = nullptr;
    m_cb_prefix_instruction[0x44] = nullptr;
    m_cb_prefix_instruction[0x45] = nullptr;
    m_cb_prefix_instruction[0x46] = nullptr;
    m_cb_prefix_instruction[0x47] = nullptr;
    m_cb_prefix_instruction[0x48] = nullptr;
    m_cb_prefix_instruction[0x49] = nullptr;
    m_cb_prefix_instruction[0x4A] = nullptr;
    m_cb_prefix_instruction[0x4B] = nullptr;
    m_cb_prefix_instruction[0x4C] = nullptr;
    m_cb_prefix_instruction[0x4D] = nullptr;
    m_cb_prefix_instruction[0x4E] = nullptr;
    m_cb_prefix_instruction[0x4F] = nullptr;
    m_cb_prefix_instruction[0x50] = nullptr;
    m_cb_prefix_instruction[0x51] = nullptr;
    m_cb_prefix_instruction[0x52] = nullptr;
    m_cb_prefix_instruction[0x53] = nullptr;
    m_cb_prefix_instruction[0x54] = nullptr;
    m_cb_prefix_instruction[0x55] = nullptr;
    m_cb_prefix_instruction[0x56] = nullptr;
    m_cb_prefix_instruction[0x57] = nullptr;
    m_cb_prefix_instruction[0x58] = nullptr;
    m_cb_prefix_instruction[0x59] = nullptr;
    m_cb_prefix_instruction[0x5A] = nullptr;
    m_cb_prefix_instruction[0x5B] = nullptr;
    m_cb_prefix_instruction[0x5C] = nullptr;
    m_cb_prefix_instruction[0x5D] = nullptr;
    m_cb_prefix_instruction[0x5E] = nullptr;
    m_cb_prefix_instruction[0x5F] = nullptr;
    m_cb_prefix_instruction[0x60] = nullptr;
    m_cb_prefix_instruction[0x61] = nullptr;
    m_cb_prefix_instruction[0x62] = nullptr;
    m_cb_prefix_instruction[0x63] = nullptr;
    m_cb_prefix_instruction[0x64] = nullptr;
    m_cb_prefix_instruction[0x65] = nullptr;
    m_cb_prefix_instruction[0x66] = nullptr;
    m_cb_prefix_instruction[0x67] = nullptr;
    m_cb_prefix_instruction[0x68] = nullptr;
    m_cb_prefix_instruction[0x69] = nullptr;
    m_cb_prefix_instruction[0x6A] = nullptr;
    m_cb_prefix_instruction[0x6B] = nullptr;
    m_cb_prefix_instruction[0x6C] = nullptr;
    m_cb_prefix_instruction[0x6D] = nullptr;
    m_cb_prefix_instruction[0x6E] = nullptr;
    m_cb_prefix_instruction[0x6F] = nullptr;
    m_cb_prefix_instruction[0x70] = nullptr;
    m_cb_prefix_instruction[0x71] = nullptr;
    m_cb_prefix_instruction[0x72] = nullptr;
    m_cb_prefix_instruction[0x73] = nullptr;
    m_cb_prefix_instruction[0x74] = nullptr;
    m_cb_prefix_instruction[0x75] = nullptr;
    m_cb_prefix_instruction[0x76] = nullptr;
    m_cb_prefix_instruction[0x77] = nullptr;
    m_cb_prefix_instruction[0x78] = nullptr;
    m_cb_prefix_instruction[0x79] = nullptr;
    m_cb_prefix_instruction[0x7A] = nullptr;
    m_cb_prefix_instruction[0x7B] = nullptr;
    m_cb_prefix_instruction[0x7C] = nullptr;
    m_cb_prefix_instruction[0x7D] = nullptr;
    m_cb_prefix_instruction[0x7E] = nullptr;
    m_cb_prefix_instruction[0x7F] = nullptr;
    m_cb_prefix_instruction[0x80] = nullptr;
    m_cb_prefix_instruction[0x81] = nullptr;
    m_cb_prefix_instruction[0x82] = nullptr;
    m_cb_prefix_instruction[0x83] = nullptr;
    m_cb_prefix_instruction[0x84] = nullptr;
    m_cb_prefix_instruction[0x85] = nullptr;
    m_cb_prefix_instruction[0x86] = nullptr;
    m_cb_prefix_instruction[0x87] = nullptr;
    m_cb_prefix_instruction[0x88] = nullptr;
    m_cb_prefix_instruction[0x89] = nullptr;
    m_cb_prefix_instruction[0x8A] = nullptr;
    m_cb_prefix_instruction[0x8B] = nullptr;
    m_cb_prefix_instruction[0x8C] = nullptr;
    m_cb_prefix_instruction[0x8D] = nullptr;
    m_cb_prefix_instruction[0x8E] = nullptr;
    m_cb_prefix_instruction[0x8F] = nullptr;
    m_cb_prefix_instruction[0x90] = nullptr;
    m_cb_prefix_instruction[0x91] = nullptr;
    m_cb_prefix_instruction[0x92] = nullptr;
    m_cb_prefix_instruction[0x93] = nullptr;
    m_cb_prefix_instruction[0x94] = nullptr;
    m_cb_prefix_instruction[0x95] = nullptr;
    m_cb_prefix_instruction[0x96] = nullptr;
    m_cb_prefix_instruction[0x97] = nullptr;
    m_cb_prefix_instruction[0x98] = nullptr;
    m_cb_prefix_instruction[0x99] = nullptr;
    m_cb_prefix_instruction[0x9A] = nullptr;
    m_cb_prefix_instruction[0x9B] = nullptr;
    m_cb_prefix_instruction[0x9C] = nullptr;
    m_cb_prefix_instruction[0x9D] = nullptr;
    m_cb_prefix_instruction[0x9E] = nullptr;
    m_cb_prefix_instruction[0x9F] = nullptr;
    m_cb_prefix_instruction[0xA0] = nullptr;
    m_cb_prefix_instruction[0xA1] = nullptr;
    m_cb_prefix_instruction[0xA2] = nullptr;
    m_cb_prefix_instruction[0xA3] = nullptr;
    m_cb_prefix_instruction[0xA4] = nullptr;
    m_cb_prefix_instruction[0xA5] = nullptr;
    m_cb_prefix_instruction[0xA6] = nullptr;
    m_cb_prefix_instruction[0xA7] = nullptr;
    m_cb_prefix_instruction[0xA8] = nullptr;
    m_cb_prefix_instruction[0xA9] = nullptr;
    m_cb_prefix_instruction[0xAA] = nullptr;
    m_cb_prefix_instruction[0xAB] = nullptr;
    m_cb_prefix_instruction[0xAC] = nullptr;
    m_cb_prefix_instruction[0xAD] = nullptr;
    m_cb_prefix_instruction[0xAE] = nullptr;
    m_cb_prefix_instruction[0xAF] = nullptr;
    m_cb_prefix_instruction[0xB0] = nullptr;
    m_cb_prefix_instruction[0xB1] = nullptr;
    m_cb_prefix_instruction[0xB2] = nullptr;
    m_cb_prefix_instruction[0xB3] = nullptr;
    m_cb_prefix_instruction[0xB4] = nullptr;
    m_cb_prefix_instruction[0xB5] = nullptr;
    m_cb_prefix_instruction[0xB6] = nullptr;
    m_cb_prefix_instruction[0xB7] = nullptr;
    m_cb_prefix_instruction[0xB8] = nullptr;
    m_cb_prefix_instruction[0xB9] = nullptr;
    m_cb_prefix_instruction[0xBA] = nullptr;
    m_cb_prefix_instruction[0xBB] = nullptr;
    m_cb_prefix_instruction[0xBC] = nullptr;
    m_cb_prefix_instruction[0xBD] = nullptr;
    m_cb_prefix_instruction[0xBE] = nullptr;
    m_cb_prefix_instruction[0xBF] = nullptr;
    m_cb_prefix_instruction[0xC0] = nullptr;
    m_cb_prefix_instruction[0xC1] = nullptr;
    m_cb_prefix_instruction[0xC2] = nullptr;
    m_cb_prefix_instruction[0xC3] = nullptr;
    m_cb_prefix_instruction[0xC4] = nullptr;
    m_cb_prefix_instruction[0xC5] = nullptr;
    m_cb_prefix_instruction[0xC6] = nullptr;
    m_cb_prefix_instruction[0xC7] = nullptr;
    m_cb_prefix_instruction[0xC8] = nullptr;
    m_cb_prefix_instruction[0xC9] = nullptr;
    m_cb_prefix_instruction[0xCA] = nullptr;
    m_cb_prefix_instruction[0xCB] = nullptr;
    m_cb_prefix_instruction[0xCC] = nullptr;
    m_cb_prefix_instruction[0xCD] = nullptr;
    m_cb_prefix_instruction[0xCE] = nullptr;
    m_cb_prefix_instruction[0xCF] = nullptr;
    m_cb_prefix_instruction[0xD0] = nullptr;
    m_cb_prefix_instruction[0xD1] = nullptr;
    m_cb_prefix_instruction[0xD2] = nullptr;
    m_cb_prefix_instruction[0xD3] = nullptr;
    m_cb_prefix_instruction[0xD4] = nullptr;
    m_cb_prefix_instruction[0xD5] = nullptr;
    m_cb_prefix_instruction[0xD6] = nullptr;
    m_cb_prefix_instruction[0xD7] = nullptr;
    m_cb_prefix_instruction[0xD8] = nullptr;
    m_cb_prefix_instruction[0xD9] = nullptr;
    m_cb_prefix_instruction[0xDA] = nullptr;
    m_cb_prefix_instruction[0xDB] = nullptr;
    m_cb_prefix_instruction[0xDC] = nullptr;
    m_cb_prefix_instruction[0xDD] = nullptr;
    m_cb_prefix_instruction[0xDE] = nullptr;
    m_cb_prefix_instruction[0xDF] = nullptr;
    m_cb_prefix_instruction[0xE0] = nullptr;
    m_cb_prefix_instruction[0xE1] = nullptr;
    m_cb_prefix_instruction[0xE2] = nullptr;
    m_cb_prefix_instruction[0xE3] = nullptr;
    m_cb_prefix_instruction[0xE4] = nullptr;
    m_cb_prefix_instruction[0xE5] = nullptr;
    m_cb_prefix_instruction[0xE6] = nullptr;
    m_cb_prefix_instruction[0xE7] = nullptr;
    m_cb_prefix_instruction[0xE8] = nullptr;
    m_cb_prefix_instruction[0xE9] = nullptr;
    m_cb_prefix_instruction[0xEA] = nullptr;
    m_cb_prefix_instruction[0xEB] = nullptr;
    m_cb_prefix_instruction[0xEC] = nullptr;
    m_cb_prefix_instruction[0xED] = nullptr;
    m_cb_prefix_instruction[0xEE] = nullptr;
    m_cb_prefix_instruction[0xEF] = nullptr;
    m_cb_prefix_instruction[0xF0] = nullptr;
    m_cb_prefix_instruction[0xF1] = nullptr;
    m_cb_prefix_instruction[0xF2] = nullptr;
    m_cb_prefix_instruction[0xF3] = nullptr;
    m_cb_prefix_instruction[0xF4] = nullptr;
    m_cb_prefix_instruction[0xF5] = nullptr;
    m_cb_prefix_instruction[0xF6] = nullptr;
    m_cb_prefix_instruction[0xF7] = nullptr;
    m_cb_prefix_instruction[0xF8] = nullptr;
    m_cb_prefix_instruction[0xF9] = nullptr;
    m_cb_prefix_instruction[0xFA] = nullptr;
    m_cb_prefix_instruction[0xFB] = nullptr;
    m_cb_prefix_instruction[0xFC] = nullptr;
    m_cb_prefix_instruction[0xFD] = nullptr;
    m_cb_prefix_instruction[0xFE] = nullptr;
    m_cb_prefix_instruction[0xFF] = nullptr;
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

//void CPU::_shift_r_logical( u8& reg )
//{
//    reg | 0x01 ? _set_flag( Flags::CARRY ) : _reset_flag( Flags::CARRY );
//    reg >>= 1;
//
//    _reset_flag( Flags::ADD_SUB );
//    _reset_flag( Flags::HALF_CARRY );
//    _process_zero_flag( reg );
//}

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

//u32 CPU::_shift_r_logical_hl()
//{
//    u8 mem_hl = m_memory.read_8( m_registers.hl );
//    _shift_r_logical( mem_hl );
//    m_memory.write( m_registers.hl, mem_hl );
//
//    return 16;
//}

////////////////////////

// Aritmethic

/*
void CPU::_add( u8 lhs, u16 rhs, bool carry ){ assert( false ); } // NOT IMPLEMENTED
void CPU::_add( u16 lhs, u16 rhs, bool carry ){ assert( false ); } // NOT IMPLEMENTED
void CPU::_add( u16 lhs, s8 rhs, bool carry ){ assert( false ); } // NOT IMPLEMENTED
void CPU::_sub( u8 lhs, u8 rhs, bool carry ){ assert( false ); } // NOT IMPLEMENTED
void CPU::_sub( u8 lhs, u16 rhs, bool carry ){ assert( false ); } // NOT IMPLEMENTED
void CPU::_inc_dec( u8 lhs, u8 inc ){ assert( false ); } // NOT IMPLEMENTED
void CPU::_inc_dec( u16 lhs, u8 inc ){ assert( false ); } // NOT IMPLEMENTED
void CPU::_decimal_adjust_acc(){ assert( false ); } // NOT IMPLEMENTED
void CPU::_complement(){ assert( false ); } // NOT IMPLEMENTED
// Rotate Shift
void CPU::_rl( u8 lhs, bool carry ){ assert( false ); } // NOT IMPLEMENTED
void CPU::_rr( u8 lhs, bool carry ){ assert( false ); } // NOT IMPLEMENTED
void CPU::_shift_l( u8 lhs ){ assert( false ); } // NOT IMPLEMENTED
void CPU::_shift_r( u8 lhs ){ assert( false ); } // NOT IMPLEMENTED
void CPU::_shift_r_logical( u8 lhs ){ assert( false ); } // NOT IMPLEMENTED
void CPU::_swap( u8 lhs ){ assert( false ); } // NOT IMPLEMENTED
// Bit
void CPU::_test_bit( u8 lhs ){ assert( false ); } // NOT IMPLEMENTED
void CPU::_set_bit( u8 lhs ){ assert( false ); } // NOT IMPLEMENTED
void CPU::_reset_bit( u8 lhs ){ assert( false ); } // NOT IMPLEMENTED
// Jumps
void CPU::_jump( u16 address ){ assert( false ); } // NOT IMPLEMENTED
void CPU::_jump( s8 relative_address ){ assert( false ); } // NOT IMPLEMENTED
bool CPU::_conditional_jump( u16 addres ){ return false; }
bool CPU::_conditional_jump( s8 relative_addres ){ return false; }
// Call and Return
void CPU::_call( u16 address ){ assert( false ); } // NOT IMPLEMENTED
bool CPU::_conditional_call( u16 address ) { return false; }
void CPU::_call_routine( u8 routine_address ){ assert( false ); } // NOT IMPLEMENTED
void CPU::_ret( bool enable_interruptions ){ assert( false ); } // NOT IMPLEMENTED
bool CPU::_conditional_ret(){ return false; }
// CPU Control
u32 CPU::_noop()
{
    ++m_registers.pc;
    return 4;
}

void CPU::_set_carry(){ assert( false ); } // NOT IMPLEMENTED
void CPU::_halt(){ assert( false ); } // NOT IMPLEMENTED
void CPU::_stop(){ assert( false ); } // NOT IMPLEMENTED
void CPU::_set_interrupts( bool enable ){ assert( false ); } // NOT IMPLEMENTED
*/
