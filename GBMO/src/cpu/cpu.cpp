
#include "cpu/cpu.h"
#include "memory/memory_system.h"

float const CPU::CPU_SPEED              = 4.194304f;
float const CPU::CPU_SPEED_CGB_DOUBLE   = 8.4f;

CPU::CPU( MemorySystem& memory )
    : m_memory( memory )
{
}
