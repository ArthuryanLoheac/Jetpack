#include "server/commands/Commands.hpp"
#include "server/client/Client.hpp"

void Commands::handleReceivingCommand(std::string command, Client &client) {
    std::string commandName = command.substr(0, command.find(' '));

    if (receivingCommands.find(commandName) == receivingCommands.end())
        client.sendOutput("501 Not implemented");

    command.erase(0, commandName.length() + 1);
    (this->*receivingCommands[commandName])(command, client);
}

void Commands::receiveREADY(std::string command, Client &client) {
    if (command.empty())
        client.ready = true;
    else
        client.sendOutput("400 Bad request");
}

void Commands::receiveMAP(std::string command, Client &client) {
    if (command.empty())
        client.sendOutput("MAP " + client.getMapPath());
    else
        client.sendOutput("400 Bad request");
}

void Commands::receiveFIRE(std::string command, Client &client) {
    (void)command;
    (void)client;
}
