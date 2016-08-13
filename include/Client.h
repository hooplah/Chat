#ifndef CLIENT_H
#define CLIENT_H

#include <atomic>
#include <mutex>
#include <thread>

#include <SFML/Network.hpp>
#include <SFML/Graphics/Image.hpp>

#include "Channel.h"
#include "Message.h"

class Client
{
    public:
        Client();
        ~Client();

        void disconnect();

        static void listenForPackets(sf::TcpSocket* socket, Channel<MessageData>* globalChannel, Channel<sf::Image>* picChannel,
                                     Channel<std::vector<std::string>>* usersChannel, std::atomic<bool>* connected);

        bool isConnected(){return mConnected;}
        sf::TcpSocket& getSocket(){return mSocket;}
        Channel<MessageData>& getGlobalChannel(){return mGlobalChannel;}
        Channel<std::vector<std::string>>& getUsersChannel(){return mUsersChannel;}
        Channel<sf::Image>& getPictureChannel(){return mPictureChannel;}

    private:
        std::atomic<bool> mConnected;
        sf::TcpSocket mSocket;
        Channel<MessageData> mGlobalChannel;
        Channel<std::vector<std::string>> mUsersChannel; // for sending names of online users
        Channel<sf::Image> mPictureChannel;
        std::thread mPacketListener;
};

#endif // CLIENT_H
