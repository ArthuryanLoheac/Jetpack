/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** Update
*/
#include <map>

#include "clientRun/ClientRun.hpp"
#include "client/graphic/Player.hpp"
#include "client/graphic/ImageClass.hpp"
#include "client/client/DataManager.hpp"
#include "client/graphic/game/Game.hpp"
#include "client/graphic/window/Window.hpp"

void handleMaxMin(sf::Vector2f &position) {
    bool isGround = false;
    if (position.y >= HEIGHT - 92) {
        position.y = HEIGHT - 92;
        Player::instance->setVelocityY(0);
        isGround = true;
        if (Player::instance->getLanding() == Player::ON_AIR) {
            Player::instance->setLanding(Player::LANDING);
            Player::instance->getImage().getPosRectangle().left = 0;
        }
    } else if (position.y <= 0) {
        position.y = 0;
        Player::instance->setVelocityY(0);
    }
    Player::instance->setGround(isGround);
}

static void updateVelocity(std::map<int, int> &map_keys, float deltaTime) {
    float fireVelocity = 0;
    float gravite = DataManager::instance->getGravity();

    if (map_keys[sf::Keyboard::Z] == sf::Event::KeyPressed ||
        map_keys[sf::Keyboard::Space] == sf::Event::KeyPressed) {
        Player::instance->setLanding(Player::ON_AIR);
        fireVelocity = DataManager::instance->getSpeedJetpack();
    }
    Player::instance->setFire(fireVelocity != 0);
    Player::instance->setVelocityY(Player::instance->getVelocityY() +
        ((-gravite + fireVelocity) * deltaTime));
}

void updateImage() {
    ImageClass &image = Player::instance->getImage();

    if (!Player::instance->getAlive()) {
        image.getPosRectangle().top = image.getPosRectangle().height * 3;
        if (image.getPosRectangle().left / image.getPosRectangle().width >=
            image.getNbFrame() - 1)
            image.getPosRectangle().left = 0;
        if (Player::instance->getY() >= HEIGHT - 93 - 30)
            Player::instance->setPos(Player::instance->getX(),
                HEIGHT - 93 - 30);
        else if (Player::instance->getX() >= (0 - 93 - 30))
            Player::instance->setPos(Player::instance->getX() - 0.25f,
                Player::instance->getY());
        return;
    }
    if (Player::instance->getGround()) {
        if (Player::instance->getLanding() == Player::LANDING) {
            image.getPosRectangle().top = image.getPosRectangle().height * 2;
            if (image.getPosRectangle().left / image.getPosRectangle().width >=
                    image.getNbFrame() - 1) {
                image.getPosRectangle().left = 0;
                Player::instance->setLanding(Player::ON_GROUND);
            }
        } else {
            image.getPosRectangle().top = 0;
        }
    } else {
        if (Player::instance->getFire())
            image.getPosRectangle().top = image.getPosRectangle().height;
        else
            image.setRectangle(0, image.getPosRectangle().height,
                Player::instance->getWidth(), Player::instance->getHeight());
    }
}

void updateImagePlayer(Player &player) {
    ImageClass &image = player.getImage();

    if (!player.getAlive()) {
        image.getPosRectangle().top = image.getPosRectangle().height * 3;
        if (image.getPosRectangle().left / image.getPosRectangle().width >=
            image.getNbFrame() - 1)
            image.getPosRectangle().left = 0;
        if (player.getY() >= HEIGHT - 93 - 30)
            player.setPos(player.getX(), HEIGHT - 93 - 30);
        else if (player.getX() >= (0 - 93 - 30))
            player.setPos(player.getX() - 0.25f, player.getY());
        player.getImage().updateAnimation();
        return;
    }
    if (player.getY() >= HEIGHT - player.getHeight()) {
        player.setGround(true);
        if (player.getLanding() == Player::ON_AIR) {
            player.setLanding(Player::LANDING);
            image.getPosRectangle().left = 0;
        }
    } else {
        player.setGround(false);
    }
    if (player.getGround()) {
        if (player.getLanding() == Player::LANDING) {
            image.getPosRectangle().top = image.getPosRectangle().height * 2;
            if (image.getPosRectangle().left / image.getPosRectangle().width >=
                    image.getNbFrame() - 1) {
                image.getPosRectangle().left = 0;
                player.setLanding(Player::ON_GROUND);
            }
        } else {
            image.getPosRectangle().top = 0;
        }
    } else {
        if (player.getFire())
            image.getPosRectangle().top = image.getPosRectangle().height;
        else
            image.setRectangle(0, image.getPosRectangle().height,
                player.getWidth(), player.getHeight());
    }
    player.getImage().updateAnimation();
}

static void updateSound(Game &game, Window &window) {
    if (window.getKeyClick(sf::Keyboard::M))
        game.setVolumeMusic(game.getVolumeMusic() - 10);
    if (window.getKeyClick(sf::Keyboard::P))
        game.setVolumeMusic(game.getVolumeMusic() + 10);
    if (window.getKeyClick(sf::Keyboard::L))
        game.setVolumeSound(game.getVolumeSound() - 10);
    if (window.getKeyClick(sf::Keyboard::O))
        game.setVolumeSound(game.getVolumeSound() + 10);

    if (Player::instance->getFire()) {
        if (game.jetpack.sound.getStatus() != sf::Sound::Playing)
            game.jetpack.sound.play();
    } else {
        if (game.jetpack.sound.getStatus() == sf::Sound::Playing)
            game.jetpack.sound.stop();
    }
}

void updateTakeCoins(Game &game) {
    sf::IntRect RectPl = {static_cast<int>(Player::instance->getX()),
        static_cast<int>(Player::instance->getY()),
        Player::instance->getWidth(), Player::instance->getHeight()};
    if (DataManager::instance->getObstacles().size() < 1)
        return;
    for (int i = DataManager::instance->getObstacles().size() - 1;
            i >= 0; i--) {
        if (i >= static_cast<int>(
            DataManager::instance->getObstacles().size()))
            break;
        Obstacle item = DataManager::instance->getObstacles()[i];
        if (item.x > 300)
            break;
        sf::IntRect RectIt = {static_cast<int>(item.x),
            static_cast<int>(item.y), item.width, item.height};
        if (RectPl.intersects(RectIt)) {
            if (item.type == Obstacle::COIN) {
                if (game.coin.sound.getStatus() == sf::Sound::Playing)
                    game.coin.sound.stop();
                game.coin.sound.play();
                DataManager::instance->getObstacles().erase(
                    DataManager::instance->getObstacles().begin() + i);
                i++;
            }
        }
    }
}

void update(Game &game, Window &window) {
    sf::Vector2f position =
        {Player::instance->getX(), Player::instance->getY()};

    std::lock_guard<std::mutex> lock(Player::instance->getMutexPlayer());
    updateVelocity(window.getMapKeys(), window.getDeltaTime());
    position.y -= (Player::instance->getVelocityY() * window.getDeltaTime());
    handleMaxMin(position);
    Player::instance->getImage().setPosition(position.x, position.y);
    Player::instance->setPos(position.x, position.y);
    Player::instance->getImage().updateAnimation();
    updateTakeCoins(game);
    updateImage();
    updateSound(game, window);
}
