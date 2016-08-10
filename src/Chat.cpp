#include "Chat.h"

#include "imgui/imgui.h"

Chat::Chat(sf::TcpSocket& socket, Channel<MessageData>& channel) :
    mMaxLines(19),
    mSocket(socket),
    mChannel(channel)
{

}

Chat::~Chat()
{
    //dtor
}

void Chat::handleEvents(sf::Event& event)
{
}

void Chat::update()
{
    MessageData msg("", "");
    if (mChannel.receive(msg, false))
    {
        mChatLog.push_back(msg);
        push(msg.name.append(": ").append(msg.msg).c_str());
        push("\n");
    }
}

void Chat::draw(sf::RenderTarget& target)
{
}

void Chat::push(const char* fmt, ...)
{
    int old_size = mBuffer.size();
    va_list args;
    va_start(args, fmt);
    mBuffer.appendv(fmt, args);
    va_end(args);
    for (int new_size = mBuffer.size(); old_size < new_size; old_size++)
        if (mBuffer[old_size] == '\n')
            mLineOffsets.push_back(old_size);
    mScrollToBottom = true;
}
