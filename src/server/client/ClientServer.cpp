#include <string>

#include "server/client/ClientServer.hpp"
#include "log/Log.hpp"
#include "game/gameConstants.hpp"

ClientServer::clientException::clientException(std::string message) {
    _message = message;
}

ClientServer::clientException::~clientException() {
}

const char *ClientServer::clientException::what() const noexcept {
    return _message.c_str();
}
// ---------------------------- END CLASS THROW ----------------------------

ClientServer::ClientServer(int _id, int _clientFd, std::string _mapPath) :
    id(_id), clientFd(_clientFd), mapPath(_mapPath) {
    Log::info() << "Client " << id << " connected" << std::endl;
    sendOutput("ID " + std::to_string(id));
}

ClientServer::~ClientServer() {
    Log::info() << "Client " << id << " disconnected" << std::endl;
}
