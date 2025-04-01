#include <string>

#include "server/client/Client.hpp"
#include "log/Log.hpp"
#include "game/gameConstants.hpp"

Client::clientException::clientException(std::string message) {
    _message = message;
}

Client::clientException::~clientException() {
}

const char *Client::clientException::what() const noexcept {
    return _message.c_str();
}

// ---------------------------- END CLASS THROW ----------------------------

Client::Client(int _id, int _clientFd, std::string _mapPath) :
    id(_id), clientFd(_clientFd), mapPath(_mapPath) {
    Log::info() << "Client " << id << " connected" << std::endl;
    sendOutput("HELLO (" + std::to_string(id) + ", " + std::to_string(GRAVITY)
        + ", " + std::to_string(SPEED_HORIZONTAL) + ", "
        + std::to_string(SPEED_JETPACK) + ")");
}

Client::~Client() {
    Log::info() << "Client " << id << " disconnected" << std::endl;
}


