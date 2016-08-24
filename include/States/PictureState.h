#ifndef PICTURESTATE_H
#define PICTURESTATE_H

#include "IState.h"

#include <SFML/Graphics.hpp>

#include "Client.h"

class PictureState : public IState
{
    public:
        PictureState(StateMachine& stateMachine, bool replace, Client& client);
        ~PictureState();

        void pause() {}
        void resume() {}

        void update();
        void draw(sf::RenderTarget& target);
        void handleEvents(sf::Event& event);

    private:
        Client& mClient;

        char mPath[256]; // file name
        sf::Image mImage;
        sf::Texture mTexture;
        sf::Sprite mSprite;
};

#endif // PICTURESTATE_H
