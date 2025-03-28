/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** Player
*/

#pragma once

class Player
{
    public:
        static Player *instance;
        Player() { instance = this; }
        void setPos(float x, float y) { this->x = x; this->y = y;}
        float getX() { return x; }
        float getY() { return y; }
        void setVelocityY(float velocityY) { this->velocityY = velocityY; }
        float getVelocityY() { return velocityY; }
        void setFire(bool isFire) { this->isFire = isFire; }
        bool getFire() { return isFire; }
    private:
        float x = 100;
        float y = 100;
        float velocityY = 0.f;
        bool isFire = false;
};