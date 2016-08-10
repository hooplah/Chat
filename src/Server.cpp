#include "Server.h"

#include <iostream>

#include "Constants.h"
#include "PacketID.h"

Server::Server() :
    mRunThread(true),
    mPacketListener(listenForPackets, &mListener, &mSocket, &mSelector,
                    &mClients, &mPacketQueue, &mPacketMutex, &mClientMutex, &mRunThread)
{
    mListener.listen(PORT);
    mSelector.add(mListener);
}

Server::~Server()
{
    mRunThread = false;
    mPacketListener.join();
}

void Server::update()
{
    mPacketMutex.lock();
    while (!mPacketQueue.empty())
    {
        std::tuple<ClientID, sf::Packet> packet_tuple = mPacketQueue.front();
        mPacketQueue.pop();
        ClientID clientID = std::get<0>(packet_tuple);
        sf::Packet packet = std::get<1>(packet_tuple);
        PacketID type;
        packet >> type;
        switch (type)
        {
            case PacketID::TEXT:
            {
                std::string name, msg;
                name = (*mClients[clientID]).name;
                packet >> msg;
                std::cout << name << ": " << msg << std::endl;

                for (auto& client : mClients)
                {
                    // construct a new packet and send it to every client
                    sf::Packet out;
                    out << PacketID::TEXT << name << msg;
                    client.second->socket.send(out);
                }

                break;
            }
            case PacketID::PICTURE:
            {
                break;
            }
            case PacketID::DISCONNECT:
            {
                //std::cout << (*mClients[clientID]).name << " disconnected" << std::endl;
                //mClients.erase(clientID);
                break;
            }
        }
    }
    mPacketMutex.unlock();
}

void Server::listenForPackets(sf::TcpListener* listener, sf::Socket* socket, sf::SocketSelector* selector,
                              std::map<ClientID, std::unique_ptr<ClientHandle>>* clients,
                              std::queue<std::tuple<ClientID, sf::Packet>>* packetQueue,
                              std::mutex* packetMutex, std::mutex* clientMutex, std::atomic<bool>* runThread)
{
    while (*runThread)
    {
        if (selector->wait(sf::seconds(0.5)))
        {
            if (selector->isReady(*listener))
            {
                clientMutex->lock();

                std::unique_ptr<ClientHandle> client = std::make_unique<ClientHandle>();
                if (listener->accept(client->socket) == sf::Socket::Done)
                {
                    sf::Packet packet;
                    if (client->socket.receive(packet) == sf::Socket::Done)
                    {
                        packet >> client->name;
                        std::cout << client->name << " connected from " << client->socket.getRemoteAddress() << std::endl;
                    }

                    selector->add(client->socket);
                    clients->emplace(clients->size(), std::move(client));
                }

                clientMutex->unlock();
            }
            // if a packet is received from any client
            clientMutex->lock();
            for (auto& clientMap : *clients)
            {
                ClientHandle& client = *clientMap.second;
                sf::Packet packet;

                if (selector->isReady(client.socket))
                {
                    if (client.socket.receive(packet) == sf::Socket::Done)
                    {
                        packetQueue->push(std::tuple<ClientID, sf::Packet>(clientMap.first, packet));
                    }
                }
            }
            clientMutex->unlock();
        }
    }
}
