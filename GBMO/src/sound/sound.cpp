#include "sound.h"

#include "memory/memory_system.h"

Sound::Sound( MemorySystem& memory )
    : m_memory( memory )
{
}

void Sound::enable()
{
    // TODO
    // Frame sequencer is reset so that the next step will be 0
    // The square duty units are reset to the first step of the waveform
    // The wave channel's sample buffer is reset to 0.

}

void Sound::disable()
{
    // Destroy content of all sound registers!
    u8 const data = 0;
    for( u16 addr = SND_PWR_REG_START_ADDR; addr <= SND_PWR_REG_END_ADDR; ++addr )
        m_memory.non_protected_write( addr, data );
}

bool Sound::isEnabled() const
{
    return ( m_memory.read_8( SND_ON_OFF_ADDR ) & MASTER_SWITCH ) != 0;
}
