#include "PictureState.h"

#include "ChatState.h"
#include "StateMachine.h"

PictureState::PictureState(StateMachine& machine, bool replace, std::string name) : IState(machine, replace)
{
    mTexture.loadFromFile("pic.png");
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
            mNext = StateMachine::build<ChatState>(mMachine, true, "lucas");
        }
    }
}
