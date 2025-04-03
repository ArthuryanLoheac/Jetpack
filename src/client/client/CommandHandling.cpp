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

static void handlePlayer(std::istringstream& iss) {
    printf("Player\n");
    (void)iss;
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
