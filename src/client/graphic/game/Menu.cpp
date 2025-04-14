#include "client/graphic/game/Menu.hpp"
#include "DataManager.hpp"


Menu::Menu(int id)
    : bg(DataManager::instance->getTexture("Menu")) {
    bg.setScale(1.3f, 1.3f);
    bg.setPosition(-300, 0);

    youAre.setFont(DataManager::instance->getFont());
    youAre.setString("You are Player " + std::to_string(id));
    youAre.setCharacterSize(50);
    youAre.setFillColor(sf::Color::White);
    youAre.setPosition(WIDTH - 400, HEIGHT - 70);
}

void Menu::update(float deltaTime) {
    (void)deltaTime;
    text.clear();
    for (auto &player : DataManager::instance->getPlayers()) {
        sf::Text text;
        text.setFont(DataManager::instance->getFont());
        text.setString("Player " + std::to_string(player->getId())
            + (player->getReady() ? " ready" : "  not ready"));
        text.setCharacterSize(50);
        if (player->getReady())
            text.setFillColor(sf::Color::Green);
        else
            text.setFillColor(sf::Color::Red);
        text.setPosition(50, 50 + player->getId() * 80);
        this->text.push_back(text);
    }
}

void Menu::Start() {
    music.sound.play();
}

void Menu::draw(sf::RenderWindow &window) {
    bg.draw(window);
    for (auto &text : text)
        window.draw(text);
    window.draw(youAre);
}

void Menu::updateSound() {
    jetpack.sound.setVolume(VolumeSound);
    music.sound.setVolume(VolumeMusic);
}

void Menu::setVolumeMusic(int volume) {
    VolumeMusic = volume;
    if (VolumeMusic < 0)
        VolumeMusic = 0;
    if (VolumeMusic > 100)
        VolumeMusic = 100;
    updateSound();
}

void Menu::setVolumeSound(int volume) {
    VolumeSound = volume;
    if (VolumeSound < 0)
        VolumeSound = 0;
    if (VolumeSound > 100)
        VolumeSound = 100;
    updateSound();
}

int Menu::getVolumeMusic() {
    return VolumeMusic;
}

int Menu::getVolumeSound() {
    return VolumeSound;
}
