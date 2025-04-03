#pragma once

#include <unordered_map>
#include <string>

#include "server/client/ClientServer.hpp"

class Client;

class Commands {
 public:
    Commands();
    ~Commands();
    void handleReceivingCommand(std::string command, ClientServer &client);

 protected:
 private:
    using CommandFunction = void (Commands::*)(std::string, ClientServer &);

    std::unordered_map<std::string, CommandFunction> receivingCommands;
    std::unordered_map<std::string, CommandFunction> sendingCommands;

    void receivingCommandFactory();
    void sendingCommandFactory();

    void receiveREADY(std::string command, ClientServer &client);
    void receiveMAP(std::string command, ClientServer &client);
    void receiveFIRE(std::string command, ClientServer &client);
};
