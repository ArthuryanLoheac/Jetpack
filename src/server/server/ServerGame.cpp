#include <iostream>

#include "server/server/Server.hpp"
#include "game/gameConstants.hpp"
#include "server/Obstacle.hpp"

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

bool Server::checkCollisions(ClientServer &player) {
    auto p = player.getPlayer();
    for (auto obstacle = obstacles.rbegin();
        obstacle != obstacles.rend(); ++obstacle) {
        if (p.x + p.width >= obstacle->getRect().left &&
            p.x <= obstacle->getRect().left + obstacle->getRect().width &&
            p.y + p.height >= obstacle->getRect().top &&
            p.y <= obstacle->getRect().top + obstacle->getRect().height) {
            if (obstacle->getType() == Obstacle::COIN &&
                !p.checkCoinsEarned(obstacle->getId())) {
                p.coins++;
                p.coinsEarned.push_back(obstacle->getId());
                obstacles.erase(std::next(obstacle).base());
                return false;
            } else if (obstacle->getType() == Obstacle::BOMB) {
                player.sendOutput("DEATH" + std::to_string(p.id));
                return true;
            }
        }
    }
    return false;
}

bool Server::updateGame() {
    deltaTime = clock.restart().asSeconds();
    int count = 0;

    for (auto &client : clients) {
        try {
            sendPlayersDataToEachClient(client.second);
        } catch (std::exception &e) {
            std::cerr << "Error sending data to client " << client.first
                      << ": " << e.what() << std::endl;
            // Continue processing other clients despite the error
        }
        updateGravity(client.second);
        if (checkCollisions(client.second))
            count++;
    }

    if (clients.size() - count > 2)
        return true;
    return false;
}

