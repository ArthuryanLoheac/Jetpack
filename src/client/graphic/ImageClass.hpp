#pragma once
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class ImageClass {
 public:
    explicit ImageClass(std::string path);
    sf::Sprite getSprite() { return sprite; }
    void draw(sf::RenderWindow &window) { window.draw(sprite); }
    void setRectangle(int x, int y, int width, int height) {
        posRectangle = sf::IntRect(x, y, width, height);
        sprite.setTextureRect(posRectangle);
    }
    void setPosition(int x, int y) { sprite.setPosition(x, y); }
    void setScale(float x, float y) { sprite.setScale(x, y); }
    void setOrigin(float x, float y) { sprite.setOrigin(x, y); }
    void setRotation(float angle) { sprite.setRotation(angle); }
    void setTimeAnimation(float time) { timeAnimation = time; }
    sf::Clock &getClock() { return clock; }
    float getTimeAnimation() { return timeAnimation; }
    void updateAnimation();
    void setNbFrame(int nbFrame) { this->nbFrame = nbFrame; }
    sf::IntRect &getPosRectangle() { return posRectangle; }
    int getNbFrame() { return nbFrame; }

 private:
    sf::Texture texture;
    sf::Sprite sprite;
    float timeAnimation;
    sf::Clock clock;

    sf::IntRect posRectangle;
    int nbFrame;
};
