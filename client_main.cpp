#include <SFML/Graphics.hpp>

#include "ChatState.h"
#include "Client.h"
#include "Constants.h"
#include "StateMachine.h"

int main(int argc, char** argv)
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Chat");

    StateMachine states;
    states.run(StateMachine::build<ChatState>(states, true, "lucas"));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                states.quit();
            }

            states.handleEvents(event);
        }

        states.nextState();
        states.update();

        window.clear(sf::Color::White);
        states.draw(window);
        window.display();
    }

    return 0;
}
