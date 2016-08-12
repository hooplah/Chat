#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include "LogWindow.h"

class ChatWindow : public LogWindow
{
    public:
        ChatWindow(const char* title, sf::TcpSocket& socket, Channel<MessageData>& msgChannel);
        ~ChatWindow();

        void push(const char* fmt, ...) IM_PRINTFARGS(2);
        void send(std::string msg);
        void update();

    private:
        char mMessage[256];
        sf::TcpSocket& mSocket;
        Channel<MessageData>& mMessageChannel;
};

#endif // CHATWINDOW_H
