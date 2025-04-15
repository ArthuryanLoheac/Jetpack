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
#include "client/graphic/game/Game.hpp"
#include "client/graphic/game/Menu.hpp"
#include "client/graphic/window/Window.hpp"
#include "client/client/Client.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

class Game;
class Menu;
class Window;
class Player;

const int WIDTH = 1280;
const int HEIGHT = 920;

int client_connection(int &sockfd);
void loopClient(int sockfd);
int graphic(int sockfd);
void update(Game &game, Window &window);
void handleCommand(std::string command);
void updateImagePlayer(Player &player);
void handleMaxMin(sf::Vector2f &position);
void updateGame(Window &window, Game &game);
void updateMenu(Window &window, Menu &menu);
