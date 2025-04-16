#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <poll.h>
#include <sys/wait.h>

#include <iostream>
#include <exception>
#include <csignal>
#include <atomic>
#include <string>
#include <vector>
#include <algorithm>

#include "server/Server.hpp"
#include "server/Obstacle.hpp"
#include "log/Log.hpp"
#include "Server.hpp"

std::atomic<bool> sigInt;

Server::ftpException::ftpException(std::string message) {
    _message = message;
}

const char *Server::ftpException::what() const noexcept {
    return _message.c_str();
}

// ---------------------------- END CLASS THROW ----------------------------

Server::Server(int port, std::string _map) :
port(port), map(_map), nfds(1), i(0), gameStarted(false) {
    fds = new struct pollfd[MAX_CONNECTIONS];
    Log::info() << "Map:\n" << map << std::endl;
    iClient = 0;
}

Server::~Server() {
    delete[] fds;
    close(socketFd);
    Log::info() << "\nServer stopped" << std::endl;
}

void Server::setMap(std::string path) {
    map = path;
}

void Server::handleNewConnection(struct pollfd fds[], int &nfds) {
    struct sockaddr_in addrIn;
    socklen_t addrInSize = sizeof(addrIn);
    int clientFd = accept(socketFd, (struct sockaddr *)&addrIn, &addrInSize);

    if (clientFd == -1) {
        throw ftpException("Error: accept");
    }
    fds[nfds].fd = clientFd;
    fds[nfds].events = POLLIN;
    nfds++;
    clients.try_emplace(clientFd, iClient, clientFd, map);
    iClient++;
    if (clients.size() == 1)
        clock.restart();
}

void Server::handleClientData(int clientFd) {
    try {
        if (!clients.at(clientFd).handleInput()) {
            removeClient(fds, nfds, i);
            i--;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error handling client " << clientFd << ": "
                  << e.what() << std::endl;
        removeClient(fds, nfds, i);
        i--;
    }
}

void Server::removeClient(struct pollfd fds[], int &nfds, int index) {
    int clientFd = fds[index].fd;

    clients.erase(clientFd);
    for (int j = index; j < nfds - 1; j++) {
        fds[j] = fds[j + 1];
    }
    nfds--;
}

void signalHandler(int signal) {
    (void)signal;
    sigInt = true;
}

bool Server::handleGameEvents() {
    if (!gameStarted)
        startGame();
    return updateGame();
}

bool Server::handleMenuEvents() {
    return updateMenu();
}

void Server::sortObstacles() {
    std::sort(obstacles.begin(), obstacles.end(), Obstacle::cmpObstacle);
}

void Server::getMapObstacles() {
    int id = 0;
    int x = 0;
    int y = 0;
    for (char c : map) {
        if (c == 'c') {
            obstacles.emplace_back(id, x, y, Obstacle::COIN);
            id++;
        } else if (c == 'e') {
            obstacles.emplace_back(id, x, y, Obstacle::BOMB);
            id++;
        }
        if (c == '\n') {
            x = 0;
            y += 92;
        } else {
            x += 92;
        }
    }
}

void Server::checkWins() {
    std::cerr << obstacles.size() << std::endl;
}

void Server::run()
{
    bool hasEvents;
    struct sigaction sigIntHandler;

    initializePoll(fds);
    sigIntHandler.sa_handler = signalHandler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;
    sigaction(SIGINT, &sigIntHandler, nullptr);
    sigInt = false;
    getMapObstacles();
    sortObstacles();
    while (!sigInt) {
        if (state == GAME)
            sigInt = handleGameEvents();
        else if (state == MENU)
            sigInt = handleMenuEvents();
        hasEvents = checkPollEvents();
        if (hasEvents) {
            processReadyFds();
        }
    }
}
