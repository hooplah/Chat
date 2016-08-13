#ifndef SERVER_H
#define SERVER_H

#include <map>
#include <atomic>
#include <queue>
#include <mutex>
#include <vector>
#include <memory>
#include <thread>

#include <SFML/Network.hpp>

#include "Message.h"
#include "Channel.h"

struct ClientHandle
{
    ClientHandle() {}

    sf::Uint8 id;
    std::string name;
    sf::TcpSocket socket;
};

class Server
{
    public:
        Server();
        ~Server();

        void update();

    private:
        static void listenForPackets(sf::TcpListener* listener, sf::Socket* socket, sf::SocketSelector* selector,
                                     std::map<ClientID, std::unique_ptr<ClientHandle>>* clients,
                                     std::queue<std::tuple<ClientID, sf::Packet>>* packetQueue,
                                     std::mutex* packetMutex, std::mutex* clientMutex, std::atomic<bool>* runThread);

        // helper functions
        ClientID findClientByName(std::string name);

        sf::TcpListener mListener;
        sf::TcpSocket mSocket;
        sf::SocketSelector mSelector;
        std::map<ClientID, std::unique_ptr<ClientHandle>> mClients;
        std::vector<ChatData> mChats;
        std::queue<std::tuple<ClientID, sf::Packet>> mPacketQueue;
        std::atomic<bool> mRunThread;

        std::thread mPacketListener; // constantly listens for packets
        std::mutex mPacketMutex;
        std::mutex mClientMutex;
};

#endif // SERVER_H
