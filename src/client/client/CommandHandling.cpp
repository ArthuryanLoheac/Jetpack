#include <iostream>
#include <string>
#include <sstream>
#include <memory>
#include <vector>

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
    for (const auto &p : DataManager::instance->getPlayers()) {
        if (p->getId() == id)
            return true;
    }
    return false;
}

static void handlePlayer(std::istringstream& iss) {
    if (DataManager::instance->getState() == DataManager::MENU)
        DataManager::instance->setState(DataManager::GAME);
    std::string idStr, xStr, yStr, velocityYStr, coinsStr, isFireStr;

    std::getline(iss, idStr, ' ');
    std::getline(iss, xStr, ' ');
    std::getline(iss, yStr, ' ');
    std::getline(iss, velocityYStr, ' ');
    std::getline(iss, coinsStr, ' ');
    std::getline(iss, isFireStr, ' ');

    try {
        int id = std::stoi(idStr);
        float x = std::stof(xStr);
        float y = std::stof(yStr);
        float velocityY = std::stof(velocityYStr);
        int coins = std::stoi(coinsStr);
        bool isFire = std::stoi(isFireStr) == 1;

        if (!isIdInList(id)) {
            Player &newPlayer = DataManager::instance->addNewPlayer();
            std::lock_guard<std::mutex> lock(newPlayer.getMutexPlayer());
            newPlayer.setId(id);
            newPlayer.setPos(x, y);
            newPlayer.setVelocityY(velocityY);
            newPlayer.setFire(isFire);
            newPlayer.setCoins(coins);
            newPlayer.setTimeDisconnect(3.f);
            newPlayer.setIsDisconnected(false);
            newPlayer.setTimeDrawDisconnected(2.f);
        } else {
            for (const auto &p : DataManager::instance->getPlayers()) {
                if (p->getId() == id) {
                    std::lock_guard<std::mutex> lock(p->getMutexPlayer());
                    p->setPos(x, y);
                    p->setVelocityY(velocityY);
                    p->setFire(isFire);
                    p->setCoins(coins);
                    p->setTimeDisconnect(3.f);
                    p->setIsDisconnected(false);
                    p->setTimeDrawDisconnected(2.f);
                }
            }
        }
    } catch (std::exception &e) {}
}

static void handleReady(std::istringstream& iss) {
    std::string idStr, isReady;

    std::getline(iss, idStr, ' ');
    std::getline(iss, isReady, ' ');

    int id = std::stoi(idStr);
    Player::Ready ready = (std::stoi(isReady) == 1) ?
        Player::READY : Player::NOT_READY;

    if (!isIdInList(id)) {
        Player &newPlayer = DataManager::instance->addNewPlayer();
        newPlayer.setId(id);
        newPlayer.setReady(ready);
    } else {
        for (const auto &p : DataManager::instance->getPlayers()) {
            if (p->getId() == id && p->getId() != Player::instance->getId()) {
                p->setReady(ready);
            }
        }
    }
}

static void handleDeath(std::istringstream& iss) {
    std::string idStr;
    std::getline(iss, idStr, ' ');

    int id = std::stoi(idStr);

    for (const auto &p : DataManager::instance->getPlayers()) {
        if (p->getId() == id) {
            std::lock_guard<std::mutex> lock(p->getMutexPlayer());
            p->setAlive(false);
            break;
        }
    }
}

void handleStart() {
    DataManager::instance->mutexState.lock();
    DataManager::instance->setState(DataManager::GAME);
    DataManager::instance->mutexState.unlock();
}

void handleMap(std::istringstream& iss) {
    std::string mapLine;
    std::vector<std::string> mapPath;
    while (std::getline(iss, mapLine))
        mapPath.push_back(mapLine);
    DataManager::instance->setMap(mapPath);
}

void handleFinish(std::istringstream& iss) {
    std::string id;

    while (std::getline(iss, id, ' ')) {
        try {
            DataManager::instance->getIdWinners().push_back(std::atoi(id.c_str()));
        } catch (std::exception &e) {}
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
    else if (commandName == "PLAYER")
        handlePlayer(iss);
    else if (commandName == "START")
        handleStart();
    else if (commandName == "READY")
        handleReady(iss);
    else if (commandName == "MAP")
        handleMap(iss);
    else if (commandName == "DEATH")
        handleDeath(iss);
    else if (commandName == "FINISH")
        handleFinish(iss);
}
