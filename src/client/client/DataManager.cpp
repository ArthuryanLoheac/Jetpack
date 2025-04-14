#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <sstream>

#include "client/client/DataManager.hpp"
#include "DataManager.hpp"

DataManager* DataManager::instance = nullptr;

DataManager::DataManager() {
    if (instance)
        return;
    instance = this;
    textures["Player"] = sf::Texture();
    textures["Player"].loadFromFile("assets/player_sprite_sheet.png");
    textures["BG"] = sf::Texture();
    textures["BG"].loadFromFile("assets/background.png");
    textures["Menu"] = sf::Texture();
    textures["Menu"].loadFromFile("assets/menu.jpg");
    textures["Zapper"] = sf::Texture();
    textures["Zapper"].loadFromFile("assets/zapper_sprite_sheet.png");
    textures["Coins"] = sf::Texture();
    textures["Coins"].loadFromFile("assets/coins_sprite_sheet.png");
    font.loadFromFile("assets/jetpack_font.ttf");
}

int DataManager::getGravity() const {
    return gravity;
}

int DataManager::getSpeedX() const {
    return speed_x;
}

int DataManager::getSpeedJetpack() const {
    return speed_jetpack;
}

int DataManager::getId() const {
    return my_id;
}

bool DataManager::getDebug() const {
    return debug;
}

int DataManager::getPort() const {
    return port;
}

std::string DataManager::getIp() const {
    return ip;
}

std::vector<std::unique_ptr<Player>> &DataManager::getPlayers() {
    return players;
}

DataManager::GameState DataManager::getState() const {
    return state;
}

sf::Texture &DataManager::getTexture(std::string x)
{
    return textures[x];
}

Player &DataManager::addNewPlayer()
{
    players.emplace_back(std::make_unique<Player>(textures["Player"]));
    return *players.back();
}

void DataManager::updateMap(float dt) {
    for (size_t i = 0; i < obstacles.size(); i++) {
        obstacles[i].update(dt);
        if (obstacles[i].x < -143) {
            obstacles.erase(obstacles.begin() + i);
            i--;
        }
    }
}

void DataManager::drawMap(Window &window) {
    for (auto &ob : obstacles)
        ob.draw(window);
}

void DataManager::setGravity(int gravity) {
    this->gravity = gravity;
}

void DataManager::setSpeedX(int speed) {
    speed_x = speed;
}

void DataManager::setSpeedJetpack(int speed) {
    speed_jetpack = speed;
}

void DataManager::setId(int id) {
    my_id = id;
}

void DataManager::setDebug(bool isDebug) {
    debug = isDebug;
}

void DataManager::setPort(int port) {
    this->port = port;
}

void DataManager::setIp(std::string ip) {
    this->ip = ip;
}

void DataManager::setState(GameState state) {
    this->state = state;
}

void DataManager::setMap(std::vector<std::string> map) {
    this->map.clear();
    this->map = map;
    int size = 143;
    int x = 0;
    int y = 0;

    for (auto &s : this->map) {
        x = 0;
        for (char &c : s) {
            if (c == 'c')
                obstacles.push_back(Obstacle(x, y, Obstacle::COIN));
            else if (c == 'e'){
                obstacles.push_back(Obstacle(x, y, Obstacle::OBSTACLE));}
            x += size;
        }
        y += size;
    }

    std::sort(obstacles.begin(), obstacles.end(), Obstacle::cmpObstacles);
}

sf::Font &DataManager::getFont() {
    return font;
}

std::vector<std::string> DataManager::getMap() const {
    return map;
}
