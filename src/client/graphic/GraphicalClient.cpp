#include <unistd.h>

#include <iostream>
#include <vector>
#include <map>

#include "clientRun/ClientRun.hpp"
#include "client/graphic/Player.hpp"
#include "client/graphic/ImageClass.hpp"
#include "client/graphic/BackGround.hpp"
#include "client/graphic/game/Game.hpp"
#include "client/graphic/game/Menu.hpp"
#include "client/graphic/window/Window.hpp"
#include "DataManager.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

int graphic(void) {
    Window window;
    Game game;
    Menu menu(DataManager::instance->getId());
    DataManager::GameState lastState = DataManager::MENU;

    while (window.isOpen()) {
        DataManager::instance->mutexState.lock();
        DataManager::GameState state = DataManager::instance->getState();
        DataManager::instance->mutexState.unlock();

        window.updateDeltaTime();
        if (lastState == DataManager::MENU && state == DataManager::GAME)
            game.Start();
        if (state == DataManager::MENU)
            updateMenu(window, menu);
        else if (state == DataManager::GAME)
            updateGame(window, game);
        window.display();
        lastState = state;
    }
    return 0;
}
