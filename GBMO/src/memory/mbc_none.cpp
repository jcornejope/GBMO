
#include "memory/mbc_none.h"
#include <cassert>

u8 MBC_None::read( u16 address )
{
    assert( ( address < 0x8000 ) || ( address >= 0xA000 && address < 0xC000 ) );

    if( address < 0x8000 )
        return m_cartridge_rom[address];
    else if( m_cartridge_ram != nullptr && address >= 0xA000 && address < 0xC000 )
        return m_cartridge_ram[address - 0xA000];

    assert( false );
    return 0xFF;
}

void MBC_None::write( u16 /*address*/, u8 /*data*/ )
{
    // Do nothing. NOT ALLOWED
    assert( false );
}
