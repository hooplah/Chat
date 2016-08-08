#ifndef PICTURESTATE_H
#define PICTURESTATE_H

#include "IState.h"

#include <SFML/Graphics.hpp>

class PictureState : public IState
{
    public:
        PictureState(StateMachine& machine, bool replace, std::string name);
        ~PictureState();

        void pause() {}
        void resume() {}

        void update();
        void draw(sf::RenderTarget& target);
        void handleEvents(sf::Event& event);

    private:
        sf::Image mImage;
        sf::Texture mTexture;
        sf::Sprite mSprite;
};

#endif // PICTURESTATE_H
