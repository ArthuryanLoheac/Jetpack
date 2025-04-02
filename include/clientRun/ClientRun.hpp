#pragma once
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>
#include <netdb.h>
#include <stdio.h>
#include <fcntl.h>
#include <signal.h>

#include <iostream>
#include <vector>
#include <sstream>
#include <map>
#include <thread>
#include <string>

#include "client/graphic/ImageClass.hpp"
#include "entryPoint/entrypoint.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

const int WIDTH = 1280;
const int HEIGHT = 920;

int client_connection(int &sockfd);
void loopClient(int sockfd);
int graphic(void);
void update(std::map<int, int> &map_keys, float deltaTime);
void handleCommand(std::string command);
