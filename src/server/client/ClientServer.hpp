#pragma once

#include <iostream>
#include <exception>
#include <string>

class ClientServer {
 public:
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

 private:
    int id;
    int clientFd;
    std::string mapPath;
};
