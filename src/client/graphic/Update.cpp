/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** Update
*/
#include "ClientRun.hpp"
#include "Player.hpp"
#include "ImageClass.hpp"

static void handleMaxMin(sf::Vector2f &position)
{
    bool isGround = false;
    if (position.y >= HEIGHT - Player::instance->getHeight() - 30) {
        position.y = HEIGHT - Player::instance->getHeight() - 30;
        Player::instance->setVelocityY(0);
        isGround = true;
    } else if (position.y <= 0) {
        position.y = 0;
        Player::instance->setVelocityY(0);
    }
    Player::instance->setGround(isGround);
}

static void updateVelocity(std::map<int, int> &map_keys, float deltaTime)
{
    float fireVelocity = 0;
    float gravite = 400;

    if (map_keys[sf::Keyboard::Z] == sf::Event::KeyPressed || map_keys[sf::Keyboard::Space] == sf::Event::KeyPressed)
        fireVelocity = 1200;
    Player::instance->setFire(fireVelocity != 0);
    Player::instance->setVelocityY(Player::instance->getVelocityY() + ((-gravite + fireVelocity) * deltaTime));
}

void updateImage()
{
    if (Player::instance->getGround())
        Player::instance->getImage().getPosRectangle().top = 0;
    else {
        if (Player::instance->getFire())
            Player::instance->getImage().getPosRectangle().top = Player::instance->getImage().getPosRectangle().height;
        else
            Player::instance->getImage().setRectangle(0, Player::instance->getImage().getPosRectangle().height, Player::instance->getWidth(), Player::instance->getHeight());
    }
}

void update(std::map<int, int> &map_keys, float deltaTime)
{
    sf::Vector2f position = {Player::instance->getX(), Player::instance->getY()};

    updateVelocity(map_keys, deltaTime);
    position.y -= (Player::instance->getVelocityY() * deltaTime);
    handleMaxMin(position);
    Player::instance->getImage().setPosition(position.x, position.y);
    Player::instance->setPos(position.x, position.y);
    Player::instance->getImage().updateAnimation();
    updateImage();
}
