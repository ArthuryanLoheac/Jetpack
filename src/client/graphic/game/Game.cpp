#include <vector>
#include <tuple>
#include <algorithm>
#include <string>

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
    if (!coin.buff.loadFromFile("assets/coin_pickup_1.wav"))
        return;
    jetpack.sound.setBuffer(jetpack.buff);
    music.sound.setBuffer(music.buff);
    coin.sound.setBuffer(coin.buff);
    music.sound.setLoop(true);
    music.sound.setVolume(VolumeMusic);
    jetpack.sound.setVolume(VolumeSound);
    coin.sound.setVolume(VolumeSound);
    coinsText.setFont(DataManager::instance->getFont());
    coinsText.setCharacterSize(30);
    coinsText.setFillColor(sf::Color::White);
    coinsText.setPosition(10, 10);
    totalCoins = 0;

    leaderBoardTitle.setFillColor(sf::Color::White);
    leaderBoardTitle.setFont(DataManager::instance->getFont());
    leaderBoardTitle.setCharacterSize(30);
    leaderBoardTitle.setPosition({WIDTH - 180, 0});
    leaderBoardTitle.setString("LEADERBOARD");

    result.setFillColor(sf::Color::White);
    result.setFont(DataManager::instance->getFont());
    result.setCharacterSize(30);
    result.setPosition({WIDTH / 2 - 100, HEIGHT / 2 - 50});
}

bool cmpTuple(const std::tuple<int, int> &a, const std::tuple<int, int> &b) {
    return std::get<1>(a) > std::get<1>(b);
}

void Game::update(float deltaTime) {
    bg.update(deltaTime);
    bg2.update(deltaTime);
    std::vector<std::tuple<int, int>> IdScores;

    for (size_t i = 0; i < DataManager::instance->getPlayers().size(); i++)
        IdScores.push_back({DataManager::instance->getPlayers()[i]->getId(),
            DataManager::instance->getPlayers()[i]->getCoins()});
    std::sort(IdScores.begin(), IdScores.end(), cmpTuple);
    for (size_t i = 0; i < IdScores.size(); i++) {
        if (i >= scoresLeaderBoard.size())
            addElementScoreBoard();
        scoresLeaderBoard[i].setString(
            "Player " + std::to_string(std::get<0>(IdScores[i]))
            + ": " + std::to_string(std::get<1>(IdScores[i])));
        scoresLeaderBoard[i].setPosition({WIDTH - 150, (i+1) * 35.f});
        if (std::get<0>(IdScores[i]) == Player::instance->getId())
            scoresLeaderBoard[i].setFillColor(sf::Color::Green);
        else
            scoresLeaderBoard[i].setFillColor(sf::Color::White);
    }
}

void Game::Start() {
    music.sound.play();
}

void Game::draw(sf::RenderWindow &window) {
    bg.draw(window);
    bg2.draw(window);

    window.draw(leaderBoardTitle);
    for (auto &s : scoresLeaderBoard)
        window.draw(s);
}

void Game::updateCoins(int coins) {
    totalCoins = coins;
    coinsText.setString("Total Coins " + std::to_string(totalCoins));
}

void Game::drawCoins(sf::RenderWindow &window) {
    window.draw(coinsText);
}

void Game::setResult() {
    if (!DataManager::instance->getIdWinners().empty()) {
        for (auto &s : DataManager::instance->getIdWinners()) {
            if (s == Player::instance->getId()) {
                result.setString("VICTORY");
                return;
            }
        }
        result.setString("DEFEAT");
    }
}

void Game::drawResult(sf::RenderWindow &window) {
    if (!DataManager::instance->getIdWinners().empty())
        window.draw(result);
    window.draw(result);
}

void Game::addElementScoreBoard() {
    scoresLeaderBoard.push_back(sf::Text());
    int s = scoresLeaderBoard.size();
    scoresLeaderBoard[s - 1].setFillColor(sf::Color::White);
    scoresLeaderBoard[s - 1].setFont(DataManager::instance->getFont());
    scoresLeaderBoard[s - 1].setCharacterSize(30);
    scoresLeaderBoard[s - 1].setPosition({WIDTH - 150, 0});
}

void Game::updateSound() {
    jetpack.sound.setVolume(VolumeSound);
    coin.sound.setVolume(VolumeSound);
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
