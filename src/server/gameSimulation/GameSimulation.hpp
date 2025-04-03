/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** GameSimulation
*/

#pragma once

#include <unordered_map>
#include <string>

#include "server/client/ClientServer.hpp"

class GameSimulation {
 public:
    GameSimulation();
    ~GameSimulation();
    void startGame(std::unordered_map<int, ClientServer> &clients);
    bool updateGame();

 protected:
 private:
    int gameState;
    std::unordered_map<int, ClientServer> clients;
};
