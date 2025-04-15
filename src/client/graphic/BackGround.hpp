#pragma once
#include "client/graphic/ImageClass.hpp"

class BackGround {
 private:
    ImageClass img;
    sf::Vector2f pos = {0, -160};
    float speed = 500;

 public:
    BackGround(sf::Texture &texture, int s, int posX = 0)
    : img(texture) {
        pos.x = posX;
        img.setPosition(posX, pos.y);
        img.setScale(3.7, 3.7);
        img.setRectangle(0, 0, 1726, 341);
        speed = s;
    }
    void update(float deltaTime) {
        pos.x -= speed * deltaTime;
        img.setPosition(pos.x, pos.y);
        if (pos.x <= -1726 * 3.7)
            pos.x = 1726 * 3.7;
    }
    void draw(sf::RenderWindow &window) {
        window.draw(img.getSprite());
    }
    sf::Vector2f getPos() { return pos; }
    void setPos(sf::Vector2f pos) { this->pos = pos; }
};
