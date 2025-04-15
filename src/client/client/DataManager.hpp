#pragma once
#include <string>
#include <vector>
#include <memory>
#include <queue>
#include <map>

#include "client/graphic/Player.hpp"
#include "client/client/Obstacle.hpp"

class Obstacle;
class Window;

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
    std::map<std::string, sf::Texture> textures;
    sf::Font font;
    GameState state = MENU;

    std::vector<std::string> map;
    std::vector<Obstacle> obstacles;

 public:
    std::mutex mutexState;
    static DataManager *instance;
    bool running;

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
    std::vector<std::string> getMap() const;

    void setGravity(int gravity);
    void setSpeedX(int speed);
    void setSpeedJetpack(int speed);
    void setId(int id);
    void setDebug(bool isDebug);
    void setPort(int port);
    void setIp(std::string ip);
    void setState(GameState state);
    void setMap(std::vector<std::string> map);

    sf::Texture &getTexture(std::string x);
    Player &addNewPlayer();

    void updateMap(float dt);
    void drawMap(Window &window);
};
