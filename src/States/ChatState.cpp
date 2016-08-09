#include "States/ChatState.h"

#include "States/PictureState.h"
#include "States/StateMachine.h"

ChatState::ChatState(StateMachine& stateMachine, bool replace, Client& client) : IState(stateMachine, replace),
    mClient(client),
    mChat(mClient.getSocket(), mClient.getChannel())
{
    //ctor
}

ChatState::~ChatState()
{
    //dtor
}

void ChatState::update()
{
    mChat.update();
}

void ChatState::draw(sf::RenderTarget& target)
{
    mChat.draw(target);
}

void ChatState::handleEvents(sf::Event& event)
{
    mChat.handleEvents(event);

    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right)
        {
            mNext = StateMachine::build<PictureState>(mMachine, false, std::ref(mClient));
        }
    }
}
