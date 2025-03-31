#include <string>

#include "clientRun/ClientRun.hpp"
#include "client/graphic/Player.hpp"

Player *Player::instance = nullptr;

int checkArgs(int ac, char **av, int &port, std::string &ip) {
    int i = 1;

    while (i < ac) {
        if (strcmp(av[i], "-d") == 0) {
            i++;
        } else if (strcmp(av[i], "-p") == 0) {
            port = atoi(av[i + 1]);
            if (port < 0 || port > 65535)
                return 84;
            i+= 2;
        } else if (strcmp(av[i], "-h") == 0) {
            ip = av[i + 1];
            i+= 2;
        } else {
            return 84;
        }
    }
    return 0;
}

int main(int ac, char **av) {
    Player player;
    std::string ip;
    int port;
    int sockfd;

    if (!(ac == 5 || ac == 6))
        return 84;
    if (checkArgs(ac, av, port, ip) == 84)
        return 84;
    if (client(port, ip, sockfd) == 84)
        return 84;
    std::thread t1(graphic);
    std::thread t2(loopClient, sockfd);
    t1.join();
    t2.detach();

    return 0;
}
