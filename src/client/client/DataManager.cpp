#include <string>

#include "client/client/DataManager.hpp"
#include "DataManager.hpp"

DataManager* DataManager::instance = nullptr;

DataManager::DataManager() {
    if (instance)
        return;
    instance = this;
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

std::vector<Player> &DataManager::getPlayers() {
    return players;
}

void DataManager::setGravity(int gravity)
{
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
