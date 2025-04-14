#include <string>

#include "server/client/ClientServer.hpp"
#include "log/Log.hpp"
#include "game/gameConstants.hpp"

// ---------------------------- ClientServer CLASS ----------------------------

ClientServer::clientException::clientException(std::string message) {
    _message = message;
}

ClientServer::clientException::~clientException() {
}

const char *ClientServer::clientException::what() const noexcept {
    return _message.c_str();
}
// ---------------------------- ClientServer CLASS ----------------------------

ClientServer::ClientServer(int _id, int _clientFd, std::string _mapPath) :
    id(_id), clientFd(_clientFd), mapPath(_mapPath), player(_id) {
    Log::info() << "Client " << id << " connected" << std::endl;
    sendOutput("HELLO " + std::to_string(id) + ", " + std::to_string(GRAVITY)
        + ", " + std::to_string(SPEED_HORIZONTAL) + ", "
        + std::to_string(SPEED_JETPACK));
    sendOutput("MAP " + getMapPath());
}

ClientServer::~ClientServer() {
    Log::info() << "Client " << id << " disconnected" << std::endl;
}

// ---------------------------- PLAYER CLASS ----------------------------

ClientServer::Player::Player(int i) :
    id(i), x(100), y(100), velocity_y(0.f),
    coins(0), isFire(false), width(92), height(92) {
}
