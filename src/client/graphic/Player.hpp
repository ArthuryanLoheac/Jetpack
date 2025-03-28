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
        float x = 100;
        float y = 100;
        void setPos(float x, float y) { this->x = x; this->y = y;}
        float getX() { return x; }
        float getY() { return y; }
};