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

#include "ClientRun.hpp"
#include "Player.hpp"
#include "ImageClass.hpp"

static void Event(sf::RenderWindow &window, std::map<int, int> &map, sf::Event &event)
{
    if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        window.close();
    if (event.key.code == sf::Keyboard::Z)
        map[sf::Keyboard::Z] = event.type;
    if (event.key.code == sf::Keyboard::Space)
        map[sf::Keyboard::Space] = event.type;
}

int graphic(void)
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML window");
    sf::Clock clock;
    std::map<int, int> map_keys = {
        {sf::Keyboard::Z, sf::Event::KeyReleased},
        {sf::Keyboard::Space, sf::Event::KeyReleased}};
    sf::Event event;

    while (window.isOpen())
    {
        while (window.pollEvent(event))
            Event(window, map_keys, event);
        update(map_keys, clock.restart().asSeconds());
        window.clear();
        Player::instance->getImage().draw(window);
        window.display();
    }
    return 0;
}