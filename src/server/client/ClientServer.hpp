#pragma once

#include <iostream>
#include <exception>
#include <string>

class ClientServer {
 public:
    class Player {
     public:
        Player();

        int id;
        float x;
        float y;
        float velocity_y;
        int coins;
        bool isFire;
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
    bool handleInput();
    void sendOutput(std::string output);
    std::string getInput(std::string& buffer);
    std::string getMapPath() const { return mapPath; }

    bool ready;
 private:
    int id;
    int clientFd;
    std::string mapPath;

    Player player;
};
