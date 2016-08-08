#include "ChatState.h"

#include "PictureState.h"
#include "StateMachine.h"

ChatState::ChatState(StateMachine& machine, bool replace, std::string name) : IState(machine, replace),
    mChat(mClient.getSocket(), mClient.getChannel(), name)
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
            mNext = StateMachine::build<PictureState>(mMachine, false, "lucas");
        }
    }
}
