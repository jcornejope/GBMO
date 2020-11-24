#pragma once

#include "utils/types.h"

class MemorySystem;

class Sound
{
public:
    enum SND_ON_OFF : u8
    {
        MASTER_SWITCH  = 1 << 7, // Bit 7 - All sound on / off ( 0: stop all sound circuits ) ( Read / Write )
        IS_CH4_ENABLED = 1 << 3, // Bit 3 - Sound 4 ON flag( Read Only )
        IS_CH3_ENABLED = 1 << 2, // Bit 2 - Sound 3 ON flag( Read Only )
        IS_CH2_ENABLED = 1 << 1, // Bit 1 - Sound 2 ON flag( Read Only )
        IS_CH1_ENABLED = 1,      // Bit 0 - Sound 1 ON flag( Read Only )
    };

    Sound( MemorySystem& memory );

    void disable();
    void enable();
    bool isEnabled() const;

private:
    MemorySystem& m_memory;
};
