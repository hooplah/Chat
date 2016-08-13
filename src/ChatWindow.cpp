#include "ChatWindow.h"

#include <iostream>

ChatWindow::ChatWindow(const char* title, sf::TcpSocket& socket, Channel<MessageData>& msgChannel) :
    LogWindow(title),
    mSocket(socket),
    mChannel(msgChannel)
{
    bzero(mMessage, 256);
}

ChatWindow::~ChatWindow()
{
    //dtor
}

void ChatWindow::send(std::string msg)
{
    sf::Packet packet;
    packet << PacketID::TEXT << msg;
    mSocket.send(packet);
}

void ChatWindow::update()
{
    MessageData msg("", "");
    if (mChannel.receive(msg, false))
    {
        push(msg.name.append(": ").append(msg.msg).c_str());
        push("\n");
    }

    LogWindow::begin();

    ImGui::InputText("", mMessage, 256);
    ImGui::SameLine();
    if (ImGui::Button(mButtonName) || ImGui::IsKeyPressed(sf::Keyboard::Return))
    {
        send(std::string(mMessage));
        memset(mMessage, 0, sizeof mMessage);
    }
    LogWindow::update();

    LogWindow::end();
}
