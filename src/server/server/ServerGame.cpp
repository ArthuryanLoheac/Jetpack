#include <iostream>

#include "server/server/Server.hpp"
#include "game/gameConstants.hpp"
#include "server/Obstacle.hpp"

#include "SFML/Graphics.hpp"

void Server::startGame() {
    gameStarted = true;
    clock.restart();
}

void Server::sendPlayersDataToEachClient(ClientServer &player) {
    for (auto &otherClient : clients) {
        if (otherClient.second.getPlayer().isAlive == false)
            continue;
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

    if (player.getPlayer().y >= HEIGHT - player.getPlayer().height) {
        player.getPlayer().y = HEIGHT - player.getPlayer().height;
        player.getPlayer().velocity_y = 0;
    } else if (player.getPlayer().y <= 0) {
        player.getPlayer().y = 0;
        player.getPlayer().velocity_y = 0;
    }
}

bool Server::checkCollisions(ClientServer &player) {
    auto &p = player.getPlayer();
    sf::FloatRect rectPlayer = {p.x, p.y, 92, 92};

    for (size_t i = 0; i < obstacles.size(); i++) {
        if (obstacles[i].getRect().left < -100) {
            obstacles.erase(obstacles.begin() + i);
            i--;
        }
    }
    for (auto obstacle = obstacles.rend();
        obstacle != obstacles.rbegin(); --obstacle) {
        if (obstacle->getRect().left > 300)
            break;
        if (rectPlayer.intersects(obstacle->getRect())) {
            if (obstacle->getType() == Obstacle::COIN &&
                !p.checkCoinsEarned(obstacle->getId()) && p.isAlive) {
                p.coins += 1;
                p.coinsEarned.push_back(obstacle->getId());
                return false;
            } else if (obstacle->getType() == Obstacle::BOMB) {
                for (auto &pToSend : clients)
                    pToSend.second.sendOutput("DEATH " + std::to_string(p.id));
                p.isAlive = false;
                p.isDeadThisFrame = true;
                return true;
            }
        }
    }
    return false;
}

void Server::updatePosObstacles() {
    for (auto obstacle = obstacles.rbegin();
        obstacle != obstacles.rend(); ++obstacle)
        obstacle->getRectRef().left -= deltaTime * 500;
}

bool Server::updateGame() {
    deltaTime = clock.restart().asSeconds();
    int count = 0;

    updatePosObstacles();
    for (auto &client : clients) {
        try {
            sendPlayersDataToEachClient(client.second);
        } catch (std::exception &e) {
            std::cerr << "Error sending data to client " << client.first
                      << ": " << e.what() << std::endl;
        }
        updateGravity(client.second);
        if (checkCollisions(client.second))
            count++;
    }
    checkWins();
    //  if (clients.size() - count < 2)
    //      return true;
    return false;
}

