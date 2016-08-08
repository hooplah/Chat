#include <thread>

#include "Server.h"

int main()
{
    Server server;
    while (true)
        server.update();

    return 0;
}
