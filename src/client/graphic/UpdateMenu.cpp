#include <unistd.h>

#include <iostream>
#include <vector>
#include <map>

#include "clientRun/ClientRun.hpp"
#include "client/graphic/Player.hpp"
#include "client/graphic/ImageClass.hpp"
#include "client/graphic/BackGround.hpp"
#include "client/graphic/game/Game.hpp"
#include "client/graphic/game/Menu.hpp"
#include "client/graphic/window/Window.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

static void EventMenu(Window &window) {
    if (window.getEvent().type == sf::Event::Closed ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        window.getWindow().close();
    if (window.getEvent().type == sf::Event::KeyReleased && window.getMapKeys()[window.getEvent().key.code] == sf::Event::KeyPressed &&
        window.getEvent().key.code == sf::Keyboard::Enter) {
        if (Player::instance->getReady() == Player::NOT_READY) {
            Player::instance->setReady(Player::READY);
        } else {
            Player::instance->setReady(Player::NOT_READY);
        }
    }
    window.getMapKeys()[window.getEvent().key.code] = window.getEvent().type;
}

void updateMenu(Window &window, Menu &menu) {
    while (window.pollEvent())
        EventMenu(window);
    menu.update(window.getDeltaTime());
    window.clear();
    menu.draw(window.getWindow());
}