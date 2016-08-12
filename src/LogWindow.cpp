#include "LogWindow.h"

#include "imgui/imgui.h"

LogWindow::LogWindow(const char* title) :
    mTitle(title),
    mButtonName("Send")
{
    //ctor
}

LogWindow::~LogWindow()
{
    //dtor
}

void LogWindow::begin()
{
    ImGui::Begin(mTitle);
    ImGui::BeginChild("scrolling");
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0,1));
}

void LogWindow::end()
{
    ImGui::PopStyleVar();
    ImGui::EndChild();
    ImGui::End();
}

void LogWindow::clear()
{
    mBuffer.clear();
    mLineOffsets.clear();
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
}
