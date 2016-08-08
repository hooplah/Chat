#include "PacketID.h"

sf::Packet& operator <<(sf::Packet& packet, const PacketID& id)
{
    return packet << (std::underlying_type<PacketID>::type)id;
}

sf::Packet& operator >>(sf::Packet& packet, PacketID& id)
{
    return packet >> (std::underlying_type<PacketID>::type&)id;
}
