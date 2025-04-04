#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <poll.h>
#include <netinet/in.h>
#include <string.h>

#include <string>
#include <iostream>

#include "client/graphic/Player.hpp"
#include "client/client/DataManager.hpp"
#include "clientRun/ClientRun.hpp"
#include "client/client/Client.hpp"

#include <SFML/System/Clock.hpp>

static int returnError(std::string message) {
    std::cerr << message << std::endl;
    return 84;
}

static void readDatas(int sockfd, struct pollfd &fds) {
    char buffer[1024] = {0};
    int valread;

    if (poll(&fds, 1, 0) > 0) {
        if (fds.revents & POLLIN) {
            valread = read(sockfd, buffer, 1024);
            if (valread > 0)
                handleCommand(buffer);
        }
    }
}

static void clockPosition(sf::Clock &clock, int sockfd) {
    std::string input;

    (void)clock;
    input = "FIRE " + std::to_string(Player::instance->getFire()) + "\n";
    write(sockfd, input.c_str(), input.size());
}

void loopClient(int sockfd) {
    sf::Clock clock;
    struct pollfd fds;

    fds.fd = sockfd;
    fds.events = POLLIN;
    while (1) {
        readDatas(sockfd, fds);
        clockPosition(clock, sockfd);
    }
}

int client_connection(int &sockfd) {
    struct sockaddr_in serv_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        return returnError("Error opening socket");
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    if (inet_pton(AF_INET, DataManager::instance->getIp().c_str(),
        &serv_addr.sin_addr) <= 0)
        return returnError("Invalid IP address");
    serv_addr.sin_port = htons(DataManager::instance->getPort());
    if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
        return returnError("Connection failed");
    return 0;
}
