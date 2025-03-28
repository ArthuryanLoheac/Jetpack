/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** ConnectionServor
*/
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include <poll.h>
#include <SFML/System/Clock.hpp>
#include <string.h>
#include <netinet/in.h>

#include "Player.hpp"

static int returnError(std::string message)
{
    std::cerr << message << std::endl;
    return 84;
}

static void readDatas(int sockfd, struct pollfd &fds)
{
    char buffer[1024] = {0};
    int valread;

    if (poll(&fds, 1, 0) > 0) {
        if (fds.revents & POLLIN) {
            valread = read(sockfd, buffer, 1024);
            if (valread > 0)
                std::cout << buffer;
        }
    }
}

static void clockPosition(sf::Clock &clock, int sockfd)
{
    std::string input;

    if (clock.getElapsedTime().asSeconds() > 1.f/30.f) {
        clock.restart();
        input = "x : " + std::to_string(Player::instance->getX()) + " y : " + std::to_string(Player::instance->getY()) + "\n";
        write(sockfd, input.c_str(), input.size());
    }
}

static void loopClient(int sockfd)
{
    sf::Clock clock;
    struct pollfd fds;

    fds.fd = sockfd;
    fds.events = POLLIN;
    while (1) {
        readDatas(sockfd, fds);
        clockPosition(clock, sockfd);
    }
}

int client(int ac, char **av)
{
    struct sockaddr_in serv_addr;
    std::string port;
    int sockfd;

    if (ac != 2)
        return 84;
    port = av[1];
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        return returnError("Error opening socket");
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(std::stoi(port));
    if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
        return returnError("Connection failed");
    loopClient(sockfd);
    return 0;
}
