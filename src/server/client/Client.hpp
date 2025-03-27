/*
** EPITECH PROJECT, 2025
** BS
** File description:
** Client
*/

#pragma once

#include <iostream>
#include <exception>

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
    protected:
    private:
        int id;
        int clientFd;
        std::string mapPath;
};
