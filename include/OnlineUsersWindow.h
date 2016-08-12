#ifndef ONLINEUSERSWINDOW_H
#define ONLINEUSERSWINDOW_H

#include "LogWindow.h"


class OnlineUsersWindow : public LogWindow
{
    public:
        OnlineUsersWindow(Channel<std::vector<std::string>>& channel);
        ~OnlineUsersWindow();

        void push(const char* fmt, ...) IM_PRINTFARGS(2);
        void update();

    private:
        Channel<std::vector<std::string>>& mChannel;
        std::vector<std::string> mLines;
};

#endif // ONLINEUSERSWINDOW_H
