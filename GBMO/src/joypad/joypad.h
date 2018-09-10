#pragma once

#include <SDL_events.h>
#include <string>

class CPU;
class MemorySystem;

class Joypad
{
public:
    Joypad( CPU& cpu, MemorySystem& memory );

    void handle_input_event( SDL_Event& event );
    bool parse_input_mapping( std::string const& config_file_path );

private:
    CPU& m_cpu;
    MemorySystem& m_memory;
};
