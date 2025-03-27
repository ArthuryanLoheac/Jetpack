/*
** EPITECH PROJECT, 2025
** BS
** File description:
** ServerConf
*/

#include "Server.hpp"
#include <iostream>
#include <exception>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <poll.h>
#include <sys/wait.h>
#include <csignal>
#include <atomic>

void Server::setSocketOptions(int socketFd)
{
    int opt = 1;

    if (setsockopt(socketFd, SOL_SOCKET, SO_REUSEADDR, &opt,
        sizeof(opt)) == -1) {
        throw ftpException("Error: setsockopt");
    }
}

void Server::setupServerSocket(int port)
{
    struct sockaddr_in addrIn;

    socketFd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFd == -1)
        throw ftpException("Error: socket");
    setSocketOptions(socketFd);
    addrIn.sin_family = AF_INET;
    addrIn.sin_port = htons(port);
    addrIn.sin_addr.s_addr = INADDR_ANY;
    if (bind(socketFd, (struct sockaddr *)&addrIn, sizeof(addrIn)) == -1) {
        throw ftpException("Error: bind");
    }
    if (listen(socketFd, MAX_CONNECTIONS) == -1) {
        throw ftpException("Error: listen");
    }
}

void Server::initializePoll(struct pollfd fds[])
{
    fds[0].fd = socketFd;
    fds[0].events = POLLIN;
}

void Server::processSocketEvents(int fd_index)
{
    if (fds[fd_index].fd == socketFd) {
        handleNewConnection(fds, nfds);
    } else {
        handleClientData(fds[fd_index].fd);
    }
}

bool Server::checkPollEvents()
{
    int poll_result = poll(fds, nfds, -1);

    if (poll_result == -1) {
        if (errno == EINTR) {
            return false;
        }
        throw ftpException("Error: poll");
    }
    return poll_result > 0;
}

void Server::processReadyFds()
{
    for (i = nfds - 1; i >= 0; i--) {
        if (fds[i].revents & POLLIN) {
            processSocketEvents(i);
        }
    }
}

