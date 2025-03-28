#include "ImageClass.hpp"

ImageClass::ImageClass(std::string path)
{
    this->texture.loadFromFile(path);
    this->sprite.setTexture(this->texture);
}

void ImageClass::updateAnimation()
{
    if ((this->clock.getElapsedTime().asMilliseconds() / 1000.f) > this->timeAnimation) {
        this->clock.restart();
        this->posRectangle.left += this->sprite.getTextureRect().width;
        if (this->posRectangle.left / this->sprite.getTextureRect().width >= this->nbFrame)
            this->posRectangle.left = 0;
        this->sprite.setTextureRect(this->posRectangle);
    }
}
