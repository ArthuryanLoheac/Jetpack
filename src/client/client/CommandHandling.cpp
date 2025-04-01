#include <iostream>
#include <string>

#include "client/graphic/Player.hpp"
#include "client/client/DataManager.hpp"
#include "clientRun/ClientRun.hpp"

void handleCommand(std::string command) {
    if (DataManager::instance->getDebug())
        std::cout << command;
}
