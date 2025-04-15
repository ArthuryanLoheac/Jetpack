#pragma once

#include "client/graphic/ImageClass.hpp"
#include "client/DataManager.hpp"
#include "client/graphic/window/Window.hpp"

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
 private:
    int width = 92;
    int height = 92;
};
