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
    window.getMapKeys()[window.getEvent().key.code] = window.getEvent().type;
}

void updateMenu(Window &window, Menu &menu) {
    while (window.pollEvent())
        EventMenu(window);
    menu.update(window.getDeltaTime());
    window.clear();
    menu.draw(window.getWindow());
}