#pragma once

#include <unordered_map>
#include <string>

class Client;

class Commands {
 public:
    Commands();
    ~Commands();
    void handleReceivingCommand(std::string command, Client &client);

 protected:
 private:
    using CommandFunction = void (Commands::*)(std::string, Client &);

    std::unordered_map<std::string, CommandFunction> receivingCommands;
    std::unordered_map<std::string, CommandFunction> sendingCommands;

    void receivingCommandFactory();
    void sendingCommandFactory();

    void receiveREADY(std::string command, Client &client);
    void receiveMAP(std::string command, Client &client);
    void receiveFIRE(std::string command, Client &client);
};
