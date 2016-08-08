#ifndef CLIENT_H
#define CLIENT_H

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

        void update();

        static void listenForPackets(sf::TcpSocket* socket, Channel<MessageData>* channel);

        sf::TcpSocket& getSocket(){return mSocket;}
        Channel<MessageData>& getChannel(){return mChannel;}

    private:
        sf::TcpSocket mSocket;
        Channel<MessageData> mChannel;
        std::thread mPacketListener;
};

#endif // CLIENT_H
