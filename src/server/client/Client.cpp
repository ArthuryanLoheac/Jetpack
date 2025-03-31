#include <string>

#include "server/client/Client.hpp"
#include "log/Log.hpp"

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
    sendOutput("ID " + std::to_string(id));
}

Client::~Client() {
    Log::info() << "Client " << id << " disconnected" << std::endl;
}


