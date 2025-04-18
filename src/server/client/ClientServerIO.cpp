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

void ClientServer::handleFire(std::istringstream &iss) {
    std::string isFiring;

    std::getline(iss, isFiring, ' ');
    if (isFiring == "1")
        player.isFire = true;
    else
        player.isFire = false;
}

void ClientServer::handleReady(std::istringstream &iss) {
    std::string isReady;

    std::getline(iss, isReady, ' ');
    if (isReady == "1")
        ready = true;
    else
        ready = false;
}

void ClientServer::handleCommand(std::string command) {
    std::istringstream iss(command);
    std::string commandName;

    std::getline(iss, commandName, ' ');
    if (commandName == "FIRE") {
        sendOutput("200 ok");
        handleFire(iss);
    } else if (commandName == "READY") {
        sendOutput("200 ok");
        handleReady(iss);
    } else if (commandName == "BYE") {
        sendOutput("200 ok");
        throw clientException("Client disconnected");
    } else {
        sendOutput("501 Not implemented");
    }
}

bool ClientServer::handleInput() {
    std::string input = receiveInput();

    if (input.empty())
        return false;
    Log::info() << "Client " << id << " sent: " << input << std::endl;
    handleCommand(input);
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
