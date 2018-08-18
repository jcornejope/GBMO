#include "catridge_utils.h"

char const* to_string( CartridgeType type )
{
    switch( type )
    {
    case CartridgeType::ROM_ONLY:                   return "ROM Only";                          break;
    case CartridgeType::MBC1:                       return "MBC1";                              break;
    case CartridgeType::MBC1_RAM:                   return "MBC1+RAM";                          break;
    case CartridgeType::MBC1_RAM_BATTERY:           return "MBC1+RAM+BATTERY";                  break;
    case CartridgeType::MBC2:                       return "MBC2";                              break;
    case CartridgeType::MBC2_BATTERY:               return "MBC2+BATTERY";                      break;
    case CartridgeType::ROM_RAM:                    return "ROM+RAM";                           break;
    case CartridgeType::ROM_RAM_BATTERY:            return "ROM+RAM+BATTERY";                   break;
    case CartridgeType::MMM01:                      return "MMM01";                             break;
    case CartridgeType::MMM01_RAM:                  return "MMM01+RAM";                         break;
    case CartridgeType::MMM01_RAM_BATTERY:          return "MMM01+RAM+BATTERY";                 break;
    case CartridgeType::MBC3_TIMER_BATTERY:         return "MBC3+TIMER+BATTERY";                break;
    case CartridgeType::MBC3_TIMER_RAM_BATTERY:     return "MBC3+TIMER+RAM+BATTERY";            break;
    case CartridgeType::MBC3:                       return "MBC3";                              break;
    case CartridgeType::MBC3_RAM:                   return "MBC3+RAM";                          break;
    case CartridgeType::MBC3_RAM_BATTERY:           return "MBC3 + RAM + BATTERY";              break;
    case CartridgeType::MBC4:                       return "MBC4";                              break;
    case CartridgeType::MBC4_RAM:                   return "MBC4 + RAM";                        break;
    case CartridgeType::MBC4_RAM_BATTERY:           return "MBC4 + RAM + BATTERY";              break;
    case CartridgeType::MBC5:                       return "MBC5";                              break;
    case CartridgeType::MBC5_RAM:                   return "MBC5 + RAM";                        break;
    case CartridgeType::MBC5_RAM_BATTERY:           return "MBC5 + RAM + BATTERY";              break;
    case CartridgeType::MBC5_RUMBLE:                return "MBC5 + RUMBLE";                     break;
    case CartridgeType::MBC5_RUMBLE_RAM:            return "MBC5 + RUMBLE + RAM";               break;
    case CartridgeType::MBC5_RUMBLE_RAM_BATTERY:    return "MBC5 + RUMBLE + RAM + BATTERY";     break;
    case CartridgeType::POCKET_CAMERA:              return "POCKET CAMERA";                     break;
    case CartridgeType::BANDAI_TAMA5:               return "BANDAI TAMA5";                      break;
    case CartridgeType::HuC3:                       return "HuC3";                              break;
    case CartridgeType::HuC1_RAM_BATTERY:           return "HuC1 + RAM + BATTERY";              break;
    default:
        return "Unknown Cartridge Type!";
        break;
    }
}

char const* to_string( ROMSize type )
{
    switch( type )
    {
    case ROMSize::ROM_32:   return "32KByte( 0 banks )";        break;
    case ROMSize::ROM_64:   return "64KByte( 4 banks )";        break;
    case ROMSize::ROM_128:  return "128KByte( 8 banks )";       break;
    case ROMSize::ROM_256:  return "256KByte( 16 banks )";      break;
    case ROMSize::ROM_512:  return "512KByte( 32 banks )";      break;
    case ROMSize::ROM_1024: return "1MByte( 64 banks (63) )";   break;
    case ROMSize::ROM_2048: return "2MByte( 128 banks (125) )"; break;
    case ROMSize::ROM_4096: return "4MByte( 256 banks )";       break;
    case ROMSize::ROM_1152: return "1.1MByte( 72 banks )";      break;
    case ROMSize::ROM_1280: return "1.2MByte( 80 banks )";      break;
    case ROMSize::ROM_1536: return "1.5MByte( 96 banks )";      break;
    default:
        return "ROM size not supported!";
        break;
    }
}

char const* to_string( RAMSize type )
{
    switch( type )
    {
    case RAMSize::NONE:     return "None";      break;
    case RAMSize::RAM_2:    return "2 KBytes";  break;
    case RAMSize::RAM_8:    return "8 Kbytes";  break;
    case RAMSize::RAM_32:   return "32 KBytes"; break;
    default:
        return "RAM size not supported!";
        break;
    }
}

char const* to_string( DestinationCode type )
{
    switch( type )
    {
    case DestinationCode::JAP:       return "Japan";    break;
    case DestinationCode::NO_JAP:    return "No Japan"; break;
    default:
        return "Unknown Destination Code!";
        break;
    }
}

char const* to_string( CGBSupport type )
{
    switch( type )
    {
    case CGBSupport::CGB_ONLY:                  return "Only for GB Color";                             break;
    case CGBSupport::NO_CGB_NO_PALETTE_INIT:    return "No GBC - No palette initialization";            break;
    case CGBSupport::SUPPORTS:                  return "Supports GB Color (Also works on other GBs)";   break;
    default:
        return "Unknown CGBSupport!";
        break;
    }
}
