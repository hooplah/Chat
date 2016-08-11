#ifndef CHAT_H
#define CHAT_H

#include <deque>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "Channel.h"
#include "Message.h"
#include "PacketID.h"
#include "imgui/imgui.h"

class Chat
{
    public:
        Chat(const char* title, sf::TcpSocket& socket, Channel<MessageData>& channel);
        ~Chat();

        void clear();
        void send(std::string msg);
        void push(const char* fmt, ...) IM_PRINTFARGS(2);
        void update();
        void handleEvents(sf::Event& event);

    private:
        const char* mTitle;
        char mMessage[255];
        ImGuiTextBuffer mBuffer;
        ImGuiTextFilter mFilter;
        ImVector<int> mLineOffsets; // Index to lines offset
        bool mScrollToBottom;

        sf::TcpSocket& mSocket;
        Channel<MessageData>& mChannel;
};

#endif // CHATG_H
