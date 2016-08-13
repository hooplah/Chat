#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include "LogWindow.h"

class ChatWindow : public LogWindow
{
    public:
        ChatWindow(const char* title, sf::TcpSocket& socket, Channel<MessageData>& msgChannel);
        ~ChatWindow();

        void send(std::string msg);
        void update();

    private:
        char mMessage[256];
        sf::TcpSocket& mSocket;
        Channel<MessageData>& mChannel;
};

#endif // CHATWINDOW_H
