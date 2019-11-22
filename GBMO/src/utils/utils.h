#pragma once

#include "utils/types.h"
#include <sstream>

static u8 nintendo_logo[0x30] =
{
    0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00, 0x0B, 0x03, 0x73, 0x00, 0x83, 0x00, 0x0C, 0x00, 0x0D,
    0x00, 0x08, 0x11, 0x1F, 0x88, 0x89, 0x00, 0x0E, 0xDC, 0xCC, 0x6E, 0xE6, 0xDD, 0xDD, 0xD9, 0x99,
    0xBB, 0xBB, 0x67, 0x63, 0x6E, 0x0E, 0xEC, 0xCC, 0xDD, 0xDC, 0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E
};

inline char const* bool_to_alpha( bool const expr ) 
{ 
    return expr ? "true" : "false"; 
}

namespace Version
{
    u32 const MAYOR = 0;
    u32 const MINOR = 8;
    //u32 const BUILD = 0;

    inline std::string to_string()
    {
        std::stringstream stream;
        stream << "v" << MAYOR << "." << MINOR;
        return stream.str();
    }
}

namespace LogCat
{
    static char const* SYSTEM  = "SYSTEM";
    static char const* ROM     = "ROM";
    static char const* DISPLAY = "DISPLAY";
    static char const* CPU     = "CPU";
    static char const* UPDATE  = "UPDATE";
}
