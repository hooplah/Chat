#include "States/PictureState.h"

#include "States/ChatState.h"
#include "States/StateMachine.h"

PictureState::PictureState(StateMachine& stateMachine, bool replace, Client& client) : IState(stateMachine, replace),
    mClient(client)
{
    mTexture.loadFromFile("assets/pic.png");
    //mTexture.update(mImage);
    mSprite = sf::Sprite(mTexture);
}

PictureState::~PictureState()
{
    //dtor
}

void PictureState::update()
{
}

void PictureState::draw(sf::RenderTarget& target)
{
    target.draw(mSprite);
}

void PictureState::handleEvents(sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right)
        {
            mNext = StateMachine::build<ChatState>(mMachine, false, std::ref(mClient));
        }
    }
}
