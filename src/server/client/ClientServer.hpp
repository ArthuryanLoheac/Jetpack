#pragma once

#include <iostream>
#include <exception>
#include <string>
#include <vector>

class ClientServer {
 public:
    class Player {
     public:
        explicit Player(int i);

        int id;
        float x;
        float y;
        float velocity_y;
        int coins;
        bool isFire;
        int width;
        int height;
        bool isAlive = true;
        bool isDeadThisFrame = false;
        std::vector<int> coinsEarned;

        bool checkCoinsEarned(int id) {
            for (std::size_t i = 0; i < coinsEarned.size(); i++) {
                if (coinsEarned[i] == id)
                    return true;
            }
            return false;
        }
    };

    class clientException : public std::exception {
     public:
        explicit clientException(std::string message);
        ~clientException();
        const char *what() const noexcept;
     private:
        std::string _message;
    };
    ClientServer(int _id, int _clientFd, std::string mapPath);
    ~ClientServer();
    std::string receiveInput();
    void sendOutput(std::string output);
    std::string getInput(std::string& buffer);
    std::string getMapPath() const { return mapPath; }
    Player &getPlayer() { return player; }

    void handleReady(std::istringstream &iss);
    bool handleInput();
    void handleCommand(std::string command);
    void handleFire(std::istringstream &iss);

    bool ready = false;

 private:
    int id;
    int clientFd;
    std::string mapPath;

    Player player;
};
