
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
    : m_registers( std::move( osc_registers ) )
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

    //if( m_enabled && _is_dac_enabled() )
    {
        // Osc
        static u8 const AMP_RATIO = 0xFF / 0xF;
        u8 const duty = _get_duty();
        u8 const wave_output = ( ( WAVEFORM[duty] & ( 1 << m_waveform_phase ) ) >> m_waveform_phase );
        m_output = wave_output * m_volume * AMP_RATIO;
    }
    //else
    //{
    //    m_output = 0;
    //}
}

void SquareChannel::tick_lenght()
{
    if( m_length_counter && ( m_registers[REG_TL_N_FREQ_MSB] & FLAGS_LENGTH_ENABLE ) )
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
    if( m_vol_envelope_enabled )
    {
        --m_vol_envelope_counter;
        if( m_vol_envelope_counter == 0 )
        {
            _read_envelope_counter();
            if( m_registers[REG_VOLUME] & FLAGS_PERIOD )
            {
                s8 const vol = m_volume + ( m_registers[REG_VOLUME] & FLAGS_ENV_MODE ) ? 1 : -1;
                if( vol >= 0 && vol <= 15 )
                    m_volume = vol;
                else
                    m_vol_envelope_enabled = false;
            }
        }
    }
}

void SquareChannel::tick_sweep()
{

}

void SquareChannel::load_length_n_duty( u8 data )
{
    m_length_counter = 64 - ( data & FLAGS_LENGTH );
}

void SquareChannel::load_vol_envelop( u8 data )
{
    if( !_is_dac_enabled( data ) )
        m_enabled = false;

    _read_envelope_counter( data );

    m_volume = _get_volume( data );

    // TODO CGB handle "zombie" mode
}

void SquareChannel::load_tl_n_freq_msb( u8 data )
{
    if( data & FLAGS_LENGTH_ENABLE )
        m_vol_envelope_enabled = true;

    // TODO: Trigger
}

u16 SquareChannel::_get_frequency() const
{
    return ( ( m_registers[REG_TL_N_FREQ_MSB] & FLAGS_FREQUENCY_MSB ) << 8 ) + m_registers[REG_FREQUENCY_LSB];
}

u8 SquareChannel::_get_volume() const
{
    return _get_volume( m_registers[REG_VOLUME] );
}

u8 SquareChannel::_get_volume( u8 const data ) const
{
    return ( data & FLAGS_VOLUME ) >> 4;
}

u8 SquareChannel::_get_duty() const 
{
    return ( m_registers[REG_DUTY_N_LENGHT] & FLAGS_DUTY ) >> 6;
}

bool SquareChannel::_is_dac_enabled() const
{
    return _is_dac_enabled( m_registers[REG_VOLUME] );
}

bool SquareChannel::_is_dac_enabled( u8 const data ) const
{
    return ( data & FLAGS_DAC_ENABLED ) != 0;
}

void SquareChannel::_read_envelope_counter()
{
    _read_envelope_counter( m_registers[REG_VOLUME] );
}

void SquareChannel::_read_envelope_counter( u8 const data )
{
    m_vol_envelope_counter = data & FLAGS_PERIOD;
    if( m_vol_envelope_counter == 0 )
        m_vol_envelope_counter = 8;
}
