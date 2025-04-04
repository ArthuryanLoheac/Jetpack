#pragma once
#include <string>
#include <vector>

#include "client/graphic/Player.hpp"
#include <memory>

class DataManager {
 private:
    int gravity;
    int speed_x;
    int speed_jetpack;
    int my_id;
    bool debug;

    int port;
    std::string ip;
    std::vector<Player> players;
    sf::Texture texturePlayer;
    sf::Texture textureBackground;

 public:
    static DataManager *instance;

    DataManager();
    int getGravity() const;
    int getSpeedX() const;
    int getSpeedJetpack() const;
    int getId() const;
    bool getDebug() const;
    int getPort() const;
    std::string getIp() const;
    std::vector<Player> &getPlayers();
    Player &addNewPlayer();

    void setGravity(int gravity);
    void setSpeedX(int speed);
    void setSpeedJetpack(int speed);
    void setId(int id);
    void setDebug(bool isDebug);
    void setPort(int port);
    void setIp(std::string ip);

    sf::Texture &getTexturePlayer();
    sf::Texture &getTextureBackground();
};
