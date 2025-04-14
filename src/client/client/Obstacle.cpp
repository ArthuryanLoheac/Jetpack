#include "Obstacle.hpp"

Obstacle::Obstacle(float x, float y, TypeObstacle tp)
: x(x), y(y), type(tp), img(DataManager::instance->getTexture("Coins")) {
    if (tp == COIN) {
        img = ImageClass(DataManager::instance->getTexture("Coins"));
        img.setNbFrame(6);
        height = 171;
        width = 191;
        img.setScale(134.f/width/1.5f, 134.f/height/1.5f);
    } else {
        img = ImageClass(DataManager::instance->getTexture("Zapper"));
        img.setNbFrame(4);
        height = 122;
        width = 105;
        img.setScale(134.f/width, 134.f/height);
    }
    img.setRectangle(0, 0, width, height);
    img.setTimeAnimation(0.15f);
}

void Obstacle::update(float dt) {
    x -= DataManager::instance->getSpeedX() * dt;
    img.setPosition(x, y);
    img.updateAnimation();
}

void Obstacle::draw(Window &window) {
    img.draw(window.getWindow());
}

bool Obstacle::cmpObstacles(Obstacle &a, Obstacle &b) {
    return a.x > b.x;
}
