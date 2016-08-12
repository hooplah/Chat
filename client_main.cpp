#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

#include <SFML/Graphics.hpp>

#include "States/LoginState.h"
#include "Client.h"
#include "Constants.h"
#include "States/StateMachine.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Chat");

    ImGui::SFML::Init(window);

    ImGuiStyle* style = &ImGui::GetStyle();
    style->WindowPadding            = ImVec2(15, 15);
    style->WindowRounding           = 5.0f;
    style->FramePadding             = ImVec2(5, 5);
    style->FrameRounding            = 4.0f;
    style->ItemSpacing              = ImVec2(12, 8);
    style->ItemInnerSpacing         = ImVec2(8, 6);
    style->IndentSpacing            = 25.0f;
    style->ScrollbarSize            = 15.0f;
    style->ScrollbarRounding        = 9.0f;
    style->GrabMinSize              = 5.0f;
    style->GrabRounding             = 3.0f;

    style->Colors[ImGuiCol_Text]                  = ImVec4(0.40f, 0.39f, 0.38f, 1.00f);
    style->Colors[ImGuiCol_TextDisabled]          = ImVec4(0.40f, 0.39f, 0.38f, 0.77f);
    style->Colors[ImGuiCol_WindowBg]              = ImVec4(0.92f, 0.91f, 0.88f, 0.70f);
    style->Colors[ImGuiCol_ChildWindowBg]         = ImVec4(1.00f, 0.98f, 0.95f, 0.58f);
    style->Colors[ImGuiCol_PopupBg]               = ImVec4(0.92f, 0.91f, 0.88f, 0.92f);
    style->Colors[ImGuiCol_Border]                = ImVec4(0.84f, 0.83f, 0.80f, 0.65f);
    style->Colors[ImGuiCol_BorderShadow]          = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
    style->Colors[ImGuiCol_FrameBg]               = ImVec4(1.00f, 0.98f, 0.95f, 1.00f);
    style->Colors[ImGuiCol_FrameBgHovered]        = ImVec4(0.99f, 1.00f, 0.40f, 0.78f);
    style->Colors[ImGuiCol_FrameBgActive]         = ImVec4(0.26f, 1.00f, 0.00f, 1.00f);
    style->Colors[ImGuiCol_TitleBg]               = ImVec4(1.00f, 0.98f, 0.95f, 1.00f);
    style->Colors[ImGuiCol_TitleBgCollapsed]      = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
    style->Colors[ImGuiCol_TitleBgActive]         = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
    style->Colors[ImGuiCol_MenuBarBg]             = ImVec4(1.00f, 0.98f, 0.95f, 0.47f);
    style->Colors[ImGuiCol_ScrollbarBg]           = ImVec4(1.00f, 0.98f, 0.95f, 1.00f);
    style->Colors[ImGuiCol_ScrollbarGrab]         = ImVec4(0.00f, 0.00f, 0.00f, 0.21f);
    style->Colors[ImGuiCol_ScrollbarGrabHovered]  = ImVec4(0.90f, 0.91f, 0.00f, 0.78f);
    style->Colors[ImGuiCol_ScrollbarGrabActive]   = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
    style->Colors[ImGuiCol_ComboBg]               = ImVec4(1.00f, 0.98f, 0.95f, 1.00f);
    style->Colors[ImGuiCol_CheckMark]             = ImVec4(0.25f, 1.00f, 0.00f, 0.80f);
    style->Colors[ImGuiCol_SliderGrab]            = ImVec4(0.00f, 0.00f, 0.00f, 0.14f);
    style->Colors[ImGuiCol_SliderGrabActive]      = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
    style->Colors[ImGuiCol_Button]                = ImVec4(0.00f, 0.00f, 0.00f, 0.14f);
    style->Colors[ImGuiCol_ButtonHovered]         = ImVec4(0.99f, 1.00f, 0.22f, 0.86f);
    style->Colors[ImGuiCol_ButtonActive]          = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
    style->Colors[ImGuiCol_Header]                = ImVec4(0.25f, 1.00f, 0.00f, 0.76f);
    style->Colors[ImGuiCol_HeaderHovered]         = ImVec4(0.25f, 1.00f, 0.00f, 0.86f);
    style->Colors[ImGuiCol_HeaderActive]          = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
    style->Colors[ImGuiCol_Column]                = ImVec4(0.00f, 0.00f, 0.00f, 0.32f);
    style->Colors[ImGuiCol_ColumnHovered]         = ImVec4(0.25f, 1.00f, 0.00f, 0.78f);
    style->Colors[ImGuiCol_ColumnActive]          = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
    style->Colors[ImGuiCol_ResizeGrip]            = ImVec4(0.00f, 0.00f, 0.00f, 0.04f);
    style->Colors[ImGuiCol_ResizeGripHovered]     = ImVec4(0.25f, 1.00f, 0.00f, 0.78f);
    style->Colors[ImGuiCol_ResizeGripActive]      = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
    style->Colors[ImGuiCol_CloseButton]           = ImVec4(0.40f, 0.39f, 0.38f, 0.16f);
    style->Colors[ImGuiCol_CloseButtonHovered]    = ImVec4(0.40f, 0.39f, 0.38f, 0.39f);
    style->Colors[ImGuiCol_CloseButtonActive]     = ImVec4(0.40f, 0.39f, 0.38f, 1.00f);
    style->Colors[ImGuiCol_TextSelectedBg]        = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
    style->Colors[ImGuiCol_ModalWindowDarkening]  = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);

    Client client;
    StateMachine states;
    states.run(StateMachine::build<LoginState>(states, true, std::ref(client)));

    sf::Clock dt;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed)
            {
                client.disconnect();
                window.close();
            }

            states.handleEvents(event);
        }

        ImGui::SFML::Update(dt.restart());

        states.nextState();
        states.update();

        window.clear(sf::Color::White);
        states.draw(window);
        ImGui::Render();
        window.display();
    }

    ImGui::SFML::Shutdown();

    return 0;
}
