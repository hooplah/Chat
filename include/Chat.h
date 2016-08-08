#ifndef CHAT_H
#define CHAT_H

#include <deque>
#include <mutex>
#include <tuple>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "Channel.h"
#include "Message.h"

class Chat
{
    public:
        Chat(sf::TcpSocket& socket, Channel<MessageData>& channel, std::string name);
        ~Chat();

        void handleEvents(sf::Event& event);
        void update();
        void draw(sf::RenderTarget& target);

        //static void listenForMessages(Channel<MessageData>* channel, std::vector<MessageData>* chatLog);

    private:
        std::size_t mMaxLines;
        sf::Font mFont;
        DrawableMessage mCurrentMessage; // current message user is typing
        std::deque<DrawableMessage> mOutputBuffer;
        std::vector<MessageData> mChatLog;

        std::thread mListener;
        sf::TcpSocket& mSocket;
        Channel<MessageData>& mChannel;
};

#endif // CHATG_H
