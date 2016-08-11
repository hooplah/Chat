#include "LogWindow.h"

#include "imgui/imgui.h"

#include <iostream>

LogWindow::LogWindow(const char* title, sf::TcpSocket& socket, Channel<MessageData>& channel) :
    mTitle(title),
    mButtonName("Send"),
    mSocket(socket),
    mMessageChannel(channel)
{
    //ctor
}

LogWindow::~LogWindow()
{
    //dtor
}

void LogWindow::clear()
{
    mBuffer.clear();
    mLineOffsets.clear();
}

void LogWindow::send(std::string msg)
{
    sf::Packet packet;
    packet << PacketID::TEXT << msg;
    mSocket.send(packet);
}

void LogWindow::push(const char* fmt, ...)
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

void LogWindow::update()
{
    MessageData msg("", "");
    if (mMessageChannel.receive(msg, false))
    {
        push(msg.name.append(": ").append(msg.msg).c_str());
        push("\n");
    }

    ImGui::Begin(mTitle);

    ImGui::InputText("", mMessage, 255);

    ImGui::SameLine();

    if (ImGui::Button(mButtonName) || ImGui::IsKeyPressed(sf::Keyboard::Return))
    {
        send(std::string(mMessage));
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
