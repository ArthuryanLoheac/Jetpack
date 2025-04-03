#include <iostream>
#include <string>
#include <sstream>

#include "client/graphic/Player.hpp"
#include "client/client/DataManager.hpp"
#include "clientRun/ClientRun.hpp"
#include "client/client/Client.hpp"

static void handleHello(std::istringstream& iss) {
    std::string id;
    std::string gravity;
    std::string speedX;
    std::string speedJetpack;

    std::getline(iss, id, ' ');
    std::getline(iss, gravity, ' ');
    std::getline(iss, speedX, ' ');
    std::getline(iss, speedJetpack, ' ');

    DataManager::instance->setId(std::stoi(id.c_str()));
    Player::instance->setId(std::stoi(id.c_str()));
    DataManager::instance->setGravity(std::stoi(gravity));
    DataManager::instance->setSpeedX(std::stoi(speedX));
    DataManager::instance->setSpeedJetpack(std::stoi(speedJetpack));
}

static bool isIdInList(int id) {
    for (auto &p : DataManager::instance->getPlayers()) {
        if (p.getId() == id)
            return true;
    }
    return false;
}

static void handlePlayer(std::istringstream& iss) {
    std::string idStr, xStr, yStr, velocityYStr, coinsStr, isFireStr;

    std::getline(iss, idStr, ' ');
    std::getline(iss, xStr, ' ');
    std::getline(iss, yStr, ' ');
    std::getline(iss, velocityYStr, ' ');
    std::getline(iss, coinsStr, ' ');
    std::getline(iss, isFireStr, ' ');

    int id = std::stoi(idStr);
    float x = std::stof(xStr);
    float y = std::stof(yStr);
    float velocityY = std::stof(velocityYStr);
    int coins = std::stoi(coinsStr);
    bool isFire = (isFireStr == "1");

    if (!isIdInList(id)) {
        Player newPlayer;
        newPlayer.setId(id);
        newPlayer.setPos(x, y);
        newPlayer.setVelocityY(velocityY);
        newPlayer.setFire(isFire);
        newPlayer.setCoins(coins);
        DataManager::instance->getPlayers().push_back(newPlayer);
    } else {
        for (auto &p : DataManager::instance->getPlayers()) {
            if (p.getId() == id) {
                p.setPos(x, y);
                p.setVelocityY(velocityY);
                p.setFire(isFire);
                p.setCoins(coins);
            }
        }
    }
}

void handleCommand(std::string command) {
    std::istringstream iss(command);
    std::string commandName;

    if (DataManager::instance->getDebug())
        std::cout << command;
    std::getline(iss, commandName, ' ');
    if (commandName == "HELLO")
        handleHello(iss);
    if (commandName == "PLAYER")
        handlePlayer(iss);
}
