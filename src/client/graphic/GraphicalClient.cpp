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

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

static void Event(Window &window) {
    if (window.getEvent().type == sf::Event::Closed ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        window.getWindow().close();
    window.getMapKeys()[window.getEvent().key.code] = window.getEvent().type;
}

void drawPlayers(Window &window) {
    // Draw the players
    for (auto &player : DataManager::instance->getPlayers()) {
        if (player.getId() != Player::instance->getId()) {
            updateImagePlayer(player);
            player.getImage().setPosition(player.getX(), player.getY());
            player.getImage().setTransparency(100);
            player.getImage().draw(window.getWindow());
        }
    }
    // Draw the main player in front
    for (auto &player : DataManager::instance->getPlayers()) {
        if (player.getId() == Player::instance->getId()) {
            Player::instance->getImage().setPosition(
                player.getX(), player.getY());
            Player::instance->getImage().draw(window.getWindow());
        }
    }
}

int graphic(void) {
    Window window;
    Game game;

    while (window.isOpen()) {
        window.updateDeltaTime();
        while (window.pollEvent())
            Event(window);
        update(game, window);
        game.update(window.getDeltaTime());
        window.clear();
        game.draw(window.getWindow());
        drawPlayers(window);
        window.display();
    }
    return 0;
}
