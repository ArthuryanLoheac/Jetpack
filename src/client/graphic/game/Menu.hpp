#pragma once

#include "client/graphic/BackGround.hpp"
#include "clientRun/ClientRun.hpp"

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

class Menu {
 private:
    struct MenuSound {
        sf::SoundBuffer buff;
        sf::Sound sound;
    };

    ImageClass bg;
    std::vector<sf::Text> text;

    sf::Text youAre;

    int VolumeMusic;
    int VolumeSound;
 public:
    MenuSound music;
    MenuSound jetpack;

    explicit Menu(int id);
    void Start();
    void update(float deltaTime);
    void draw(sf::RenderWindow &window);
    void updateSound();
    void setVolumeMusic(int volume);
    void setVolumeSound(int volume);
    int getVolumeMusic();
    int getVolumeSound();
};
