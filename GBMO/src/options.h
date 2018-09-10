#pragma once

#include "utils/types.h"
#include <string>

struct Options
{
    Options() 
        : m_resolution_scale ( 1 ) 
        , m_volume( 0.f )
        , m_log( true )
    {}

    std::string m_rom_path;
    std::string m_input_config_file_path;

    u32 m_resolution_scale;
    float m_volume;
    bool m_log;
};
