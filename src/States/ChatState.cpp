#include "States/ChatState.h"

#include "States/PictureState.h"
#include "States/StateMachine.h"

ChatState::ChatState(StateMachine& stateMachine, bool replace, Client& client) : IState(stateMachine, replace),
    mClient(client),
    mGlobalChat("Global Chat", mClient.getSocket(), mClient.getChannel())
    //mUserList("Online Users", mClient.getSocket(), mClient.getChannel())
{
    //mUserList.setButtonName("Search");
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

    //mUserList.update();

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
            //mNext = StateMachine::build<PictureState>(mMachine, false, std::ref(mClient));
        }
    }
}
