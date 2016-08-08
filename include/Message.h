#ifndef MESSAGE_H_INCLUDED
#define MESSAGE_H_INCLUDED

#include <SFML/Graphics/Text.hpp>

#include "User.h"

struct MessageData
{
    MessageData(std::string name, std::string msg) : name(name), msg(msg) {}

    std::string name; // who sent this message
    std::string msg; // actual data/string
};

struct DrawableMessage
{
    DrawableMessage(MessageData data, sf::Font& font) : data(data)
    {
        text = sf::Text(getFullLine(), font, 24);
        text.setColor(sf::Color::Black);
    }

    MessageData data;
    sf::Text text; // what needs to be drawn

    void sync(){text.setString(data.msg);}
    void setPosition(sf::Vector2f pos){text.setPosition(pos);}
    std::string getFullLine()
    {
        if (data.name == "" && data.msg == "")
            return ("");

        std::string str = data.name;
        str.append(": ");
        str.append(data.msg);
        return str;
    }
};

#endif // MESSAGE_H_INCLUDED
