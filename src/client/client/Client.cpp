#include <string>

#include "client/client/Client.hpp"
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
    clientFd(_clientFd), mapPath(_mapPath) {
    self.id = _id;
    Log::info() << "Client " << self.id << " connected" << std::endl;
    sendOutput("ID " + std::to_string(self.id));
}

Client::~Client() {
    Log::info() << "Client " << self.id << " disconnected" << std::endl;
}

void Client::setId(int id) {
    self.id = id;
}

void Client::setX(float x) {
    self.x = x;
}

void Client::setY(float y) {
    self.y = y;
}

void Client::setCoins(int coins) {
    self.coins = coins;
}

void Client::setVelocityY(float velocity_y) {
    self.velocity_y = velocity_y;
}

void Client::setFire(bool fire) {
    self.isFire = fire;
}

int Client::getId() const {
    return self.id;
}

float Client::getX() const {
    return self.x;
}

float Client::getY() const {
    return self.y;
}

int Client::getCoins() const {
    return self.coins;
}

float Client::getVelocityY() const {
    return self.velocity_y;
}

bool Client::getFire() const {
    return self.isFire;
}
