#include "server/server/Server.hpp"
#include "Server.hpp"

void Server::startGame() {
    gameStarted = true;
}

bool Server::updateGame() {
    printf("Game updated\n");
    for (auto &client : clients) {
        ClientServer &player = client.second;
    }
    return false;
}