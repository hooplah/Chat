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

        static void listenForPackets(sf::TcpSocket* socket, Channel<MessageData>* msgChannel,
                                     Channel<std::vector<std::string>>* usersChannel, std::atomic<bool>* connected);

        bool isConnected(){return mConnected;}
        sf::TcpSocket& getSocket(){return mSocket;}
        Channel<MessageData>& getMessageChannel(){return mMessageChannel;}
        Channel<std::vector<std::string>>& getUsersChannel(){return mUsersChannel;}

    private:
        std::atomic<bool> mConnected;
        sf::TcpSocket mSocket;
        Channel<MessageData> mMessageChannel;
        Channel<std::vector<std::string>> mUsersChannel; // for sending vector of online users
        std::thread mPacketListener;
};

#endif // CLIENT_H
