/*
** EPITECH PROJECT, 2025
** Test
** File description:
** main
*/

#include "Client.hpp"
#include "Player.hpp"

Player *Player::instance = nullptr;

int main (int ac, char **av)
{
    Player player;
    std::thread t1(graphic);
    std::thread t2(client, ac, av);
    t1.join();
    t2.detach();

    return 0;
}
