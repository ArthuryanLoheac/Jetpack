#pragma once

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <poll.h>
#include <sys/wait.h>

#include <exception>
#include <iostream>
#include <csignal>
#include <atomic>
#include <unordered_map>
#include <string>

#include "server/client/Client.hpp"

class Server {
 public:
    class ftpException : public std::exception {
     public:
        ftpException(std::string message);
        const char *what() const noexcept;
     private:
        std::string _message;
    };
    Server(int port, std::string userHomePath);
    ~Server();
    void setMap(std::string path);
    void setSocketOptions(int socketFd);
    void setupServerSocket(int port);
    void run();
    void processReadyFds();
    void processSocketEvents(int fd_index);
    bool checkPollEvents();
    void initializePoll(struct pollfd fds[]);
    void handleNewConnection(struct pollfd fds[], int &nfds);
    void handleClientData(int clientFd);
    void removeClient(struct pollfd fds[], int &nfds, int index);

 private:
    int port;
    std::string map;
    int socketFd;
    const int MAX_CONNECTIONS = 42;
    std::unordered_map<int, Client> clients;
    struct pollfd *fds;
    int nfds;
    int i;
};
