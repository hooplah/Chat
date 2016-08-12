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
