#ifndef ONLINEUSERSWINDOW_H
#define ONLINEUSERSWINDOW_H

#include "LogWindow.h"

#include <tuple>

class OnlineUsersWindow : public LogWindow
{
    public:
        OnlineUsersWindow(Channel<std::vector<std::string>>& channel);
        ~OnlineUsersWindow();

        void update();

        std::vector<std::tuple<bool, const char*>>& getButtons(){return mButtons;}

    private:
        Channel<std::vector<std::string>>& mChannel;
        std::vector<std::tuple<bool, const char*>> mButtons;
};

#endif // ONLINEUSERSWINDOW_H
