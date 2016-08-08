#ifndef PACKETID_H_INCLUDED
#define PACKETID_H_INCLUDED

#include <SFML/Network/Packet.hpp>

enum class PacketID: sf::Uint8
{
    TEXT,
    PICTURE,
};

sf::Packet& operator <<(sf::Packet& packet, const PacketID& id);
sf::Packet& operator >>(sf::Packet& packet, PacketID& id);

#endif // PACKETID_H_INCLUDED
