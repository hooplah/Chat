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

void OnlineUsersWindow::push(const char* fmt, ...)
{
}

void OnlineUsersWindow::update()
{
    LogWindow::begin();

    std::vector<std::string> clients;
    if (mChannel.receive(clients, false))
    {
        clear();
        for (auto& client : clients)
        {
            bool button = ImGui::Button(client.c_str(), ImGui::CalcTextSize(client.c_str()));
            mButtons.push_back(std::make_pair(button, client.c_str()));
        }
    }

    if (mScrollToBottom)
        ImGui::SetScrollHere(1.0f);
    mScrollToBottom = false;

    LogWindow::end();
}
