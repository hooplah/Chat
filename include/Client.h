#ifndef CLIENT_H
#define CLIENT_H

#include <atomic>
#include <mutex>
#include <thread>

#include <SFML/Network.hpp>

#include "Channel.h"
#include "Message.h"

class Client
{
    public:
        Client();
        ~Client();

        void disconnect();

        static void listenForPackets(sf::TcpSocket* socket, Channel<MessageData>* channel, std::atomic<bool>* connected);

        bool isConnected(){return mConnected;}
        sf::TcpSocket& getSocket(){return mSocket;}
        Channel<MessageData>& getChannel(){return mChannel;}

    private:
        std::atomic<bool> mConnected;
        sf::TcpSocket mSocket;
        Channel<MessageData> mChannel;
        std::thread mPacketListener;
};

#endif // CLIENT_H
