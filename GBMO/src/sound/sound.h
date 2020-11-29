#pragma once

#include "utils/types.h"

#include <SDL_audio.h>

class MemorySystem;
class SquareChannel;

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

    enum SND_OUTPUT_TERMINAL : u8
    {
        SO2_CH4 = 1 << 7, // Bit 7 - Output sound 4 to SO2 terminal
        SO2_CH3 = 1 << 6, // Bit 6 - Output sound 3 to SO2 terminal
        SO2_CH2 = 1 << 5, // Bit 5 - Output sound 2 to SO2 terminal
        SO2_CH1 = 1 << 4, // Bit 4 - Output sound 1 to SO2 terminal
        SO1_CH4 = 1 << 3, // Bit 3 - Output sound 4 to SO1 terminal
        SO1_CH3 = 1 << 2, // Bit 2 - Output sound 3 to SO1 terminal
        SO1_CH2 = 1 << 1, // Bit 1 - Output sound 2 to SO1 terminal
        SO1_CH1 = 1, // Bit 0 - Output sound 1 to SO1 terminal
    };


    enum SND_CONTROL : u8
    {
        VIN_TO_SO2 = 1 << 7,    // Bit 7 - Output Vin to SO2 terminal( 1 = Enable )
        SO2_VOLUME = 0x70,      // Bit 6 - 4 - SO2 output level( volume )  ( 0 - 7 )
        VIN_TO_SO1 = 1 << 3,    // Bit 3 - Output Vin to SO1 terminal( 1 = Enable )
        SO1_VOLUME = 0x07,      // Bit 2 - 0 - SO1 output level( volume )  ( 0 - 7 )
    };

    Sound( MemorySystem& memory );

    bool init();
    void deinit();

    void update( u32 cycles );

    void disable();
    void enable();
    bool is_enabled() const;
    bool is_channel_enabled( SND_OUTPUT_TERMINAL const channel_flag ) const;

    //void fill_audio_buffer( Uint8* stream, int len );

private:

    SquareChannel* m_square1_channel;
    SquareChannel* m_square2_channel;
    //SquareOsc m_square1_channel;
    //SquareOsc m_square2_channel;
    //WaveOsc m_wave_channel;
    //NoiseOsc m_noise_channel;
    //SilenceOsc m_silence_channel;

    MemorySystem& m_memory;

    u32 m_sound_cycles;
    u32 m_buff_write_pos;

    u32 m_mixer_cycles;

    sample_t* m_sound_buffer;
    SDL_AudioStream* m_stream;
    SDL_AudioDeviceID m_device;
};
