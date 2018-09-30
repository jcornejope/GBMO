
#include "memory/mbc_none.h"
#include "utils/assert.h"

u8 MBC_None::read( u16 address )
{
    ASSERT_MSG( ( address < 0x8000 ) || ( address >= 0xA000 && address < 0xC000 ), 
                "Address [%#06x] is not a valid cartridge address", address );

    if( address < 0x8000 )
        return m_cartridge_rom[address];
    else if( m_cartridge_ram != nullptr && address >= 0xA000 && address < 0xC000 )
        return m_cartridge_ram[address - 0xA000];

    //ERROR_MSG( "This shouldn't happen and is already asserted" );
    return 0xFF;
}

void MBC_None::write( u16 address, u8 /*data*/ )
{
    // TODO handle ram
    if( address < 0x8000 )
        return;

    //ERROR_MSG( "NOT IMPLEMENTED!" );
}
