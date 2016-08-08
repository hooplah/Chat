#ifndef SERVER_H
#define SERVER_H

#include <atomic>
#include <queue>
#include <mutex>
#include <vector>
#include <memory>
#include <thread>

#include <SFML/Network.hpp>

struct ClientHandle
{
    ClientHandle() {}

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
                                     std::vector<std::unique_ptr<ClientHandle>>* clients, std::queue<sf::Packet>* packetQueue,
                                     std::mutex* packetMutex, std::mutex* clientMutex, std::atomic<bool>* runThread);

        sf::TcpListener mListener;
        sf::TcpSocket mSocket;
        sf::SocketSelector mSelector;
        std::vector<std::unique_ptr<ClientHandle>> mClients;
        std::queue<sf::Packet> mPacketQueue;
        std::atomic<bool> mRunThread;

        std::thread mPacketListener; // constantly listens for packets
        std::mutex mPacketMutex;
        std::mutex mClientMutex;
};

#endif // SERVER_H
