#include "server/gameSimulation/GameSimulation.hpp"
#include "log/Log.hpp"

GameSimulation::GameSimulation() : gameState(0) {
    Log::info() << "Game simulation initialized" << std::endl;
}

GameSimulation::~GameSimulation() {
    Log::info() << "Game simulation destroyed" << std::endl;
}

void GameSimulation::startGame(std::unordered_map<int, Client> &clients) {
    this->clients = clients;
    gameState = 1;
    Log::info() << "Game started" << std::endl;
    for (auto &client : clients) {
        client.second.sendOutput("START");
    }
}

// TODO(*): Implement the game logic
// return false if game is not finished
// return true if game is finished
bool GameSimulation::updateGame() {
    return false;
}
