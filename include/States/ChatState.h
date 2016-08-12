#ifndef CHATSTATE_H
#define CHATSTATE_H

#include "IState.h"

#include "Client.h"
#include "ChatWindow.h"
#include "OnlineUsersWindow.h"

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
        ChatWindow mGlobalChat;
        std::vector<ChatWindow> mPrivateChats;
        OnlineUsersWindow mUserList;
};

#endif // CHATSTATE_H
