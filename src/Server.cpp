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
        sf::Packet packet = mPacketQueue.front();
        mPacketQueue.pop();
        PacketID type;
        std::string name, msg;
        packet >> type >> name >> msg;
        std::cout << name << ": " << msg << std::endl;

        for (auto& client : mClients)
        {
            client->socket.send(packet);
        }
    }
    mPacketMutex.unlock();
}

void Server::listenForPackets(sf::TcpListener* listener, sf::Socket* socket, sf::SocketSelector* selector,
                              std::vector<std::unique_ptr<ClientHandle>>* clients, std::queue<sf::Packet>* packetQueue,
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
                    std::cout << "New client connected: " << client->socket.getRemoteAddress() << std::endl;

                    sf::Packet packet;
                    if (client->socket.receive(packet) == sf::Socket::Done)
                    {
                        packet >> client->name;
                    }

                    selector->add(client->socket);
                    clients->push_back(std::move(client));
                }

                clientMutex->unlock();
            }
            clientMutex->lock();
            for (auto it = clients->begin(); it != clients->end(); ++it)
            {
                ClientHandle& client = **it;
                sf::Packet packet;

                if (selector->isReady(client.socket))
                {
                    if (client.socket.receive(packet) == sf::Socket::Done)
                    {
                        packetQueue->push(packet);
                    }
                }
            }
            clientMutex->unlock();
        }
    }
}
