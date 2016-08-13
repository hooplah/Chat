#include "OnlineUsersWindow.h"

#include <iostream>

OnlineUsersWindow::OnlineUsersWindow(Channel<std::vector<std::string>>& channel) : LogWindow("Online Users"),
    mChannel(channel)
{
    //ctor
}

OnlineUsersWindow::~OnlineUsersWindow()
{
    //dtor
}

void OnlineUsersWindow::update()
{
    LogWindow::begin();

    std::vector<std::string> clients;
    if (mChannel.receive(clients, false))
    {
        clear();
        mButtons.clear();
        for (auto& client : clients)
        {
            mButtons.push_back(std::make_pair(ImGui::Button(client.c_str()), client.c_str()));
        }
    }

    if (mScrollToBottom)
        ImGui::SetScrollHere(1.0f);
    mScrollToBottom = false;

    LogWindow::end();
}
