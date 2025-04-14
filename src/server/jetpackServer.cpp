#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>

#include "log/Log.hpp"
#include "server/Server.hpp"

static int printHelp(int exitCode) {
    std::cout << "USAGE: ./jetpackServer -p <port> -m <map> [-d]" << std::endl;
    std::cout << "\tport\tport number on which the server socket listens"
        << std::endl;
    std::cout << "\tmap\tpath to the file containing the map" << std::endl;
    std::cout << "\t-d (debug)\tdisplay the server's debug output" << std::endl;
    return exitCode;
}

static int getPort(const std::string &portStr) {
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

static std::string getMap(const std::string pathMap) {
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

static bool handleArgs(int argc, char **argv, int &port, std::string &map) {
    for (int i = 0; i < argc; i++) {
        if (std::string(argv[i]) == "-p" && i + 1 < argc) {
            port = getPort(argv[i + 1]);
            i++;
        } else if (std::string(argv[i]) == "-m" && i + 1 < argc) {
            map = getMap(argv[i + 1]);
            i++;
        } else if (std::string(argv[i]) == "-d") {
            Log::setDebug(true);
        } else {
            return false;
        }
    }
    return true;
}

static int runServer(int port, std::string map) {
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

static bool checkMapFormat(const std::string &map) {
    int globalLength = 0;
    int currentLength = 0;
    int lineNumber = 0;
    if (map.empty()) {
        std::cerr << "Invalid map format (map is empty)" << std::endl;
        return false;
    }
    for (char c : map) {
        if (c != '_' && c != 'e' && c != 'c' && c != '\n') {
            std::cerr << "Invalid map format (invalid character: " << c
                << ")" << std::endl;
            return false;
        }
        if (c == '\n') {
            if (globalLength == 0) {
                globalLength = currentLength;
            } else if (currentLength != globalLength) {
                std::cerr << "Invalid map format (inconsistent line length)"
                    << std::endl;
                return false;
            }
            lineNumber++;
            currentLength = 0;
        } else {
            currentLength++;
        }
    }
    if (lineNumber != 10) {
        std::cerr << "Invalid map format (invalid number of lines: "
            << lineNumber << ")" << std::endl;
        return false;
    }
    return true;
}

int entrypointServer(int argc, char **argv) {
    std::string map = "";
    int port = -1;

    if (!handleArgs(argc - 1, argv + 1, port, map))
        return printHelp(84);
    if (port == -1 || !checkMapFormat(map))
        return 84;
    std::cout << "Starting server on port " << port << std::endl;
    return runServer(port, map);
}
