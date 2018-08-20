
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
 /*    m_base_instruction[0x01] =
     m_base_instruction[0x02] =
     m_base_instruction[0x03] =
     m_base_instruction[0x04] =
     m_base_instruction[0x05] =
     m_base_instruction[0x06] =
     m_base_instruction[0x07] =
     m_base_instruction[0x08] =
     m_base_instruction[0x09] =
     m_base_instruction[0x0A] =
     m_base_instruction[0x0B] =
     m_base_instruction[0x0C] =
     m_base_instruction[0x0D] =
     m_base_instruction[0x0E] =
     m_base_instruction[0x0F] =
     m_base_instruction[0x10] =
     m_base_instruction[0x11] =
     m_base_instruction[0x12] =
     m_base_instruction[0x13] =
     m_base_instruction[0x14] =
     m_base_instruction[0x15] =
     m_base_instruction[0x16] =
     m_base_instruction[0x17] =
     m_base_instruction[0x18] =
     m_base_instruction[0x19] =
     m_base_instruction[0x1A] =
     m_base_instruction[0x1B] =
     m_base_instruction[0x1C] =
     m_base_instruction[0x1D] =
     m_base_instruction[0x1E] =
     m_base_instruction[0x1F] =
     m_base_instruction[0x20] =
     m_base_instruction[0x21] =
     m_base_instruction[0x22] =
     m_base_instruction[0x23] =
     m_base_instruction[0x24] =
     m_base_instruction[0x25] =
     m_base_instruction[0x26] = */
    m_base_instruction[0x27] = bind( &CPU::_decimal_adjust_acc, this );
/*     m_base_instruction[0x28] =
     m_base_instruction[0x29] =
     m_base_instruction[0x2A] =
     m_base_instruction[0x2B] =
     m_base_instruction[0x2C] =
     m_base_instruction[0x2D] =
     m_base_instruction[0x2E] =
     m_base_instruction[0x2F] =
     m_base_instruction[0x30] =
     m_base_instruction[0x31] =
     m_base_instruction[0x32] =
     m_base_instruction[0x33] =
     m_base_instruction[0x34] =
     m_base_instruction[0x35] =
     m_base_instruction[0x36] =
     m_base_instruction[0x37] =
     m_base_instruction[0x38] =
     m_base_instruction[0x39] =
     m_base_instruction[0x3A] =
     m_base_instruction[0x3B] =
     m_base_instruction[0x3C] =
     m_base_instruction[0x3D] =
     m_base_instruction[0x3E] =
     m_base_instruction[0x3F] =
     m_base_instruction[0x40] =
     m_base_instruction[0x41] =
     m_base_instruction[0x42] =
     m_base_instruction[0x43] =
     m_base_instruction[0x44] =
     m_base_instruction[0x45] =
     m_base_instruction[0x46] = */
     m_base_instruction[0x47] = bind( &CPU::_ld_r_r, this, ref( m_registers.b ), cref( m_registers.a ) );
/*     m_base_instruction[0x48] =
     m_base_instruction[0x49] =
     m_base_instruction[0x4A] =
     m_base_instruction[0x4B] =
     m_base_instruction[0x4C] =
     m_base_instruction[0x4D] =
     m_base_instruction[0x4E] =
     m_base_instruction[0x4F] =
     m_base_instruction[0x50] =
     m_base_instruction[0x51] =
     m_base_instruction[0x52] =
     m_base_instruction[0x53] =
     m_base_instruction[0x54] =
     m_base_instruction[0x55] =
     m_base_instruction[0x56] =
     m_base_instruction[0x57] =
     m_base_instruction[0x58] =
     m_base_instruction[0x59] =
     m_base_instruction[0x5A] =
     m_base_instruction[0x5B] =
     m_base_instruction[0x5C] =
     m_base_instruction[0x5D] =
     m_base_instruction[0x5E] =
     m_base_instruction[0x5F] =
     m_base_instruction[0x60] =
     m_base_instruction[0x61] =
     m_base_instruction[0x62] =
     m_base_instruction[0x63] =
     m_base_instruction[0x64] =
     m_base_instruction[0x65] =
     m_base_instruction[0x66] =
     m_base_instruction[0x67] =
     m_base_instruction[0x68] =
     m_base_instruction[0x69] =
     m_base_instruction[0x6A] =
     m_base_instruction[0x6B] =
     m_base_instruction[0x6C] =
     m_base_instruction[0x6D] =
     m_base_instruction[0x6E] =
     m_base_instruction[0x6F] =
     m_base_instruction[0x70] =
     m_base_instruction[0x71] =
     m_base_instruction[0x72] =
     m_base_instruction[0x73] =
     m_base_instruction[0x74] =
     m_base_instruction[0x75] =
     m_base_instruction[0x76] =
     m_base_instruction[0x77] =
     m_base_instruction[0x78] =
     m_base_instruction[0x79] =
     m_base_instruction[0x7A] =
     m_base_instruction[0x7B] =
     m_base_instruction[0x7C] =
     m_base_instruction[0x7D] =
     m_base_instruction[0x7E] =
     m_base_instruction[0x7F] =
     m_base_instruction[0x80] =
     m_base_instruction[0x81] =
     m_base_instruction[0x82] =
     m_base_instruction[0x83] =
     m_base_instruction[0x84] =
     m_base_instruction[0x85] =
     m_base_instruction[0x86] =
     m_base_instruction[0x87] =
     m_base_instruction[0x88] =
     m_base_instruction[0x89] =
     m_base_instruction[0x8A] =
     m_base_instruction[0x8B] =
     m_base_instruction[0x8C] =
     m_base_instruction[0x8D] =
     m_base_instruction[0x8E] =
     m_base_instruction[0x8F] =
     m_base_instruction[0x90] =
     m_base_instruction[0x91] =
     m_base_instruction[0x92] =
     m_base_instruction[0x93] =
     m_base_instruction[0x94] =
     m_base_instruction[0x95] =
     m_base_instruction[0x96] =
     m_base_instruction[0x97] =
     m_base_instruction[0x98] =
     m_base_instruction[0x99] =
     m_base_instruction[0x9A] =
     m_base_instruction[0x9B] =
     m_base_instruction[0x9C] =
     m_base_instruction[0x9D] =
     m_base_instruction[0x9E] =
     m_base_instruction[0x9F] =
     m_base_instruction[0xA0] =
     m_base_instruction[0xA1] =
     m_base_instruction[0xA2] =
     m_base_instruction[0xA3] =
     m_base_instruction[0xA4] =
     m_base_instruction[0xA5] =
     m_base_instruction[0xA6] =
     m_base_instruction[0xA7] =
     m_base_instruction[0xA8] =
     m_base_instruction[0xA9] =
     m_base_instruction[0xAA] =
     m_base_instruction[0xAB] =
     m_base_instruction[0xAC] =
     m_base_instruction[0xAD] =
     m_base_instruction[0xAE] =
     m_base_instruction[0xAF] =
     m_base_instruction[0xB0] =
     m_base_instruction[0xB1] =
     m_base_instruction[0xB2] =
     m_base_instruction[0xB3] =
     m_base_instruction[0xB4] =
     m_base_instruction[0xB5] =
     m_base_instruction[0xB6] =
     m_base_instruction[0xB7] =
     m_base_instruction[0xB8] =
     m_base_instruction[0xB9] =
     m_base_instruction[0xBA] =
     m_base_instruction[0xBB] =
     m_base_instruction[0xBC] =
     m_base_instruction[0xBD] =
     m_base_instruction[0xBE] =
     m_base_instruction[0xBF] =
     m_base_instruction[0xC0] =
     m_base_instruction[0xC1] =
     m_base_instruction[0xC2] =
     m_base_instruction[0xC3] =
     m_base_instruction[0xC4] =
     m_base_instruction[0xC5] =
     m_base_instruction[0xC6] =
     m_base_instruction[0xC7] =
     m_base_instruction[0xC8] =
     m_base_instruction[0xC9] =
     m_base_instruction[0xCA] =
     m_base_instruction[0xCB] =
     m_base_instruction[0xCC] =
     m_base_instruction[0xCD] =
     m_base_instruction[0xCE] =
     m_base_instruction[0xCF] =
     m_base_instruction[0xD0] =
     m_base_instruction[0xD1] =
     m_base_instruction[0xD2] =
     m_base_instruction[0xD3] =
     m_base_instruction[0xD4] =
     m_base_instruction[0xD5] =
     m_base_instruction[0xD6] =
     m_base_instruction[0xD7] =
     m_base_instruction[0xD8] =
     m_base_instruction[0xD9] =
     m_base_instruction[0xDA] =
     m_base_instruction[0xDB] =
     m_base_instruction[0xDC] =
     m_base_instruction[0xDD] =
     m_base_instruction[0xDE] =
     m_base_instruction[0xDF] =
     m_base_instruction[0xE0] =
     m_base_instruction[0xE1] =
     m_base_instruction[0xE2] =
     m_base_instruction[0xE3] =
     m_base_instruction[0xE4] =
     m_base_instruction[0xE5] =
     m_base_instruction[0xE6] =
     m_base_instruction[0xE7] =
     m_base_instruction[0xE8] =
     m_base_instruction[0xE9] =
     m_base_instruction[0xEA] =
     m_base_instruction[0xEB] =
     m_base_instruction[0xEC] =
     m_base_instruction[0xED] =
     m_base_instruction[0xEE] =
     m_base_instruction[0xEF] =
     m_base_instruction[0xF0] =
     m_base_instruction[0xF1] =
     m_base_instruction[0xF2] =
     m_base_instruction[0xF3] =
     m_base_instruction[0xF4] =
     m_base_instruction[0xF5] =
     m_base_instruction[0xF6] =
     m_base_instruction[0xF7] =
     m_base_instruction[0xF8] =
     m_base_instruction[0xF9] =
     m_base_instruction[0xFA] =
     m_base_instruction[0xFB] =
     m_base_instruction[0xFC] =
     m_base_instruction[0xFD] =
     m_base_instruction[0xFE] =
     m_base_instruction[0xFF] =

     m_cb_prefix_instruction[0x00] =
     m_cb_prefix_instruction[0x01] =
     m_cb_prefix_instruction[0x02] =
     m_cb_prefix_instruction[0x03] =
     m_cb_prefix_instruction[0x04] =
     m_cb_prefix_instruction[0x05] =
     m_cb_prefix_instruction[0x06] =
     m_cb_prefix_instruction[0x07] =
     m_cb_prefix_instruction[0x08] =
     m_cb_prefix_instruction[0x09] =
     m_cb_prefix_instruction[0x0A] =
     m_cb_prefix_instruction[0x0B] =
     m_cb_prefix_instruction[0x0C] =
     m_cb_prefix_instruction[0x0D] =
     m_cb_prefix_instruction[0x0E] =
     m_cb_prefix_instruction[0x0F] =
     m_cb_prefix_instruction[0x10] =
     m_cb_prefix_instruction[0x11] =
     m_cb_prefix_instruction[0x12] =
     m_cb_prefix_instruction[0x13] =
     m_cb_prefix_instruction[0x14] =
     m_cb_prefix_instruction[0x15] =
     m_cb_prefix_instruction[0x16] =
     m_cb_prefix_instruction[0x17] =
     m_cb_prefix_instruction[0x18] =
     m_cb_prefix_instruction[0x19] =
     m_cb_prefix_instruction[0x1A] =
     m_cb_prefix_instruction[0x1B] =
     m_cb_prefix_instruction[0x1C] =
     m_cb_prefix_instruction[0x1D] =
     m_cb_prefix_instruction[0x1E] =
     m_cb_prefix_instruction[0x1F] =
     m_cb_prefix_instruction[0x20] =
     m_cb_prefix_instruction[0x21] =
     m_cb_prefix_instruction[0x22] =
     m_cb_prefix_instruction[0x23] =
     m_cb_prefix_instruction[0x24] =
     m_cb_prefix_instruction[0x25] =
     m_cb_prefix_instruction[0x26] =
     m_cb_prefix_instruction[0x27] =
     m_cb_prefix_instruction[0x28] =
     m_cb_prefix_instruction[0x29] =
     m_cb_prefix_instruction[0x2A] =
     m_cb_prefix_instruction[0x2B] =
     m_cb_prefix_instruction[0x2C] =
     m_cb_prefix_instruction[0x2D] =
     m_cb_prefix_instruction[0x2E] =
     m_cb_prefix_instruction[0x2F] =
     m_cb_prefix_instruction[0x30] =
     m_cb_prefix_instruction[0x31] =
     m_cb_prefix_instruction[0x32] =
     m_cb_prefix_instruction[0x33] =
     m_cb_prefix_instruction[0x34] =
     m_cb_prefix_instruction[0x35] =
     m_cb_prefix_instruction[0x36] =
     m_cb_prefix_instruction[0x37] =
     m_cb_prefix_instruction[0x38] =
     m_cb_prefix_instruction[0x39] =
     m_cb_prefix_instruction[0x3A] =
     m_cb_prefix_instruction[0x3B] =
     m_cb_prefix_instruction[0x3C] =
     m_cb_prefix_instruction[0x3D] =
     m_cb_prefix_instruction[0x3E] =
     m_cb_prefix_instruction[0x3F] =
     m_cb_prefix_instruction[0x40] =
     m_cb_prefix_instruction[0x41] =
     m_cb_prefix_instruction[0x42] =
     m_cb_prefix_instruction[0x43] =
     m_cb_prefix_instruction[0x44] =
     m_cb_prefix_instruction[0x45] =
     m_cb_prefix_instruction[0x46] =
     m_cb_prefix_instruction[0x47] =
     m_cb_prefix_instruction[0x48] =
     m_cb_prefix_instruction[0x49] =
     m_cb_prefix_instruction[0x4A] =
     m_cb_prefix_instruction[0x4B] =
     m_cb_prefix_instruction[0x4C] =
     m_cb_prefix_instruction[0x4D] =
     m_cb_prefix_instruction[0x4E] =
     m_cb_prefix_instruction[0x4F] =
     m_cb_prefix_instruction[0x50] =
     m_cb_prefix_instruction[0x51] =
     m_cb_prefix_instruction[0x52] =
     m_cb_prefix_instruction[0x53] =
     m_cb_prefix_instruction[0x54] =
     m_cb_prefix_instruction[0x55] =
     m_cb_prefix_instruction[0x56] =
     m_cb_prefix_instruction[0x57] =
     m_cb_prefix_instruction[0x58] =
     m_cb_prefix_instruction[0x59] =
     m_cb_prefix_instruction[0x5A] =
     m_cb_prefix_instruction[0x5B] =
     m_cb_prefix_instruction[0x5C] =
     m_cb_prefix_instruction[0x5D] =
     m_cb_prefix_instruction[0x5E] =
     m_cb_prefix_instruction[0x5F] =
     m_cb_prefix_instruction[0x60] =
     m_cb_prefix_instruction[0x61] =
     m_cb_prefix_instruction[0x62] =
     m_cb_prefix_instruction[0x63] =
     m_cb_prefix_instruction[0x64] =
     m_cb_prefix_instruction[0x65] =
     m_cb_prefix_instruction[0x66] =
     m_cb_prefix_instruction[0x67] =
     m_cb_prefix_instruction[0x68] =
     m_cb_prefix_instruction[0x69] =
     m_cb_prefix_instruction[0x6A] =
     m_cb_prefix_instruction[0x6B] =
     m_cb_prefix_instruction[0x6C] =
     m_cb_prefix_instruction[0x6D] =
     m_cb_prefix_instruction[0x6E] =
     m_cb_prefix_instruction[0x6F] =
     m_cb_prefix_instruction[0x70] =
     m_cb_prefix_instruction[0x71] =
     m_cb_prefix_instruction[0x72] =
     m_cb_prefix_instruction[0x73] =
     m_cb_prefix_instruction[0x74] =
     m_cb_prefix_instruction[0x75] =
     m_cb_prefix_instruction[0x76] =
     m_cb_prefix_instruction[0x77] =
     m_cb_prefix_instruction[0x78] =
     m_cb_prefix_instruction[0x79] =
     m_cb_prefix_instruction[0x7A] =
     m_cb_prefix_instruction[0x7B] =
     m_cb_prefix_instruction[0x7C] =
     m_cb_prefix_instruction[0x7D] =
     m_cb_prefix_instruction[0x7E] =
     m_cb_prefix_instruction[0x7F] =
     m_cb_prefix_instruction[0x80] =
     m_cb_prefix_instruction[0x81] =
     m_cb_prefix_instruction[0x82] =
     m_cb_prefix_instruction[0x83] =
     m_cb_prefix_instruction[0x84] =
     m_cb_prefix_instruction[0x85] =
     m_cb_prefix_instruction[0x86] =
     m_cb_prefix_instruction[0x87] =
     m_cb_prefix_instruction[0x88] =
     m_cb_prefix_instruction[0x89] =
     m_cb_prefix_instruction[0x8A] =
     m_cb_prefix_instruction[0x8B] =
     m_cb_prefix_instruction[0x8C] =
     m_cb_prefix_instruction[0x8D] =
     m_cb_prefix_instruction[0x8E] =
     m_cb_prefix_instruction[0x8F] =
     m_cb_prefix_instruction[0x90] =
     m_cb_prefix_instruction[0x91] =
     m_cb_prefix_instruction[0x92] =
     m_cb_prefix_instruction[0x93] =
     m_cb_prefix_instruction[0x94] =
     m_cb_prefix_instruction[0x95] =
     m_cb_prefix_instruction[0x96] =
     m_cb_prefix_instruction[0x97] =
     m_cb_prefix_instruction[0x98] =
     m_cb_prefix_instruction[0x99] =
     m_cb_prefix_instruction[0x9A] =
     m_cb_prefix_instruction[0x9B] =
     m_cb_prefix_instruction[0x9C] =
     m_cb_prefix_instruction[0x9D] =
     m_cb_prefix_instruction[0x9E] =
     m_cb_prefix_instruction[0x9F] =
     m_cb_prefix_instruction[0xA0] =
     m_cb_prefix_instruction[0xA1] =
     m_cb_prefix_instruction[0xA2] =
     m_cb_prefix_instruction[0xA3] =
     m_cb_prefix_instruction[0xA4] =
     m_cb_prefix_instruction[0xA5] =
     m_cb_prefix_instruction[0xA6] =
     m_cb_prefix_instruction[0xA7] =
     m_cb_prefix_instruction[0xA8] =
     m_cb_prefix_instruction[0xA9] =
     m_cb_prefix_instruction[0xAA] =
     m_cb_prefix_instruction[0xAB] =
     m_cb_prefix_instruction[0xAC] =
     m_cb_prefix_instruction[0xAD] =
     m_cb_prefix_instruction[0xAE] =
     m_cb_prefix_instruction[0xAF] =
     m_cb_prefix_instruction[0xB0] =
     m_cb_prefix_instruction[0xB1] =
     m_cb_prefix_instruction[0xB2] =
     m_cb_prefix_instruction[0xB3] =
     m_cb_prefix_instruction[0xB4] =
     m_cb_prefix_instruction[0xB5] =
     m_cb_prefix_instruction[0xB6] =
     m_cb_prefix_instruction[0xB7] =
     m_cb_prefix_instruction[0xB8] =
     m_cb_prefix_instruction[0xB9] =
     m_cb_prefix_instruction[0xBA] =
     m_cb_prefix_instruction[0xBB] =
     m_cb_prefix_instruction[0xBC] =
     m_cb_prefix_instruction[0xBD] =
     m_cb_prefix_instruction[0xBE] =
     m_cb_prefix_instruction[0xBF] =
     m_cb_prefix_instruction[0xC0] =
     m_cb_prefix_instruction[0xC1] =
     m_cb_prefix_instruction[0xC2] =
     m_cb_prefix_instruction[0xC3] =
     m_cb_prefix_instruction[0xC4] =
     m_cb_prefix_instruction[0xC5] =
     m_cb_prefix_instruction[0xC6] =
     m_cb_prefix_instruction[0xC7] =
     m_cb_prefix_instruction[0xC8] =
     m_cb_prefix_instruction[0xC9] =
     m_cb_prefix_instruction[0xCA] =
     m_cb_prefix_instruction[0xCB] =
     m_cb_prefix_instruction[0xCC] =
     m_cb_prefix_instruction[0xCD] =
     m_cb_prefix_instruction[0xCE] =
     m_cb_prefix_instruction[0xCF] =
     m_cb_prefix_instruction[0xD0] =
     m_cb_prefix_instruction[0xD1] =
     m_cb_prefix_instruction[0xD2] =
     m_cb_prefix_instruction[0xD3] =
     m_cb_prefix_instruction[0xD4] =
     m_cb_prefix_instruction[0xD5] =
     m_cb_prefix_instruction[0xD6] =
     m_cb_prefix_instruction[0xD7] =
     m_cb_prefix_instruction[0xD8] =
     m_cb_prefix_instruction[0xD9] =
     m_cb_prefix_instruction[0xDA] =
     m_cb_prefix_instruction[0xDB] =
     m_cb_prefix_instruction[0xDC] =
     m_cb_prefix_instruction[0xDD] =
     m_cb_prefix_instruction[0xDE] =
     m_cb_prefix_instruction[0xDF] =
     m_cb_prefix_instruction[0xE0] =
     m_cb_prefix_instruction[0xE1] =
     m_cb_prefix_instruction[0xE2] =
     m_cb_prefix_instruction[0xE3] =
     m_cb_prefix_instruction[0xE4] =
     m_cb_prefix_instruction[0xE5] =
     m_cb_prefix_instruction[0xE6] =
     m_cb_prefix_instruction[0xE7] =
     m_cb_prefix_instruction[0xE8] =
     m_cb_prefix_instruction[0xE9] =
     m_cb_prefix_instruction[0xEA] =
     m_cb_prefix_instruction[0xEB] =
     m_cb_prefix_instruction[0xEC] =
     m_cb_prefix_instruction[0xED] =
     m_cb_prefix_instruction[0xEE] =
     m_cb_prefix_instruction[0xEF] =
     m_cb_prefix_instruction[0xF0] =
     m_cb_prefix_instruction[0xF1] =
     m_cb_prefix_instruction[0xF2] =
     m_cb_prefix_instruction[0xF3] =
     m_cb_prefix_instruction[0xF4] =
     m_cb_prefix_instruction[0xF5] =
     m_cb_prefix_instruction[0xF6] =
     m_cb_prefix_instruction[0xF7] =
     m_cb_prefix_instruction[0xF8] =
     m_cb_prefix_instruction[0xF9] =
     m_cb_prefix_instruction[0xFA] =
     m_cb_prefix_instruction[0xFB] =
     m_cb_prefix_instruction[0xFC] =
     m_cb_prefix_instruction[0xFD] =
     m_cb_prefix_instruction[0xFE] =
     m_cb_prefix_instruction[0xFF] =
*/

    m_base_instruction[0x02] = [this]() { m_memory.write( m_registers.bc, m_registers.a ); return 8; };

    m_base_instruction[0x80] = [this]() { _add( m_registers.b, false ); return 4; };
    m_base_instruction[0x86] = [this]() { _add( m_memory.read_8( m_registers.hl ), false ); return 8; };
    m_base_instruction[0xC6] = [this]() { _add( m_memory.read_8( m_registers.pc++ ), false ); return 8; };
    m_base_instruction[0x88] = [this]() { _add( m_registers.b, true ); return 4; };
    m_base_instruction[0x90] = [this]() { _sub( m_registers.b, false ); return 4; };
    m_base_instruction[0x98] = [this]() { _sub( m_registers.b, true ); return 4; };
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

// Aritmethic
void CPU::_add( u8 const rhs, bool const carry )
{
    u8 const carry_value = carry && _is_flag_set( Flags::CARRY ) ? 1 : 0;

    _process_carry_flag( m_registers.a + rhs + carry_value );
    _process_half_carry_flag( rhs, carry_value, true );

    m_registers.a += rhs + carry_value;

    _process_zero_flag();
    _reset_flag( Flags::ADD_SUB );
}

void CPU::_sub( u8 const rhs, bool const carry )
{
    u8 const carry_value = carry && _is_flag_set( Flags::CARRY ) ? 1 : 0;

    _process_carry_flag( m_registers.a - rhs - carry_value );
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
    _process_carry_flag( aux );
    _set_flag( Flags::ADD_SUB );
}

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
