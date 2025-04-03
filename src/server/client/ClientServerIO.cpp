/*
** EPITECH PROJECT, 2025
** BS
** File description:
** ClientIO
*/
#include <unistd.h>
#include <string>

#include "server/client/ClientServer.hpp"
#include "log/Log.hpp"

bool ClientServer::handleInput() {
    std::string input = receiveInput();

    if (input.empty()) {
        return false;
    }
    Log::info() << "Client " << id << " sent: " << input << std::endl;
    return true;
}

std::string ClientServer::getInput(std::string& buffer) {
    size_t lineEnd = buffer.find("\r\n");
    std::string input;

    if (lineEnd != std::string::npos) {
        input = buffer.substr(0, lineEnd);
        buffer.erase(0, lineEnd + 2);
        return input;
    }
    lineEnd = buffer.find('\n');
    if (lineEnd != std::string::npos) {
        input = buffer.substr(0, lineEnd);
        if (lineEnd > 0 && input[lineEnd - 1] == '\r')
            input.pop_back();
        buffer.erase(0, lineEnd + 1);
        return input;
    }
    return "";
}

std::string ClientServer::receiveInput() {
    char buffer[1024];
    std::string inputBuffer;
    ssize_t readSize;
    std::string input;

    while (true) {
        readSize = read(clientFd, buffer, 1024);
        if (readSize == -1)
            throw clientException("Error: read");
        if (readSize == 0)
            throw clientException("Client disconnected");
        inputBuffer.append(buffer, readSize);
        input = getInput(inputBuffer);
        if (!input.empty()) {
            break;
        }
    }
    return input;
}

void ClientServer::sendOutput(std::string output) {
    output += "\r\n";
    if (write(clientFd, output.c_str(), output.size()) == -1) {
        throw clientException("Error: write");
    }
}
