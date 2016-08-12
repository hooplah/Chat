#ifndef LOGWINDOW_H
#define LOGWINDOW_H

#include <deque>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "Channel.h"
#include "Message.h"
#include "PacketID.h"
#include "imgui/imgui.h"

class LogWindow
{
    public:
        LogWindow(const char* title);
        ~LogWindow();

        void begin();
        void end();
        void clear();
        virtual void push(const char* fmt, ...) IM_PRINTFARGS(2);
        virtual void update();

        void setTitle(const char* title){mTitle=title;}
        void setButtonName(const char* name){mButtonName=name;}

    protected:
        const char* mTitle;
        const char* mButtonName;
        ImGuiTextBuffer mBuffer;
        ImGuiTextFilter mFilter;
        ImVector<int> mLineOffsets; // Index to lines offset
        bool mScrollToBottom;
};

#endif // LOGWINDOW_H
