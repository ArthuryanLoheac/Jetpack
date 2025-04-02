/*
** EPITECH PROJECT, 2025
** BS
** File description:
** ClientIO
*/
#include <unistd.h>
#include <string>

#include "server/client/Client.hpp"
#include "server/commands/Commands.hpp"
#include "log/Log.hpp"

bool Client::handleInput() {
    std::string input = receiveInput();
    Commands command;

    if (input.empty()) {
        return false;
    }
    Log::info() << "Client " << id << " sent: " << input << std::endl;
    try {
        command.handleReceivingCommand(input, *this);
    } catch (const std::exception& e) {
        Log::error() << "Error handling command: " << e.what() << std::endl;
        return false;
    }
    return true;
}

std::string Client::getInput(std::string& buffer) {
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

std::string Client::receiveInput() {
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

void Client::sendOutput(std::string output) {
    output += "\r\n";
    if (write(clientFd, output.c_str(), output.size()) == -1) {
        throw clientException("Error: write");
    }
}
