#ifndef CHAT_H
#define CHAT_H

#include <deque>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "Channel.h"
#include "Message.h"
#include "imgui/imgui.h"

struct ChatWindow
{
    ChatWindow(const char* title) : mTitle(title) {}

    const char* mTitle;
    char mMessage[255];
    ImGuiTextBuffer mBuffer;
    ImGuiTextFilter mFilter;
    ImVector<int> mLineOffsets; // Index to lines offset
    bool mScrollToBottom;

    void clear()
    {
        mBuffer.clear();
        mLineOffsets.clear();
    }

    void addLog(const char* fmt, ...) IM_PRINTFARGS(2)
    {
        int old_size = mBuffer.size();
        va_list args;
        va_start(args, fmt);
        mBuffer.appendv(fmt, args);
        va_end(args);
        for (int new_size = mBuffer.size(); old_size < new_size; old_size++)
            if (mBuffer[old_size] == '\n')
                mLineOffsets.push_back(old_size);
        mScrollToBottom = true;
    }

    void update(sf::TcpSocket& socket)
    {
        ImGui::SetNextWindowSize(ImVec2(500,400), ImGuiSetCond_FirstUseEver);

        ImGui::Begin(mTitle);

        ImGui::InputText("", mMessage, 255);

        ImGui::SameLine();

        if (ImGui::Button("Send"))
        {
            sf::Packet packet;
            packet << PacketID::TEXT << std::string(mMessage);
            socket.send(packet);

            memset(mMessage, 0, sizeof mMessage);
        }

        ImGui::Separator();

        ImGui::BeginChild("scrolling");
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0,1));

        if (mFilter.IsActive())
        {
            const char* buf_begin = mBuffer.begin();
            const char* line = buf_begin;
            for (int line_no = 0; line != NULL; line_no++)
            {
                const char* line_end = (line_no < mLineOffsets.Size) ? buf_begin + mLineOffsets[line_no] : NULL;
                if (mFilter.PassFilter(line, line_end))
                    ImGui::TextUnformatted(line, line_end);
                line = line_end && line_end[1] ? line_end + 1 : NULL;
            }
        }
        else
        {
            ImGui::TextUnformatted(mBuffer.begin());
        }

        if (mScrollToBottom)
            ImGui::SetScrollHere(1.0f);
        mScrollToBottom = false;
        ImGui::PopStyleVar();
        ImGui::EndChild();
        ImGui::End();
    }
};

class Chat
{
    public:
        Chat(sf::TcpSocket& socket, Channel<MessageData>& channel);
        ~Chat();

        void handleEvents(sf::Event& event);
        void update();
        void draw(sf::RenderTarget& target);

        void push(const char* fmt, ...) IM_PRINTFARGS(2);

    private:
        std::size_t mMaxLines;
        std::vector<MessageData> mChatLog;

        ChatWindow mGlobalChat;

        sf::TcpSocket& mSocket;
        Channel<MessageData>& mChannel;
};

#endif // CHATG_H
