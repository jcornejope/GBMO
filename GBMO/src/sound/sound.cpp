#include "sound.h"

#include "memory/memory_system.h"
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
    desired.callback = audio_callback;
    desired.userdata = this; // Probably can use SDL_AudioQueue instead of manually filling the audio buffer...
    
    m_device = SDL_OpenAudioDevice( NULL, 0, &desired, &obtained, 0 );
    if( m_device == 0 ) 
    {
        LOG_E( LogCat::SOUND, "Failed opening audio device [%s]", SDL_GetError() );
        ERROR_MSG( "Failed opening audio device [%s]", SDL_GetError() );
        return false;
    }

    SDL_PauseAudioDevice( m_device, 0 ); // This means unpause!

    return true;
}

void Sound::deinit()
{
    if( m_device != 0 )
        SDL_CloseAudioDevice( m_device );
}

void Sound::update( u32 cycles )
{
    m_sound_cycles += cycles;
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

bool Sound::is_enabled() const
{
    return ( m_memory.read_8( SND_ON_OFF_ADDR ) & MASTER_SWITCH ) != 0;
}

void Sound::fill_audio_buffer( Uint8* stream, int len )
{
    // NOISE!
    //u16 buf[AUDIO_BUFFER_SIZE]; 
    //for( u32 i = 0; i < AUDIO_BUFFER_SIZE; ++i )
    //    buf[i] = static_cast<u16>( rand() * 2 * 3.141596 );

    //memcpy( stream, buf, len);

    memset( stream, 0, len );
}
