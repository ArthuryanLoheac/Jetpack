#pragma once
#include <string>

#include "client/graphic/ImageClass.hpp"

class Obstacle {
 public:
    enum TypeObstacle {
        COIN,
        BOMB
    };

    explicit Obstacle(int id, int x, int y, TypeObstacle type)
        : id(id), rect(x, y, 134, 134), type(type) {}
    void setId(int id) { this->id = id; }
    int getId() { return id; }
    void setRect(int x, int y);
    sf::Rect<float> getRect() const { return rect; }
    sf::Rect<float> &getRectRef() { return rect; }
    void setType(TypeObstacle type) { this->type = type; }
    TypeObstacle getType() { return type; }
    static bool cmpObstacle(const Obstacle &a, const Obstacle &b) {
        return a.getRect().left < b.getRect().left;
    }

 private:
    int id;
    sf::Rect<float> rect;
    TypeObstacle type;
};
