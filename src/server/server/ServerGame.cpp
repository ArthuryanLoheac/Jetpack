#include "server/server/Server.hpp"
#include "game/gameConstants.hpp"

void Server::startGame() {
    gameStarted = true;
    clock.restart();
}

void Server::sendPlayersDataToEachClient(ClientServer &player) {
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

void Server::updateGravity(ClientServer &player) {
    float fireVelocity = 0;
    float gravite = GRAVITY;

    if (player.getPlayer().isFire)
        fireVelocity = SPEED_JETPACK;
    player.getPlayer().velocity_y += (-gravite + fireVelocity) * deltaTime;
    player.getPlayer().y -= player.getPlayer().velocity_y * deltaTime;

    if (player.getPlayer().y >= HEIGHT - player.getPlayer().height - 30) {
        player.getPlayer().y = HEIGHT - player.getPlayer().height - 30;
        player.getPlayer().velocity_y = 0;
    } else if (player.getPlayer().y <= 0) {
        player.getPlayer().y = 0;
        player.getPlayer().velocity_y = 0;
    }
}

bool Server::updateGame() {
    deltaTime = clock.restart().asSeconds();
    for (auto &client : clients) {
        try {
            sendPlayersDataToEachClient(client.second);
        } catch (std::exception &e) {
            std::cerr << "Error sending data to client " << client.first
                      << ": " << e.what() << std::endl;
            return true;
        }
        updateGravity(client.second);
    }
    return false;
}

