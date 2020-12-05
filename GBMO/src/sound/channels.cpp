
#include "channels.h"

#include <utility>

u8 const SquareChannel::WAVEFORM[4] =
{
    0x01, //00000001 
    0x81, //10000001 
    0x87, //10000111 
    0x7E  //01111110 
};

SquareChannel::SquareChannel( MemorySpan&& osc_registers )
    : registers( std::move( osc_registers ) )
{
}

void SquareChannel::reset()
{
    m_waveform_phase = 0;
}

void SquareChannel::tick()
{
    --m_timer;
    if( m_timer == 0 )
    {
        m_timer = ( 2048 - _get_frequency() ) * 4;
        m_waveform_phase = ++m_waveform_phase & 0x07;
    }

    //if( m_enabled )
    {
        // Osc
        static u8 const AMP_RATIO = 0xFF / 0xF;
        u8 const duty = _get_duty();
        u8 const wave_output = ( ( WAVEFORM[duty] & ( 1 << m_waveform_phase ) ) >> m_waveform_phase );
        m_output = wave_output * _get_volume() * AMP_RATIO;
    }
    //else
    //{
    //    m_output = 0;
    //}
}

void SquareChannel::tick_lenght()
{
    if( m_length_counter && ( registers[REG_TL_N_FREQ_MSB] & FLAGS_LENGTH_ENABLE ) )
    {
        --m_length_counter;
        if( m_length_counter == 0 )
        {
            m_enabled = false;
        }
    }
}

void SquareChannel::tick_envelope()
{

}

void SquareChannel::tick_sweep()
{

}

void SquareChannel::load_length_n_duty( u8 data )
{
    m_length_counter = 64 - ( data & FLAGS_LENGTH );
}

u16 SquareChannel::_get_frequency() const
{
    return ( ( registers[REG_TL_N_FREQ_MSB] & FLAGS_FREQUENCY_MSB ) << 8 ) + registers[REG_FREQUENCY_LSB];
}

u8 SquareChannel::_get_volume() const
{
    return ( registers[REG_VOLUME] & FLAGS_VOLUME ) >> 4;
}

u8 SquareChannel::_get_duty() const 
{
    return ( registers[REG_DUTY_N_LENGHT] & FLAGS_DUTY ) >> 6;
}