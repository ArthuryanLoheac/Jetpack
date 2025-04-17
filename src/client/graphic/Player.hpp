#pragma once
#include <mutex>

#include "client/graphic/ImageClass.hpp"

class Player {
 public:
    enum Landing {
        LANDING,
        ON_GROUND,
        ON_AIR
    };

    enum Ready {
        NOT_READY,
        READY
    };

    static Player *instance;
    explicit Player(sf::Texture &texturePlayer)
        : img(texturePlayer) {
        img.setRectangle(0, 0, width, height);
        img.setScale(92.f/width, 92.f/height);
        img.setTimeAnimation(0.15f);
        img.setPosition(x, y);
        img.setNbFrame(4);
        if (instance == nullptr)
            instance = this;
    }
    void setPos(float x, float y) {
        this->x = x;
        this->y = y;
    }
    float getX() { return x; }
    float getY() { return y; }
    void setVelocityY(float velocityY) { this->velocityY = velocityY; }
    void setFireLastFrame() { isFireLastFrame = isFire; }
    float getVelocityY() { return velocityY; }
    void setFire(bool isFire) { this->isFire = isFire; }
    bool getFire() { return isFire; }
    bool getFireLastFrame() { return isFireLastFrame; }
    int getWidth() { return width; }
    int getHeight() { return height; }
    ImageClass &getImage() { return img; }
    void setGround(bool isGround) { this->isGround = isGround; }
    bool getGround() { return isGround; }
    void setLanding(Landing landing) { this->landing = landing; }
    Landing getLanding() { return landing; }
    void setId(int id) { this->id = id; }
    int getId() { return id; }
    void setCoins(int coins) { this->coins = coins; }
    int getCoins() { return coins; }
    void setAlive(bool isAlive) { this->isAlive = isAlive; }
    bool getAlive() { return isAlive; }
    std::mutex &getMutexPlayer() { return mutexPlayer; }
    Ready getReady() {
        std::lock_guard<std::mutex> lock(mutexPlayer);
        return ready;
    }
    Ready getReadyLastFrame() {
        std::lock_guard<std::mutex> lock(mutexPlayer);
        return readyLastFrame;
    }
    void setReady(Ready ready) {
        std::lock_guard<std::mutex> lock(mutexPlayer);
        this->ready = ready;
    }
    void setReadyLastFrame() {
        std::lock_guard<std::mutex> lock(mutexPlayer);
        this->readyLastFrame = ready;
    }

 private:
    float x = 100;
    float y = 100;
    int width = 134;
    int height = 134;
    float velocityY = 0.f;
    bool isFire = false;
    bool isFireLastFrame = false;
    bool isGround = false;
    int coins = 0;
    int id = 0;
    bool isAlive = true;
    Ready ready = NOT_READY;
    Ready readyLastFrame = NOT_READY;
    ImageClass img;
    Landing landing = ON_AIR;
    std::mutex mutexPlayer;
};
