#ifndef LOGWINDOW_H
#define LOGWINDOW_H

#include <deque>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "Channel.h"
#include "Message.h"
#include "PacketID.h"
#include "imgui/imgui.h"

class LogWindow
{
    public:
        LogWindow(const char* title, sf::TcpSocket& socket, Channel<MessageData>& channel);
        ~LogWindow();

        void clear();
        void send(std::string msg);
        void push(const char* fmt, ...) IM_PRINTFARGS(2);
        void update();

        void setTitle(const char* title){mTitle=title;}
        void setButtonName(const char* name){mButtonName=name;}

    private:
        const char* mTitle;
        const char* mButtonName;
        char mMessage[255];
        ImGuiTextBuffer mBuffer;
        ImGuiTextFilter mFilter;
        ImVector<int> mLineOffsets; // Index to lines offset
        bool mScrollToBottom;

        sf::TcpSocket& mSocket;
        Channel<MessageData>& mMessageChannel;
};

#endif // LOGWINDOW_H
