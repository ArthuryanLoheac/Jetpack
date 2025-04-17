#include "Player.hpp"
#include "DataManager.hpp"

void Player::setId(int id){
    this->id = id;
    txtDisconnect.setFont(DataManager::instance->getFont());
    txtDisconnect.setString("Player " + std::to_string(this->id) + " disconnected");
}