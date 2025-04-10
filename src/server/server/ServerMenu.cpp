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
    deltaTime = clock.restart().asSeconds();
    for (auto &client : clients) {
        sendReadyDataToEachClient(client.second);
    }
    return false;
}
