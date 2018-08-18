#pragma once

#include "cartridge\cartridge.h"
#include "memory\memory_system.h"
#include "cpu\cpu.h"

struct Options;

class GBMO
{
public:
    GBMO( Options const& options );

private:
    Cartridge m_cartridge;
    MemorySystem m_memory_system;
    CPU m_cpu;
};
