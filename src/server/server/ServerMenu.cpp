#include "server/server/Server.hpp"
#include "game/gameConstants.hpp"

void Server::sendReadyDataToEachClient(ClientServer &player) {
    for (auto &otherClient : clients) {
        player.sendOutput("READY " +
            std::to_string(otherClient.second.getPlayer().id) + " " +
            std::to_string(otherClient.second.ready));
    }
}

bool Server::updateMenu() {
    bool everyoneReady = true;
    if (clients.size() == 0)
        everyoneReady = false;
    deltaTime = clock.restart().asSeconds();
    for (auto &client : clients) {
        sendReadyDataToEachClient(client.second);
        if (!client.second.ready)
            everyoneReady = false;
    }
    if (everyoneReady) {
        state = GAME;
        for (auto &client : clients)
            client.second.sendOutput("START ");
    }
    return false;
}
