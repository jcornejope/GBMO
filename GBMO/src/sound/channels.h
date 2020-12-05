#pragma once

#include "utils/types.h"
#include "memory/memory_span.h"

#include <SDL_audio.h>

class SquareChannel
{
    enum Registers : u16
    {
        REG_SWEEP = 0,      // NRx0
        REG_DUTY_N_LENGHT,  // NRx1
        REG_VOLUME,         // NRx2
        REG_FREQUENCY_LSB,  // NRx3
        REG_TL_N_FREQ_MSB,  // NRx4
    };

    enum RegisterFlags : u8
    {
        // NRx0
        FLAGS_SWEEP_PERIOD    = 0x70,
        FLAGS_NEGATE          = 0x08,
        FLAGS_SWEEP_SHIFT     = 0x07,

        // NRx1
        FLAGS_DUTY            = 0xC0,
        FLAGS_LENGTH          = 0x3F,

        // NRx2
        FLAGS_VOLUME          = 0xF0,
        FLAGS_ENV_MODE        = 0x08,
        FLAGS_PERIOD          = 0x07,

        // NRx4
        FLAGS_TRIGGER         = 0x80,
        FLAGS_LENGTH_ENABLE   = 0x40,
        FLAGS_FREQUENCY_MSB   = 0x07,
    };

    static u8 const WAVEFORM[4];

public:
    SquareChannel( MemorySpan&& osc_registers );

    void reset();

    void tick();
    void tick_lenght() {};
    void tick_envelope() {};
    void tick_sweep() {};

    u8 get_output() const { return m_output; }

private:
    u16 _get_frequency() const;
    u8 _get_volume() const;
    u8 _get_duty() const;

    MemorySpan registers;

    u32 m_timer = 1u;
    u8 m_output = 0;
    u8 m_waveform_phase = 0;
};