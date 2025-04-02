#pragma once

#include <iostream>
#include <exception>
#include <string>

class Client {
 public:
    class clientException : public std::exception {
     public:
        clientException(std::string message);
        ~clientException();
        const char *what() const noexcept;
     private:
        std::string _message;
    };
    
    Client(int _id, int _clientFd, std::string mapPath);
    ~Client();
    std::string receiveInput();
    bool handleInput();
    void sendOutput(std::string output);
    std::string getInput(std::string& buffer);

    struct Player {
        int id;
        float x;
        float y;
        float velocity_y;
        int coins;
        bool isFire;
    };

 protected:
 private:
    int clientFd;
    std::string mapPath;
    Player self;
    Player opponent;
};
