#include "States/LoginState.h"

#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

#include "Constants.h"
#include "States/ChatState.h"
#include "States/StateMachine.h"

#include <iostream>

LoginState::LoginState(StateMachine& stateMachine, bool replace, Client& client) : IState(stateMachine, replace),
    mClient(client)
{
    bzero(mName, sizeof mName);
}

LoginState::~LoginState()
{
    //dtor
}

void LoginState::update()
{
    ImGui::Begin("Login");
    ImGui::Text("Username");

    ImGui::InputText("", mName, sizeof mName);
    ImGui::SetWindowFocus();

    if (ImGui::Button("Login") || ImGui::IsKeyPressed(sf::Keyboard::Return))
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
