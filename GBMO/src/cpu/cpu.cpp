
#include "cpu/cpu.h"
#include "memory/memory_system.h"

float const CPU::CPU_SPEED              = 4.194304f;
float const CPU::CPU_SPEED_CGB_DOUBLE   = 8.4f;

CPU::CPU( MemorySystem& memory )
    : m_memory( memory )
{
    m_registers.a = 0x0F;
    m_registers.b = 0xFF;

    _initialize_instruction_tables();
    
    this->m_base_instruction[0x47]();
    this->m_base_instruction[0x47]();
}
