#include <string>

#include "client/graphic/ImageClass.hpp"

ImageClass::ImageClass(sf::Texture &text) {
    this->sprite.setTexture(text);
}

void ImageClass::updateAnimation() {
    if ((this->clock.getElapsedTime().asMilliseconds() / 1000.f) >
            this->timeAnimation) {
        this->clock.restart();
        this->posRectangle.left += this->sprite.getTextureRect().width;
        if (this->posRectangle.left / this->sprite.getTextureRect().width >=
                this->nbFrame)
            this->posRectangle.left = 0;
        this->sprite.setTextureRect(this->posRectangle);
    }
}
