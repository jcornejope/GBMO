
#include "sound.h"

#include "channels.h"

#include "memory/memory_system.h"
#include "memory/memory_span.h"
#include "utils/assert.h"
#include "utils/logger.h"
#include "utils/utils.h"

#include <SDL.h>
#include <functional>

void audio_callback( void* userdata, Uint8* stream, int len )
{
    Sound* sound = reinterpret_cast<Sound*>( userdata );
    sound->fill_audio_buffer( stream, len );
}

Sound::Sound( MemorySystem& memory )
    : m_memory( memory )
    , m_sound_cycles( 0 )
    , m_buff_write_pos( 0 )
    , m_sound_buffer( nullptr )
    , m_stream( nullptr )
    , m_device( 0 )
{
}

bool Sound::init()
{
    SDL_AudioSpec desired, obtained;

    SDL_memset( &desired, 0, sizeof( desired ) );
    desired.freq = 44100;
    desired.format = AUDIO_S16SYS;
    desired.channels = 2;
    desired.samples = AUDIO_BUFFER_SIZE / desired.channels;
    desired.callback = nullptr; // audio_callback;
    desired.userdata = this;

    m_device = SDL_OpenAudioDevice( NULL, 0, &desired, &obtained, 0 );
    if( m_device == 0 ) 
    {
        LOG_E( LogCat::SOUND, "Failed opening audio device [%s]", SDL_GetError() );
        ERROR_MSG( "Failed opening audio device [%s]", SDL_GetError() );
        return false;
    }

    m_stream = SDL_NewAudioStream( obtained.format, obtained.channels, obtained.samples, desired.format, desired.channels, desired.samples );
    if( m_stream == nullptr )
    {
        LOG_E( LogCat::SOUND, "Failed creating audio stream [%s]", SDL_GetError() );
        ERROR_MSG( "Failed creating audio stream [%s]", SDL_GetError() );
        return false;
    }

    SDL_PauseAudioDevice( m_device, 0 ); // This means unpause!

    m_sound_buffer = new sample_t[AUDIO_BUFFER_SIZE];
    m_square1_channel = new SquareChannel( MemorySpan( m_memory, CH1_SWEEP_ADDR, 5 ) );
    m_square2_channel = new SquareChannel( MemorySpan( m_memory, 0xFF15, 5 ) );

    m_ch1_ms = new MemorySpan( m_memory, CH1_SWEEP_ADDR, 5 );

    return true;
}

void Sound::deinit()
{
    if( m_sound_buffer != nullptr )
    {
        delete[] m_sound_buffer;
        m_sound_buffer = nullptr;
    }

    if( m_square1_channel != nullptr )
    {
        delete m_square1_channel;
        m_square1_channel = nullptr;
    }

    if( m_square2_channel != nullptr )
    {
        delete m_square2_channel;
        m_square2_channel = nullptr;
    }
    
    if( m_device != 0 )
        SDL_CloseAudioDevice( m_device );


    delete m_ch1_ms;
}

void Sound::update( u32 cycles )
{
    m_sound_cycles += cycles;

    for( u32 i = 0; i < cycles; ++i )
    {
        // update oscillators
        m_square1_channel->tick();
        m_square2_channel->tick();

        // update frame sequencer

        // update mixer (ignoring Vin for now as it was never used).
        ++m_mixer_cycles;
        if( m_mixer_cycles > 95 )
        {
            m_mixer_cycles = 0;

            sample_t sample = 0;
            sample_t const sq1_out = static_cast<sample_t>( m_square1_channel->get_output() ) * 128;
            SDL_MixAudioFormat( (u8*)&sample, (u8*)&sq1_out, AUDIO_S16SYS, sizeof( sample_t ), SDL_MIX_MAXVOLUME );
            sample_t const sq2_out = static_cast<sample_t>( m_square2_channel->get_output() ) * 128;
            SDL_MixAudioFormat( (u8*)&sample, (u8*)&sq2_out, AUDIO_S16SYS, sizeof( sample_t ), SDL_MIX_MAXVOLUME );

            m_sound_buffer[m_buff_write_pos++] = sample;
            m_sound_buffer[m_buff_write_pos++] = sample;

            //m_sound_buffer[m_buff_write_pos++] = static_cast<sample_t>( rand() );
            //m_sound_buffer[m_buff_write_pos++] = static_cast<sample_t>( rand() );

            if( m_buff_write_pos == AUDIO_BUFFER_SIZE )
            {
                m_buff_write_pos = 0;
                SDL_QueueAudio( m_device, m_sound_buffer, AUDIO_BUFFER_SIZE * sizeof( sample_t ) );
            }
        }
    }
}

void Sound::enable()
{
    // TODO
    // Frame sequencer is reset so that the next step will be 0
    // The square duty units are reset to the first step of the waveform
    // The wave channel's sample buffer is reset to 0.
    if(m_square1_channel)
        m_square1_channel->reset();

    if( m_square2_channel )
        m_square2_channel->reset();
}

void Sound::disable()
{
    // Destroy content of all sound registers!
    u8 const data = 0;
    for( u16 addr = SND_PWR_REG_START_ADDR; addr <= SND_PWR_REG_END_ADDR; ++addr )
        m_memory.non_protected_write( addr, data );
}

bool Sound::is_enabled() const
{
    return ( m_memory.read_8( SND_ON_OFF_ADDR ) & MASTER_SWITCH ) != 0;
}

void Sound::fill_audio_buffer( Uint8* stream, int len )
{
    static sample_t buf[AUDIO_BUFFER_SIZE];

    ASSERT( AUDIO_BUFFER_SIZE * sizeof( sample_t ) >= len );

    auto const bytes_in_stream = SDL_AudioStreamAvailable( m_stream );
    auto bytes_to_read_from_stream = ( bytes_in_stream < len ) ? bytes_in_stream : len;
    if( bytes_in_stream > 0 )
    {
        if( SDL_AudioStreamGet( m_stream, buf, bytes_to_read_from_stream ) < 0 )
        {
            LOG_E( LogCat::SOUND, "Failed to get [%d] samples from audio stream [%s]", bytes_to_read_from_stream, SDL_GetError() );
            bytes_to_read_from_stream = 0;
        }
    }

    size_t const silence_padding = static_cast<size_t>( len ) - static_cast<size_t>( bytes_to_read_from_stream );
    memset( buf + ( bytes_to_read_from_stream / sizeof(sample_t) ), 0, silence_padding );

    memcpy( stream, buf, len );
}
