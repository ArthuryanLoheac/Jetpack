#pragma once

#include "client/graphic/BackGround.hpp"

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

class Game {
 private:
   struct Sounds {
      sf::SoundBuffer buff;
      sf::Sound sound;
   };

   BackGround bg;
   BackGround bg2;
   Sounds music;

 public:
   Game();
   void update(float deltaTime);
   void draw(sf::RenderWindow &window);
};
