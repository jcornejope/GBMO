#pragma once

#include "utils/types.h"
#include <string>

struct Options
{
    Options() {}

    std::string m_rom_path;

    u32 m_resolution_x;
    u32 m_resolution_y;
    float m_volume;
    bool m_log;
};
