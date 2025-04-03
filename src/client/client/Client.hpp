#pragma once

#include <iostream>
#include <exception>
#include <string>

class Client {
 public:
    class clientException : public std::exception {
     public:
        explicit clientException(std::string message);
        ~clientException();
        const char *what() const noexcept;
     private:
        std::string _message;
    };

    Client(int _id, int _clientFd, std::string mapPath);
    Client(const Client &other);
    ~Client();

    void sendOutput(std::string output);
    struct Player {
        int id;
        float x;
        float y;
        float velocity_y;
        int coins;
        bool isFire;
    };
    void setId(int id);
    void setX(float x);
    void setY(float y);
    void setCoins(int coins);
    void setVelocityY(float velocity_y);
    void setFire(bool fire);
    int getId() const;
    float getX() const;
    float getY() const;
    int getCoins() const;
    float getVelocityY() const;
    bool getFire() const;

 private:
    int clientFd;
    std::string mapPath;
    Player self;
    Player opponent;
};
