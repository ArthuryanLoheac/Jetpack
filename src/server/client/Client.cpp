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

Client::Player::Player() :
    id(0), x(0), y(0), velocity_y(0), coins(0), isFire(false) {
}

Client::Client(int _id, int _clientFd, std::string _mapPath) :
    clientFd(_clientFd), mapPath(_mapPath) {
    self.id = _id; // Assign playerNumber in self to _id
    Log::info() << "Client " << self.id << " connected" << std::endl;
    sendOutput("ID " + std::to_string(self.id));
}

Client::~Client() {
    Log::info() << "Client " << self.id << " disconnected" << std::endl;
}


