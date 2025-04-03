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
    DataManager::instance->setGravity(std::stoi(gravity));
    DataManager::instance->setSpeedX(std::stoi(speedX));
    DataManager::instance->setSpeedJetpack(std::stoi(speedJetpack));
}

static void handlePlayer(std::istringstream& iss, Client client) {
    std::string id;
    std::string x;
    std::string y;
    std::string velocityY;
    std::string coins;
    std::string isFiring;

    std::getline(iss, id, ' ');
    std::getline(iss, x, ' ');
    std::getline(iss, y, ' ');
    std::getline(iss, velocityY, ' ');
    std::getline(iss, coins, ' ');
    std::getline(iss, isFiring, ' ');

    client.setId(std::stoi(id.c_str()));
    client.setX(std::stoi(x.c_str()));
    client.setY(std::stoi(y.c_str()));
    client.setVelocityY(std::stoi(velocityY.c_str()));
    client.setCoins(std::stoi(coins.c_str()));
    client.setFire(std::stoi(isFiring.c_str()));
}

void handleCommand(std::string command, Client client) {
    std::istringstream iss(command);
    std::string commandName;

    if (DataManager::instance->getDebug())
        std::cout << command;
    std::getline(iss, commandName, ' ');
    if (commandName == "HELLO")
        handleHello(iss);
    if (commandName == "PLAYER")
        handlePlayer(iss, client);
}
