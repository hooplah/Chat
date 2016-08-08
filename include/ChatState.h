#ifndef CHATSTATE_H
#define CHATSTATE_H

#include "IState.h"

#include "Client.h"
#include "Chat.h"

class ChatState : public IState
{
    public:
        ChatState(StateMachine& stateMachine, bool replace, std::string name);
        ~ChatState();

        void pause() {}
        void resume() {}

        void update();
        void draw(sf::RenderTarget& target);
        void handleEvents(sf::Event& event);

    private:
        Client mClient;
        Chat mChat;
};

#endif // CHATSTATE_H
