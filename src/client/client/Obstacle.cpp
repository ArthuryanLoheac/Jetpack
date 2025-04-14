#include "Obstacle.hpp"

Obstacle::Obstacle(float x, float y, TypeObstacle tp)
: x(x), y(y), type(tp), img(DataManager::instance->getTexture("Coins")) {
    if (tp == COIN) {
        img = ImageClass(DataManager::instance->getTexture("Coins"));
    } else {
        img = ImageClass(DataManager::instance->getTexture("Zapper"));
    }
}

void Obstacle::update(float dt) {
    x -= DataManager::instance->getSpeedX() * dt;
    img.setPosition(x, y);
}

void Obstacle::draw(Window &window) {
    img.draw(window.getWindow());
}

bool Obstacle::cmpObstacles(Obstacle &a, Obstacle &b) {
    return a.x > b.x;
}
