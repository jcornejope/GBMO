#pragma once

#include "utils/types.h"

#include <SDL_audio.h>

class MemorySystem;
class SquareChannel;
class MemorySpan;

class Sound
{
    static u32 const AUDIO_BUFFER_SIZE = 8192;
    using sample_t = s16;

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

    bool init();
    void deinit();

    void update( u32 cycles );

    void disable();
    void enable();
    bool is_enabled() const;

    void fill_audio_buffer( Uint8* stream, int len );

private:
    SquareChannel* m_square1_channel;
    SquareChannel* m_square2_channel;
    //SquareOsc m_square1_channel;
    //SquareOsc m_square2_channel;
    //WaveOsc m_wave_channel;
    //NoiseOsc m_noise_channel;
    //SilenceOsc m_silence_channel;

    MemorySystem& m_memory;
    MemorySpan* m_ch1_ms;

    u32 m_sound_cycles;
    u32 m_buff_write_pos;

    u32 m_mixer_cycles;

    sample_t* m_sound_buffer;
    SDL_AudioStream* m_stream;
    SDL_AudioDeviceID m_device;
};
