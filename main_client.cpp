#include <string>

#include "clientRun/ClientRun.hpp"
#include "client/graphic/Player.hpp"
#include "client/client/DataManager.hpp"
#include <memory>

Player *Player::instance = nullptr;

int checkArgs(int ac, char **av) {
    int i = 1;

    while (i < ac) {
        if (strcmp(av[i], "-d") == 0) {
            DataManager::instance->setDebug(true);
            i++;
        } else if (strcmp(av[i], "-p") == 0) {
            DataManager::instance->setPort(atoi(av[i + 1]));
            if (DataManager::instance->getPort() < 0 ||
                DataManager::instance->getPort() > 65535)
                return 84;
            i+= 2;
        } else if (strcmp(av[i], "-h") == 0) {
            DataManager::instance->setIp(av[i + 1]);
            i+= 2;
        } else {
            return 84;
        }
    }
    return 0;
}

int main(int ac, char **av) {
    int sockfd;
    DataManager dataManager;
    DataManager::instance->setDebug(false);
    Client client(0, sockfd, "");
    Player player(DataManager::instance->getTexturePlayer());
    DataManager::instance->getPlayers().push_back(player);

    if (!(ac == 5 || ac == 6))
        return 84;
    if (checkArgs(ac, av) == 84)
        return 84;
    if (client_connection(sockfd) == 84)
        return 84;
    std::thread t1(graphic);
    std::thread t2(loopClient, sockfd);
    t1.join();
    t2.detach();

    return 0;
}
