#include "Window.hpp"

Window::Window()
: window(sf::VideoMode(WIDTH, HEIGHT), "JetPack Joyride") {
    window.clear();
    window.display();
    deltaTime = 0;
    map_keys = {
        {sf::Keyboard::Z, sf::Event::KeyReleased},
        {sf::Keyboard::Space, sf::Event::KeyReleased}};
}

void Window::updateDeltaTime() {
    deltaTime = clock.restart().asSeconds();
    for (auto &key : map_keys)
        map_keysLastFrame[key.first] = key.second;
}
