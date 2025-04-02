#pragma once
#include <map>
#include <string>

#include "clientRun/ClientRun.hpp"
#include "client/graphic/Player.hpp"
#include "client/graphic/ImageClass.hpp"
#include "client/graphic/BackGround.hpp"
#include "client/graphic/game/Game.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

class Window {
    private:
        sf::Clock clock;
        std::map<int, int> map_keys;
        sf::Event event;
        float deltaTime;
        sf::RenderWindow window;

    public:
        Window();
        sf::RenderWindow &getWindow() { return window; }
        sf::Event &getEvent() { return event; }
        sf::Clock &getClock() { return clock; }
        float getDeltaTime() { return deltaTime; }
        std::map<int, int> &getMapKeys() { return map_keys; }
        bool isOpen() { return window.isOpen(); }
        void updateDeltaTime();
        bool pollEvent() { return window.pollEvent(event); }
        void clear() { window.clear(); }
        void display() { window.display(); }
};
