#pragma once
#include <vector>

#include "client/graphic/BackGround.hpp"

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

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

    sf::Text coinsText;
    int totalCoins;

    std::vector<sf::Text> scoresLeaderBoard;
    sf::Text leaderBoardTitle;

 public:
    GameSound music;
    GameSound jetpack;
    GameSound coin;

    Game();
    void Start();
    void update(float deltaTime);
    void draw(sf::RenderWindow &window);
    void updateSound();
    void setVolumeMusic(int volume);
    void setVolumeSound(int volume);
    int getVolumeMusic();
    int getVolumeSound();
    void updateCoins(int coins);
    void drawCoins(sf::RenderWindow &window);

    void addElementScoreBoard();
};
