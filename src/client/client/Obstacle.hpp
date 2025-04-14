#pragma once

#include "client/graphic/ImageClass.hpp"
#include "DataManager.hpp"
#include "Window.hpp"

class Obstacle {
 public:
    enum TypeObstacle {
        COIN,
        OBSTACLE,
    };
    float x, y;
    TypeObstacle type;
    ImageClass img;
    Obstacle(float x, float y, TypeObstacle tp);
    void update(float dt);
    void draw(Window &window);

    static bool cmpObstacles(Obstacle &a, Obstacle &b);
};
