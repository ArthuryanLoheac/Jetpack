#include <unistd.h>

#include <iostream>
#include <vector>
#include <map>

#include "clientRun/ClientRun.hpp"
#include "client/graphic/Player.hpp"
#include "client/graphic/ImageClass.hpp"
#include "client/graphic/BackGround.hpp"
#include "client/graphic/game/Game.hpp"
#include "client/graphic/window/Window.hpp"
#include "client/DataManager.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

static void EventGame(Window &window) {
    if (window.getEvent().type == sf::Event::Closed ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        window.getWindow().close();
    window.getMapKeys()[window.getEvent().key.code] = window.getEvent().type;
}

void drawPlayers(Window &window) {
    // Draw the players
    for (auto &player : DataManager::instance->getPlayers()) {
        if (player->getId() != Player::instance->getId()) {
            updateImagePlayer(*player);
            player->getImage().setPosition(player->getX(), player->getY());
            player->getImage().setTransparency(100);
            player->getImage().draw(window.getWindow());
            player->getNameTxt().setPosition(player->getX() +
                player->getWidth()/4, player->getY());
            if (player->getIsDisconnected() && player->getAlive() &&
                Player::instance->getAlive() &&
                player->getTimeDrawDisconnected() > 0)
                window.getWindow().draw(player->getDisconnectTxt());
            window.getWindow().draw(player->getNameTxt());
        }
    }
    // Draw the main player in front
    for (auto &player : DataManager::instance->getPlayers()) {
        if (player->getId() == Player::instance->getId()) {
            Player::instance->getImage().setPosition(
                player->getX(), player->getY());
            Player::instance->getImage().draw(window.getWindow());
        }
    }
}

void updateVelocity(float deltaTime, Player &player) {
    float fireVelocity = player.getFire() ?
        DataManager::instance->getSpeedJetpack() : 0;
    float gravite = DataManager::instance->getGravity();

    player.setVelocityY(player.getVelocityY() +
        ((-gravite + fireVelocity) * deltaTime));
}

void updatePlayers(Window &window) {
    for (auto &player : DataManager::instance->getPlayers()) {
        std::lock_guard<std::mutex> lock(player->getMutexPlayer());
        if (player->getId() != Player::instance->getId()) {
            sf::Vector2f position =
                {player->getX(), player->getY()};
            updateVelocity(window.getDeltaTime(), *player);
            position.y -= (player->getVelocityY() * window.getDeltaTime());
            handleMaxMin(position);
            player->setPos(position.x, position.y);
            if (!player->getIsDisconnected()) {
                player->setTimeDisconnect(player->getTimeDisconnect() -
                    window.getDeltaTime());
                if (player->getTimeDisconnect() < 0 && player->getAlive())
                    player->setIsDisconnected(true);
            } else if (player->getTimeDrawDisconnected() > 0) {
                player->setTimeDrawDisconnected(
                    player->getTimeDrawDisconnected() - window.getDeltaTime());
            }
        }
    }
}

void updateGame(Window &window, Game &game) {
    while (window.pollEvent())
        EventGame(window);
    update(game, window);
    game.update(window.getDeltaTime());
    DataManager::instance->updateMap(window.getDeltaTime());
    updatePlayers(window);
    game.updateCoins(Player::instance->getCoins());
    window.clear();
    game.draw(window.getWindow());
    DataManager::instance->drawMap(window);
    drawPlayers(window);
    game.drawCoins(window.getWindow());
    game.setResult();
    game.drawResult(window.getWindow());
}
