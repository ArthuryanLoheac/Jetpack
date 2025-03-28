/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** Update
*/
#include "ClientRun.hpp"
#include "Player.hpp"

static void handleMaxMin(sf::Vector2f &position)
{
    if (position.y >= 570) {
        position.y = 570;
        Player::instance->setVelocityY(0);
    } else if (position.y <= 0){
        position.y = 0;
        Player::instance->setVelocityY(0);
    }
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

void update(std::map<int, int> &map_keys, sf::RectangleShape &shape, float deltaTime)
{
    sf::Vector2f position = {Player::instance->getX(), Player::instance->getY()};

    updateVelocity(map_keys, deltaTime);
    position.y -= (Player::instance->getVelocityY() * deltaTime);
    handleMaxMin(position);
    shape.setPosition(position);
    Player::instance->setPos(position.x, position.y);
}
