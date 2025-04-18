#include "client/graphic/Player.hpp"
#include "client/client/DataManager.hpp"

void Player::setId(int id) {
    this->id = id;
    txtDisconnect.setFont(DataManager::instance->getFont());
    txtDisconnect.setString("Player " + std::to_string(this->id) +
        " disconnected");
    nametxt.setFont(DataManager::instance->getFont());
    nametxt.setString("P " + std::to_string(this->id));
}
