#ifndef MESSAGE_H_INCLUDED
#define MESSAGE_H_INCLUDED

typedef sf::Uint8 ClientID;

struct MessageData
{
    MessageData(std::string name, std::string msg) : name(name), msg(msg) {}

    std::string name; // who sent this message
    std::string msg; // actual data/string
};

struct ChatData // for server
{
    std::vector<MessageData> log;
    std::vector<ClientID> recipients; // members of the chat
};

#endif // MESSAGE_H_INCLUDED
