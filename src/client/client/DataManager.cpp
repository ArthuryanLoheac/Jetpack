#include <string>
#include <vector>
#include <memory>

#include "client/client/DataManager.hpp"

DataManager* DataManager::instance = nullptr;

DataManager::DataManager() {
    if (instance)
        return;
    instance = this;
    texturePlayer.loadFromFile("assets/player_sprite_sheet.png");
    textureBackground.loadFromFile("assets/background.png");
    textureMenu.loadFromFile("assets/menu.jpg");
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

Player &DataManager::addNewPlayer() {
    players.emplace_back(std::make_unique<Player>(texturePlayer));
    return *players.back();
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

sf::Texture &DataManager::getTexturePlayer() {
    return texturePlayer;
}

sf::Texture &DataManager::getTextureBackground() {
    return textureBackground;
}

void DataManager::setState(GameState state) {
    this->state = state;
}

sf::Texture &DataManager::getTextureMenu() {
    return textureMenu;
}

sf::Font &DataManager::getFont() {
    return font;
}
