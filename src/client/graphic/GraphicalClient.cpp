#include <unistd.h>

#include <iostream>
#include <vector>
#include <map>

#include "clientRun/ClientRun.hpp"
#include "client/graphic/Player.hpp"
#include "client/graphic/ImageClass.hpp"
#include "client/graphic/BackGround.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

static void Event(sf::RenderWindow &window, std::map<int, int> &map,
sf::Event &event) {
    if (event.type == sf::Event::Closed ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        window.close();
    if (event.key.code == sf::Keyboard::Z)
        map[sf::Keyboard::Z] = event.type;
    if (event.key.code == sf::Keyboard::Space)
        map[sf::Keyboard::Space] = event.type;
}

void setMusic(sf::SoundBuffer &music, sf::Sound &sound) {
    if (!music.loadFromFile("assets/theme.ogg"))
        return;
    sound.setBuffer(music);
    sound.play();
    sound.setLoop(true);
}

int graphic(void) {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML window");
    sf::Clock clock;
    std::map<int, int> map_keys = {
        {sf::Keyboard::Z, sf::Event::KeyReleased},
        {sf::Keyboard::Space, sf::Event::KeyReleased}};
    sf::Event event;
    BackGround bg;
    BackGround bg2(1726 * 3.7);
    float deltaTime = 0;
    sf::SoundBuffer music;
    sf::Sound sound;

    setMusic(music, sound);
    while (window.isOpen()) {
        deltaTime = clock.restart().asSeconds();
        while (window.pollEvent(event))
            Event(window, map_keys, event);
        update(map_keys, deltaTime);
        bg.update(deltaTime);
        bg2.update(deltaTime);
        window.clear();
        bg.draw(window);
        bg2.draw(window);
        Player::instance->getImage().draw(window);
        window.display();
    }
    return 0;
}
