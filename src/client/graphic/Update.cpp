/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** Update
*/
#include <map>

#include "clientRun/ClientRun.hpp"
#include "client/graphic/Player.hpp"
#include "client/graphic/ImageClass.hpp"
#include "client/client/DataManager.hpp"

static void handleMaxMin(sf::Vector2f &position) {
    bool isGround = false;
    if (position.y >= HEIGHT - Player::instance->getHeight() - 30) {
        position.y = HEIGHT - Player::instance->getHeight() - 30;
        Player::instance->setVelocityY(0);
        isGround = true;
        if (Player::instance->getLanding() == Player::ON_AIR) {
            Player::instance->setLanding(Player::LANDING);
            Player::instance->getImage().getPosRectangle().left = 0;
        }
    } else if (position.y <= 0) {
        position.y = 0;
        Player::instance->setVelocityY(0);
    }
    Player::instance->setGround(isGround);
}

static void updateVelocity(std::map<int, int> &map_keys, float deltaTime) {
    float fireVelocity = 0;
    float gravite = DataManager::instance->getGravity();

    if (map_keys[sf::Keyboard::Z] == sf::Event::KeyPressed ||
        map_keys[sf::Keyboard::Space] == sf::Event::KeyPressed) {
        Player::instance->setLanding(Player::ON_AIR);
        fireVelocity = DataManager::instance->getSpeedJetpack();
    }
    Player::instance->setFire(fireVelocity != 0);
    Player::instance->setVelocityY(Player::instance->getVelocityY() +
        ((-gravite + fireVelocity) * deltaTime));
}

void updateImage() {
    ImageClass &image = Player::instance->getImage();

    if (Player::instance->getGround()) {
        if (Player::instance->getLanding() == Player::LANDING) {
            image.getPosRectangle().top = image.getPosRectangle().height * 2;
            if (image.getPosRectangle().left / image.getPosRectangle().width >=
                    image.getNbFrame() - 1) {
                image.getPosRectangle().left = 0;
                Player::instance->setLanding(Player::ON_GROUND);
            }
        } else {
            image.getPosRectangle().top = 0;
        }
    } else {
        if (Player::instance->getFire())
            image.getPosRectangle().top = image.getPosRectangle().height;
        else
            image.setRectangle(0, image.getPosRectangle().height,
                Player::instance->getWidth(), Player::instance->getHeight());
    }
}

void update(std::map<int, int> &map_keys, float deltaTime) {
    sf::Vector2f position =
        {Player::instance->getX(), Player::instance->getY()};

    updateVelocity(map_keys, deltaTime);
    position.y -= (Player::instance->getVelocityY() * deltaTime);
    handleMaxMin(position);
    Player::instance->getImage().setPosition(position.x, position.y);
    Player::instance->setPos(position.x, position.y);
    Player::instance->getImage().updateAnimation();
    updateImage();
}
