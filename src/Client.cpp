#include "Client.h"

#include <SFML/Graphics.hpp>

#include "Constants.h"
#include "PacketID.h"

Client::Client() :
    mConnected(true), // assume we can connect to the server
    mPacketListener(listenForPackets, &mSocket, &mGlobalChannel, &mPictureChannel, &mUsersChannel, &mConnected)
{
    if (mSocket.connect(SERVER_IPADDRESS, PORT) == sf::Socket::Done)
        mConnected = true;
    else
        mConnected = false;
}

Client::~Client()
{
    mPacketListener.join();
}

void Client::disconnect()
{
    sf::Packet packet;
    packet << PacketID::DISCONNECT;
    mSocket.send(packet);

    //mSocket.disconnect();
    mConnected = false;
}

void Client::listenForPackets(sf::TcpSocket* socket, Channel<MessageData>* globalChannel, Channel<sf::Image>* picChannel,
                              Channel<std::vector<std::string>>* usersChannel, std::atomic<bool>* connected)
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
                        globalChannel->send(msg);
                    }
                    break;
                }
                case PacketID::PICTURE:
                {
                    sf::Image image;
                    sf::Uint32 size;
                    sf::Vector2u picSize;
                    std::size_t received;
                    const sf::Uint8* pixelPtr;

                    packet >> size;
                    packet >> picSize.x >> picSize.y;
                    pixelPtr = static_cast<const sf::Uint8*>(packet.getData());
                    image.create(picSize.x, picSize.y, pixelPtr);
                    picChannel->send(image);
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
                    usersChannel->send(clients);
                    break;
                }
            }
        }
    }
}
