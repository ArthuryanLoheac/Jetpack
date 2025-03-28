/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** Client
*/

#pragma once
#include "entrypoint.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>
#include <vector>
#include <netdb.h>
#include <stdio.h>
#include <fcntl.h>
#include <sstream>
#include <map>
#include <signal.h>
#include <thread>
#include "ImageClass.hpp"

const int WIDTH = 1280;
const int HEIGHT = 920;

int client(int port, std::string ip);
int graphic(void);
void update(std::map<int, int> &map_keys, float deltaTime);