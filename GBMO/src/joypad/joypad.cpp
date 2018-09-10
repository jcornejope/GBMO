
#include "joypad/joypad.h"
#include "cpu/cpu.h"
#include "memory/memory_system.h"

Joypad::Joypad( CPU& cpu, MemorySystem& memory )
    : m_cpu( cpu )
    , m_memory( memory )
{

}

void Joypad::handle_input_event( SDL_Event & event )
{
    (void)event;
    // TODO IMPLEMENT!!
}

bool Joypad::parse_input_mapping( std::string const & config_file_path )
{
    (void)config_file_path;
    // TODO IMPLEMENT!!
    return false;
}
