#ifndef CHATSTATE_H
#define CHATSTATE_H

#include "IState.h"

#include "Client.h"
#include "LogWindow.h"

class ChatState : public IState
{
    public:
        ChatState(StateMachine& stateMachine, bool replace, Client& client);
        ~ChatState();

        void pause() {}
        void resume() {}

        void update();
        void draw(sf::RenderTarget& target);
        void handleEvents(sf::Event& event);

    private:
        Client& mClient;
        LogWindow mGlobalChat;
        std::vector<LogWindow> mPrivateChats;
        //LogWindow mUserList;
};

#endif // CHATSTATE_H
