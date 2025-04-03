/*
** EPITECH PROJECT, 2025
** BS
** File description:
** ClientIO
*/
#include <unistd.h>
#include <string>

#include "client/client/Client.hpp"
#include "log/Log.hpp"

void Client::sendOutput(std::string output) {
    output += "\r\n";
    if (write(clientFd, output.c_str(), output.size()) == -1) {
        throw clientException("Error: write");
    }
}
