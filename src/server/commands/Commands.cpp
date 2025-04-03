#include "server/commands/Commands.hpp"

Commands::Commands() {
    receivingCommandFactory();
    sendingCommandFactory();
}

Commands::~Commands() {
}

void Commands::receivingCommandFactory() {
    receivingCommands["READY"] = &Commands::receiveREADY;
    receivingCommands["MAP"] = &Commands::receiveMAP;
    receivingCommands["FIRE"] = &Commands::receiveFIRE;
}

void Commands::sendingCommandFactory() {
}
