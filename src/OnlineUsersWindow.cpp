#include "OnlineUsersWindow.h"

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
    //LogWindow::push(fmt);
    ImGui::Button(fmt, ImGui::CalcTextSize(fmt));
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
            mLines.push_back(client);
            push(client.c_str());
        }
    }

    LogWindow::update();

    LogWindow::end();
}
