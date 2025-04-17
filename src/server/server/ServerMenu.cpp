#include "server/server/Server.hpp"
#include "game/gameConstants.hpp"
#include "log/Log.hpp"

void Server::sendReadyDataToEachClient(ClientServer &player) {
    for (auto &otherClient : clients) {
        try {
            player.sendOutput("READY " +
                std::to_string(otherClient.second.getPlayer().id) + " " +
                std::to_string(otherClient.second.ready));
        } catch (const std::exception &e) {
            Log::error() << "Error sending ready data to client: "
                << e.what() << std::endl;
        }
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
