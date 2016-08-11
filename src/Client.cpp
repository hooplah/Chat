#include "Client.h"

#include "Constants.h"
#include "PacketID.h"

Client::Client() :
    mConnected(true), // assume we can connect to the server
    mPacketListener(listenForPackets, &mSocket, &mChannel, &mConnected)
{
    if (mSocket.connect(SERVER_IPADDRESS, PORT) == sf::Socket::Done)
        mConnected = true;
    else
        mConnected = false;
}

Client::~Client()
{
    disconnect();
    mPacketListener.join();
}

void Client::disconnect()
{
    sf::Packet packet;
    packet << PacketID::DISCONNECT;
    //mSocket.send(packet);

    mConnected = false;
    //mSocket.disconnect();
}

void Client::listenForPackets(sf::TcpSocket* socket, Channel<MessageData>* channel, std::atomic<bool>* connected)
{
    while (*connected)
    {
        sf::Packet packet;
        if (socket->receive(packet) == sf::Socket::Done)
        {
            PacketID type; // what type of packet
            packet >> type;

            switch (type)
            {
                case PacketID::TEXT:
                {
                    std::string name, senderMsg;
                    if (packet >> name >> senderMsg)
                    {
                        MessageData msg(name, senderMsg);
                        channel->send(msg);
                    }
                    break;
                }
                case PacketID::PICTURE:
                {
                    break;
                }
                case PacketID::REQUEST_USERS:
                {
                    sf::Uint8 clientSize;
                    std::vector<std::string> clients;
                    packet >> clientSize;
                    for (std::size_t i = 0; i < clientSize; i++)
                    {
                        std::string name;
                        packet >> name;
                        clients.push_back(name);
                    }
                    break;
                }
            }
        }
    }
}
