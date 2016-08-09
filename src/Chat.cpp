#include "Chat.h"

#include "PacketID.h"

Chat::Chat(sf::TcpSocket& socket, Channel<MessageData>& channel) :
    mMaxLines(19),
    mCurrentMessage(MessageData("", ""), mFont),
    mSocket(socket),
    mChannel(channel)
{
    mFont.loadFromFile("assets/arial.ttf");

    mCurrentMessage.setPosition(sf::Vector2f(10.f, 570.f));

    for (unsigned int i = 0; i < mMaxLines; i++)
        mChatLog.push_back(MessageData("", ""));
}

Chat::~Chat()
{
    //dtor
}

void Chat::handleEvents(sf::Event& event)
{
    // typing
    if (event.type == sf::Event::TextEntered)
    {
        if (event.text.unicode < 128 && event.text.unicode != 8 && event.text.unicode != 13 &&
            event.text.unicode != 27)
        {
            mCurrentMessage.data.msg += static_cast<char>(event.text.unicode);
        }
        else if (event.text.unicode == 8) // backspace
        {
            if (mCurrentMessage.data.msg.size() >= 1)
            {
                mCurrentMessage.data.msg.pop_back(); // take off last char
            }
        }
        else if (event.text.unicode == 13) // enter - send message
        {
            sf::Packet packet;
            packet << PacketID::TEXT << mCurrentMessage.data.msg;
            mSocket.send(packet);

            mCurrentMessage.data.msg = "";
        }

        mCurrentMessage.sync();
    }
}

void Chat::update()
{
    MessageData msg("", "");
    if (mChannel.receive(msg, false))
    {
        mChatLog.push_back(msg);
    }

    for (auto data : mChatLog)
    {
        mOutputBuffer.push_back(DrawableMessage(data, mFont));

        if (mOutputBuffer.size() > mMaxLines)
            mOutputBuffer.pop_front();
    }
}

void Chat::draw(sf::RenderTarget& target)
{
    target.draw(mCurrentMessage.text);

    for (std::size_t i = 0; i < mOutputBuffer.size(); i++)
    {
        mOutputBuffer[i].setPosition(sf::Vector2f(10.f, i*30.f));
        target.draw(mOutputBuffer[i].text);
    }
}
