#include "Client.h"

#include <iostream>

#include "Constants.h"
#include "PacketID.h"

Client::Client() :
    mPacketListener(listenForPackets, &mSocket, &mChannel)
{
    if (mSocket.connect(SERVER_IPADDRESS, PORT) == sf::Socket::Done)
        std::cout << "Connected to " << mSocket.getRemoteAddress() << std::endl;
}

Client::~Client()
{
    mPacketListener.join();
}

void Client::update()
{
}

void Client::listenForPackets(sf::TcpSocket* socket, Channel<MessageData>* channel)
{
    while (true)
    {
        sf::Packet packet;
        if (socket->receive(packet) == sf::Socket::Done)
        {
            sf::Uint8 type; // what type of packet
            std::string name, senderMsg;
            if (packet >> type >> name >> senderMsg)
            {
                MessageData msg(name, senderMsg);
                channel->send(msg);
            }
        }
    }
}
