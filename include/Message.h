#ifndef MESSAGE_H_INCLUDED
#define MESSAGE_H_INCLUDED

struct MessageData
{
    MessageData(std::string name, std::string msg) : name(name), msg(msg) {}

    std::string name; // who sent this message
    std::string msg; // actual data/string
};

#endif // MESSAGE_H_INCLUDED
