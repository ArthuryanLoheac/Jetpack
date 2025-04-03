#include "server/server/Server.hpp"
#include "Server.hpp"

void Server::startGame() {
    gameStarted = true;
}

bool Server::updateGame() {
    printf("Game updated\n");
    for (auto &client : clients) {
        ClientServer &player = client.second;
        for (auto &otherClient : clients) {
            player.sendOutput(
                "PLAYER " + std::to_string(otherClient.second.getPlayer().id) + " " +
                std::to_string(otherClient.second.getPlayer().x) + " " +
                std::to_string(otherClient.second.getPlayer().y) + " " +
                std::to_string(otherClient.second.getPlayer().velocity_y) + " " +
                std::to_string(otherClient.second.getPlayer().coins) + " " +
                std::to_string(otherClient.second.getPlayer().isFire));
        }
    }
    return false;
}