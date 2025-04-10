#pragma once
#include <string>
#include <vector>
#include <memory>

#include "client/graphic/Player.hpp"

class DataManager {
   public:
      enum GameState {
         MENU,
         GAME
      };
 private:
    int gravity;
    int speed_x;
    int speed_jetpack;
    int my_id;
    bool debug;

    int port;
    std::string ip;
    std::vector<std::unique_ptr<Player>> players;
    sf::Texture texturePlayer;
    sf::Texture textureBackground;
    sf::Texture textureMenu;
    sf::Font font;
    GameState state = MENU;

 public:
    std::mutex mutexState;
    static DataManager *instance;

    DataManager();
    int getGravity() const;
    int getSpeedX() const;
    int getSpeedJetpack() const;
    int getId() const;
    bool getDebug() const;
    int getPort() const;
    std::string getIp() const;
    std::vector<std::unique_ptr<Player>> &getPlayers();
    GameState getState() const;
    sf::Font &getFont();

    void setGravity(int gravity);
    void setSpeedX(int speed);
    void setSpeedJetpack(int speed);
    void setId(int id);
    void setDebug(bool isDebug);
    void setPort(int port);
    void setIp(std::string ip);
    void setState(GameState state);

    sf::Texture &getTexturePlayer();
    sf::Texture &getTextureBackground();
    sf::Texture &getTextureMenu();
    Player &addNewPlayer();
};
