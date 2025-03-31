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

#include "server/Server.hpp"
#include "log/Log.hpp"

std::atomic<bool> sigInt;

Server::ftpException::ftpException(std::string message) {
    _message = message;
}

const char *Server::ftpException::what() const noexcept {
    return _message.c_str();
}

// ---------------------------- END CLASS THROW ----------------------------

Server::Server(int port, std::string _map) :
port(port), map(_map), nfds(1), i(0) {
    fds = new struct pollfd[MAX_CONNECTIONS];
    Log::info() << "Map:\n" << map << std::endl;
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
    clients.try_emplace(clientFd, i, clientFd, map);
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

void Server::run() {
    bool hasEvents;
    struct sigaction sigIntHandler;

    initializePoll(fds);
    sigIntHandler.sa_handler = signalHandler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;
    sigaction(SIGINT, &sigIntHandler, nullptr);
    sigInt = false;
    while (!sigInt) {
        hasEvents = checkPollEvents();
        if (hasEvents) {
            processReadyFds();
        }
    }
}
