/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** GraphicalClient
*/
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <map>

#include "Player.hpp"

static void Event(sf::RenderWindow &window, std::map<int, int> &map, sf::Event &event)
{
    if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        window.close();
    if (event.key.code == sf::Keyboard::Z)
        map[sf::Keyboard::Z] = event.type;
    if (event.key.code == sf::Keyboard::S)
        map[sf::Keyboard::S] = event.type;
    if (event.key.code == sf::Keyboard::Q)
        map[sf::Keyboard::Q] = event.type;
    if (event.key.code == sf::Keyboard::D)
        map[sf::Keyboard::D] = event.type;
}

static void update(std::map<int, int> map_keys, sf::RectangleShape &shape, float deltaTime)
{
    sf::Vector2f position = {Player::instance->getX(), Player::instance->getY()};
    if (map_keys[sf::Keyboard::Z] == sf::Event::KeyPressed)
        position.y -= 200 * deltaTime;
    if (map_keys[sf::Keyboard::S] == sf::Event::KeyPressed)
        position.y += 200 * deltaTime;
    if (map_keys[sf::Keyboard::Q] == sf::Event::KeyPressed)
        position.x -= 200 * deltaTime;
    if (map_keys[sf::Keyboard::D] == sf::Event::KeyPressed)
        position.x += 200 * deltaTime;
    shape.setPosition(position);
    Player::instance->setPos(position.x, position.y);
}
    
int graphic()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
    sf::RectangleShape shape(sf::Vector2f(100, 100));
    sf::Clock clock;
    std::map<int, int> map_keys = {
        {sf::Keyboard::Z, sf::Event::KeyReleased},
        {sf::Keyboard::S, sf::Event::KeyReleased},
        {sf::Keyboard::Q, sf::Event::KeyReleased},
        {sf::Keyboard::D, sf::Event::KeyReleased}};
    sf::Event event;

    shape.setFillColor(sf::Color::Green);
    shape.setPosition(Player::instance->getX(), Player::instance->getY());
    while (window.isOpen())
    {
        while (window.pollEvent(event))
            Event(window, map_keys, event);
        update(map_keys, shape, clock.restart().asSeconds());
        window.clear();
        window.draw(shape);
        window.display();
    }
    return 0;
}