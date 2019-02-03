#pragma once

#include "utils/types.h"

enum class CartridgeType : u8
{
    ROM_ONLY                    = 0x00, // ROM ONLY                 
    MBC1                        = 0x01, // MBC1                     
    MBC1_RAM                    = 0x02, // MBC1+RAM                 
    MBC1_RAM_BATTERY            = 0x03, // MBC1+RAM+BATTERY         
    MBC2                        = 0x05, // MBC2                     
    MBC2_BATTERY                = 0x06, // MBC2+BATTERY             
    ROM_RAM                     = 0x08, // ROM+RAM                  
    ROM_RAM_BATTERY             = 0x09, // ROM+RAM+BATTERY          
    MMM01                       = 0x0B, // MMM01                    
    MMM01_RAM                   = 0x0C, // MMM01+RAM                
    MMM01_RAM_BATTERY           = 0x0D, // MMM01+RAM+BATTERY        
    MBC3_TIMER_BATTERY          = 0x0F, // MBC3+TIMER+BATTERY       
    MBC3_TIMER_RAM_BATTERY      = 0x10, // MBC3+TIMER+RAM+BATTERY   
    MBC3                        = 0x11, // MBC3                     
    MBC3_RAM                    = 0x12, // MBC3+RAM
    MBC3_RAM_BATTERY            = 0x13, // MBC3 + RAM + BATTERY
    MBC4                        = 0x15, // MBC4
    MBC4_RAM                    = 0x16, // MBC4 + RAM
    MBC4_RAM_BATTERY            = 0x17, // MBC4 + RAM + BATTERY
    MBC5                        = 0x19, // MBC5
    MBC5_RAM                    = 0x1A, // MBC5 + RAM
    MBC5_RAM_BATTERY            = 0x1B, // MBC5 + RAM + BATTERY
    MBC5_RUMBLE                 = 0x1C, // MBC5 + RUMBLE
    MBC5_RUMBLE_RAM             = 0x1D, // MBC5 + RUMBLE + RAM
    MBC5_RUMBLE_RAM_BATTERY     = 0x1E, // MBC5 + RUMBLE + RAM + BATTERY
    POCKET_CAMERA               = 0xFC, // POCKET CAMERA
    BANDAI_TAMA5                = 0xFD, // BANDAI TAMA5
    HuC3                        = 0xFE, // HuC3
    HuC1_RAM_BATTERY            = 0xFF, // HuC1 + RAM + BATTERY
};

enum class ROMSize : u8
{
    ROM_32      = 0x00, // 00h - 32KByte( no ROM banking )
    ROM_64      = 0x01, // 01h - 64KByte( 4 banks )
    ROM_128     = 0x02, // 02h - 128KByte( 8 banks )
    ROM_256     = 0x03, // 03h - 256KByte( 16 banks )
    ROM_512     = 0x04, // 04h - 512KByte( 32 banks )
    ROM_1024    = 0x05, // 05h - 1MByte( 64 banks ) - only 63 banks used by MBC1
    ROM_2048    = 0x06, // 06h - 2MByte( 128 banks ) - only 125 banks used by MBC1
    ROM_4096    = 0x07, // 07h - 4MByte( 256 banks )
    ROM_1152    = 0x52, // 52h - 1.1MByte( 72 banks )
    ROM_1280    = 0x53, // 53h - 1.2MByte( 80 banks )
    ROM_1536    = 0x54, // 54h - 1.5MByte( 96 banks )
};

enum class RAMSize : u8
{
    NONE    = 0x00, // 00h - None
    RAM_2   = 0x01, // 01h - 2 KBytes
    RAM_8   = 0x02, // 02h - 8 Kbytes
    RAM_32  = 0x03, // 03h - 32 KBytes( 4 banks of 8KBytes each )

};

enum class DestinationCode : u8
{
    JAP     = 0x00,
    NO_JAP  = 0x01
};

enum class CGBSupport : u8
{
    SUPPORTS = 0x00,
    CGB_ONLY = 0x80,
    NO_CGB_NO_PALETTE_INIT = 0xFF
};

/* New license code (not sure how the 2 bytes combines to form this values)
00 - none                     01 - nintendo           08 - capcom
13 - electronic arts          18 - hudsonsoft         19 - b - ai
20 - kss                      22 - pow                24 - pcm complete
25 - san - x                    28 - kemco japan        29 - seta
30 - viacom                   31 - nintendo           32 - bandia
33 - ocean / acclaim            34 - konami             35 - hector
37 - taito                    38 - hudson             39 - banpresto
41 - ubi soft                 42 - atlus              44 - malibu
46 - angel                    47 - pullet - proof       49 - irem
50 - absolute                 51 - acclaim            52 - activision
53 - american sammy           54 - konami             55 - hi tech entertainment
56 - ljn                      57 - matchbox           58 - mattel
59 - milton bradley           60 - titus              61 - virgin
64 - lucasarts                67 - ocean              69 - electronic arts
70 - infogrames               71 - interplay          72 - broderbund
73 - sculptured               75 - sci                78 - t * hq
79 - accolade                 80 - misawa             83 - lozc
86 - tokuma shoten i * 87 - tsukuda ori * 91 - chun soft
92 - video system             93 - ocean / acclaim      95 - varie
96 - yonezawa / s'pal 97- kaneko 99- pack in soft
*/

/* Old license code
00- none               01- nintendo           08- capcom
09- hot-b              0A- jaleco             0B- coconuts
0C- elite systems      13- electronic arts    18- hudsonsoft
19- itc entertainment  1A- yanoman            1D- clary
1F- virgin             24- pcm complete       25- san-x
28- kotobuki systems   29- seta               30- infogrames
31- nintendo           32- bandai             33- "see above"
34- konami             35- hector             38- capcom
39- banpresto          3C- *entertainment i   3E- gremlin
41- ubi soft           42- atlus              44- malibu
46- angel              47- spectrum holoby    49- irem
4A- virgin             4D- malibu             4F- u.s. gold
50- absolute           51- acclaim            52- activision
53- american sammy     54- gametek            55- park place
56- ljn                57- matchbox           59- milton bradley
5A- mindscape          5B- romstar            5C- naxat soft
5D- tradewest          60- titus              61- virgin
67- ocean              69- electronic arts    6E- elite systems
6F- electro brain      70- infogrames         71- interplay
72- broderbund         73- sculptered soft    75- the sales curve
78- t*hq               79- accolade           7A- triffix entertainment
7C- microprose         7F- kemco              80- misawa entertainment
83- lozc               86- *tokuma shoten i   8B- bullet-proof software
8C- vic tokai          8E- ape                8F- i'max
91- chun soft          92- video system       93- tsuburava
95- varie              96- yonezawa/s'pal     97- kaneko
99- arc                9A- nihon bussan       9B- tecmo
9C- imagineer          9D- banpresto          9F- nova
A1- hori electric      A2- bandai             A4- konami
A6- kawada             A7- takara             A9- technos japan
AA- broderbund         AC- toei animation     AD- toho
AF- namco              B0- acclaim            B1- ascii or nexoft
B2- bandai             B4- enix               B6- hal
B7- snk                B9- pony canyon        BA- *culture brain o
BB- sunsoft            BD- sony imagesoft     BF- sammy
C0- taito              C2- kemco              C3- squaresoft
C4- *tokuma shoten i   C5- data east          C6- tonkin house
C8- koei               C9- ufl                CA- ultra
CB- vap                CC- use                CD- meldac
CE- *pony canyon or    CF- angel              D0- taito
D1- sofel              D2- quest              D3- sigma enterprises
D4- ask kodansha       D6- naxat soft         D7- copya systems
D9- banpresto          DA- tomy               DB- ljn
DD- ncs                DE- human              DF- altron
E0- jaleco             E1- towachiki          E2- uutaka
E3- varie              E5- epoch              E7- athena
E8- asmik              E9- natsume            EA- king records
EB- atlus              EC- epic/sony records  EE- igs
F0- a wave F3- extreme entertainment FF- ljn
*/

///////////////////////////////////////////////
// String conversion functions
///////////////////////////////////////////////
char const* to_string( CartridgeType type );
char const* to_string( ROMSize type );
char const* to_string( RAMSize type );
char const* to_string( DestinationCode type );
char const* to_string( CGBSupport type );
