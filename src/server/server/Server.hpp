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
#include <vector>

#include "server/client/ClientServer.hpp"
#include "server/Obstacle.hpp"

#include "SFML/System/Clock.hpp"

class Server {
 public:
    enum GameState {
        MENU,
        GAME
    };

    class ftpException : public std::exception {
     public:
        explicit ftpException(std::string message);
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
    bool handleGameEvents();
    bool handleMenuEvents();
    void sortObstacles();
    void getMapObstacles();
    void checkWins();
    bool endOfRun();
    bool lastPlayerStanding();
    bool isEveryoneDead();

    void startGame();
    bool updateGame();
    void sendPlayersDataToEachClient(ClientServer &player);
    void updateGravity(ClientServer &player);
    bool checkCollisions(ClientServer &player);
    void updatePosObstacles();

    bool updateMenu();
    void sendReadyDataToEachClient(ClientServer &player);

 private:
    sf::Clock clock;

    int port;
    std::string map;
    int socketFd;
    const int MAX_CONNECTIONS = 42;
    std::unordered_map<int, ClientServer> clients;
    struct pollfd *fds;
    int nfds;
    int i;
    int iClient;
    GameState state = MENU;
    bool gameStarted;
    float deltaTime;
    bool ended = false;
    std::vector<Obstacle> obstacles;
};
