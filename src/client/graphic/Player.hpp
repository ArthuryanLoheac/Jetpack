/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** Player
*/

#pragma once
#include "client/graphic/ImageClass.hpp"

class Player {
 public:
    enum Landing {
        LANDING,
        ON_GROUND,
        ON_AIR
    };

    static Player *instance;
    Player()
        : img("assets/player_sprite_sheet.png") {
        img.setRectangle(0, 0, width, height);
        img.setTimeAnimation(0.15f);
        img.setPosition(x, y);
        img.setNbFrame(4);
        if (instance == nullptr)
            instance = this;
    }
    void setPos(float x, float y) { this->x = x; this->y = y;}
    float getX() { return x; }
    float getY() { return y; }
    void setVelocityY(float velocityY) { this->velocityY = velocityY; }
    float getVelocityY() { return velocityY; }
    void setFire(bool isFire) { this->isFire = isFire; }
    bool getFire() { return isFire; }
    int getWidth() { return width; }
    int getHeight() { return height; }
    ImageClass &getImage() { return img; }
    void setGround(bool isGround) { this->isGround = isGround; }
    bool getGround() { return isGround; }
    void setLanding(Landing landing) { this->landing = landing; }
    Landing getLanding() { return landing; }
    void setId(int id) { this->id = id; }
    int getId() { return id; }

 private:
    float x = 100;
    float y = 100;
    int width = 134;
    int height = 134;
    float velocityY = 0.f;
    bool isFire = false;
    bool isGround = false;
    int id;
    ImageClass img;
    Landing landing = ON_AIR;
};
