#pragma once

#include "client/graphic/BackGround.hpp"

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

class Game {
 private:
    struct GameSound {
        sf::SoundBuffer buff;
        sf::Sound sound;
    };

    BackGround bg;
    BackGround bg2;

    int VolumeMusic;
    int VolumeSound;
 public:
    GameSound music;
    GameSound jetpack;

    Game();
    void update(float deltaTime);
    void draw(sf::RenderWindow &window);
    void updateSound();
    void setVolumeMusic(int volume);
    void setVolumeSound(int volume);
    int getVolumeMusic();
    int getVolumeSound();
};
