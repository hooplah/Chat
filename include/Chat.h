#ifndef CHAT_H
#define CHAT_H

#include <deque>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "Channel.h"
#include "Message.h"

class Chat
{
    public:
        Chat(sf::TcpSocket& socket, Channel<MessageData>& channel);
        ~Chat();

        void handleEvents(sf::Event& event);
        void update();
        void draw(sf::RenderTarget& target);

    private:
        std::size_t mMaxLines;
        sf::Font mFont;
        DrawableMessage mCurrentMessage; // current message user is typing
        std::deque<DrawableMessage> mOutputBuffer;
        std::vector<MessageData> mChatLog;

        sf::TcpSocket& mSocket;
        Channel<MessageData>& mChannel;
};

#endif // CHATG_H
