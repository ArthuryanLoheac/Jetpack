#include "server/server/Server.hpp"
#include "Server.hpp"
#include "gameConstants.hpp"

void Server::startGame() {
    gameStarted = true;
    clock.restart();
}

void Server::sendPlayersDataToEachClient(ClientServer &player)
{
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

//static void handleMaxMin(sf::Vector2f &position) {
//    bool isGround = false;
//    if (position.y >= HEIGHT - Player::instance->getHeight() - 30) {
//        position.y = HEIGHT - Player::instance->getHeight() - 30;
//        Player::instance->setVelocityY(0);
//        isGround = true;
//        if (Player::instance->getLanding() == Player::ON_AIR) {
//            Player::instance->setLanding(Player::LANDING);
//            Player::instance->getImage().getPosRectangle().left = 0;
//        }
//    } else if (position.y <= 0) {
//        position.y = 0;
//        Player::instance->setVelocityY(0);
//    }
//    Player::instance->setGround(isGround);
//}

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
        sendPlayersDataToEachClient(client.second);
        updateGravity(client.second);
    }
    return false;
}