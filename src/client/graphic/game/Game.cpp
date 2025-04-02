#include "Game.hpp"

Game::Game() 
    : bg(BackGround()), bg2(BackGround(1726 * 3.7)) {
    if (!music.buff.loadFromFile("assets/theme.ogg"))
        return;
    music.sound.setBuffer(music.buff);
    music.sound.play();
    music.sound.setLoop(true);
}

void Game::update(float deltaTime) {
    bg.update(deltaTime);
    bg2.update(deltaTime);
}

void Game::draw(sf::RenderWindow &window) {
    bg.draw(window);
    bg2.draw(window);
}
