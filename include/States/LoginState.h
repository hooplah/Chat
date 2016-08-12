#ifndef LOGINSTATE_H
#define LOGINSTATE_H

#include "IState.h"

#include "Client.h"

class LoginState : public IState
{
    public:
        LoginState(StateMachine& stateMachine, bool replace, Client& client);
        ~LoginState();

        void pause() {}
        void resume() {}

        void update();
        void draw(sf::RenderTarget& target);
        void handleEvents(sf::Event& event);

    private:
        Client& mClient;
        char mName[256];
};

#endif // LOGINSTATE_H
