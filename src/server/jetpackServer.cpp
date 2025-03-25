/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** jetpackServer
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include "Log.hpp"
#include "server/Server.hpp"

static int printHelp(int exitCode)
{
    std::cout << "USAGE: ./jetpackServer -p <port> -m <map> [-d]" << std::endl;
    std::cout << "\tport\tport number on which the server socket listens"
        << std::endl;
    std::cout << "\tmap\tpath to the file containing the map" << std::endl;
    std::cout << "\t-d (debug)\tdisplay the server's debug output" << std::endl;
    return exitCode;
}

static int getPort(const std::string &portStr)
{
    int port = -1;

    if (portStr.empty() || !std::all_of(portStr.begin(), portStr.end(),
        ::isdigit)) {
        std::cerr << "Invalid port number" << std::endl;
        return -1;
    }
    try {
        port = std::stoi(portStr);
    } catch (std::exception &e) {
        std::cerr << "Invalid port number" << std::endl;
        return -1;
    }
    if (port < 0 || port > 65535)
        return -1;
    return port;
}

static std::string getMap(const std::string pathMap)
{
    std::ifstream file(pathMap);
    std::string map = "";

    if (!file.is_open()) {
        std::cerr << "Invalid map file" << std::endl;
        return "";
    }
    for (std::string line; std::getline(file, line);)
        map += line + "\n";
    file.close();
    return map;
}

static bool handleArgs(int argc, char **argv, int &port, std::string &map)
{
    for (int i = 0; i < argc; i++) {
        if (std::string(argv[i]) == "-p" && i + 1 < argc) {
            port = getPort(argv[i + 1]);
            i++;
        } else if (std::string(argv[i]) == "-m" && i + 1 < argc) {
            map = getMap(argv[i + 1]);
            i++;
        } else if (std::string(argv[i]) == "-d") {
            Log::setDebug(true);
        } else
            return false;
    }
    return true;
}

static int runServer(int port, std::string map)
{
    Server server(port, map);

    try {
        server.setupServerSocket(port);
    } catch (Server::ftpException &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    server.run();
    return 0;
}

int entrypointServer(int argc, char **argv)
{
    std::string map = "";
    int port = -1;

    if (!handleArgs(argc - 1, argv + 1, port, map))
        return printHelp(84);
    if (port == -1 || map == "")
        return 84;
    std::cout << "Starting server on port " << port << std::endl;
    return runServer(port, map);
}