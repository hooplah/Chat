#include "States/ChatState.h"

#include "States/PictureState.h"
#include "States/StateMachine.h"

#include <iostream>

ChatState::ChatState(StateMachine& stateMachine, bool replace, Client& client) : IState(stateMachine, replace),
    mClient(client),
    mGlobalChat("Global Chat", mClient.getSocket(), mClient.getGlobalChannel()),
    mUserList(mClient.getUsersChannel())
{
    mUserList.setButtonName("Search");
}

ChatState::~ChatState()
{
    //dtor
}

void ChatState::update()
{
    mGlobalChat.update();

    for (auto& chat : mPrivateChats)
        chat.update();

    for (auto& button : mUserList.getButtons())
    {
        bool pressed = std::get<0>(button);
        const char* name = std::get<1>(button);
        if (pressed)
        {
            //mPrivateChats.push_back(ChatWindow(name, mClient.getSocket(), mClient.getMessageChannel(), name));
        }
    }

    mUserList.update();

    sf::Packet packet;
    packet << PacketID::REQUEST_USERS;
    mClient.getSocket().send(packet);
}

void ChatState::draw(sf::RenderTarget& target)
{
}

void ChatState::handleEvents(sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right)
        {
            mMachine.run(StateMachine::build<PictureState>(mMachine, false, std::ref(mClient)));
        }
    }
}
