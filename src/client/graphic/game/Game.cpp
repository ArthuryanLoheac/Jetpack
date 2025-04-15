#include "client/DataManager.hpp"
#include "client/graphic/game/Game.hpp"

Game::Game()
    : bg(BackGround(DataManager::instance->getTexture("BG"),
        DataManager::instance->getSpeedX())),
    bg2(BackGround(DataManager::instance->getTexture("BG"),
        DataManager::instance->getSpeedX(), 1726 * 3.7)) {
    VolumeMusic = 50;
    VolumeSound = 50;

    if (!music.buff.loadFromFile("assets/theme.ogg"))
        return;
    if (!jetpack.buff.loadFromFile("assets/jetpack.ogg"))
        return;
    jetpack.sound.setBuffer(jetpack.buff);
    music.sound.setBuffer(music.buff);
    music.sound.setLoop(true);
    music.sound.setVolume(VolumeMusic);
    jetpack.sound.setVolume(VolumeSound);
}

void Game::update(float deltaTime) {
    bg.update(deltaTime);
    bg2.update(deltaTime);
}

void Game::Start() {
    music.sound.play();
}

void Game::draw(sf::RenderWindow &window) {
    bg.draw(window);
    bg2.draw(window);
}

void Game::updateSound() {
    jetpack.sound.setVolume(VolumeSound);
    music.sound.setVolume(VolumeMusic);
}

void Game::setVolumeMusic(int volume) {
    VolumeMusic = volume;
    if (VolumeMusic < 0)
        VolumeMusic = 0;
    if (VolumeMusic > 100)
        VolumeMusic = 100;
    updateSound();
}

void Game::setVolumeSound(int volume) {
    VolumeSound = volume;
    if (VolumeSound < 0)
        VolumeSound = 0;
    if (VolumeSound > 100)
        VolumeSound = 100;
    updateSound();
}

int Game::getVolumeMusic() {
    return VolumeMusic;
}

int Game::getVolumeSound() {
    return VolumeSound;
}
