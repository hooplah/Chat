#include "States/LoginState.h"

#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

#include "Constants.h"
#include "States/ChatState.h"
#include "States/StateMachine.h"

LoginState::LoginState(StateMachine& stateMachine, bool replace, Client& client) : IState(stateMachine, replace),
    mClient(client)
{
    //ctor
}

LoginState::~LoginState()
{
    //dtor
}

void LoginState::update()
{
    ImGui::Begin("Login");

    ImGui::InputText("", mName, 255);
    if (ImGui::IsItemHovered())
    {
        ImGui::SetTooltip("Username");
        ImGui::BeginTooltip();
        ImGui::EndTooltip();
    }

    if (ImGui::Button("Login", ImVec2(64.f, 32.f)))
    {
        if (mClient.isConnected())
        {
            sf::Packet packet;
            packet << std::string(mName);
            mClient.getSocket().send(packet);

            mNext = StateMachine::build<ChatState>(mMachine, true, std::ref(mClient));
        }
    }

    ImGui::End();
}

void LoginState::draw(sf::RenderTarget& target)
{
}

void LoginState::handleEvents(sf::Event& event)
{
}
