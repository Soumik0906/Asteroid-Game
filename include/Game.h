#ifndef GAME_H
#define GAME_H

#include "WindowManager.h"
#include "ResourceManager.h"
#include "GameObjectManager.h"
#include "TextManager.h"
#include "Menu.h"
#include "Settings.h"
#include <SFML/Audio.hpp>
#include <vector>
#include <optional>
#include <memory>

enum class GameState { MENU, PLAYING, GAME_OVER, SETTINGS };

class Game {
public:
    Game();
    ~Game() = default;
    void run();

private:
    void handleEvents();
    void handleMenuEvents();
    void handleGameEvents();
    void handleBulletFire();
    void update(float dt);
    void render();

    void handleSettingsEvents();

    void togglePause();
    void checkCollisions();
    void checkSpaceshipAsteroidCollision();
    void checkWinGame();
    void gameOver();
    void restartGame();
    void spawnAsteroid(int size, const std::optional<sf::Vector2f>& position = std::nullopt, bool checkSpaceshipPosition = false);
    void displayMessage(const sf::Text& text);

    bool paused;
    int lives;
    int score;
    float bulletCooldown;
    sf::Time lastBulletTime;

    WindowManager windowManager;
    ResourceManager resourceManager;
    GameObjectManager gameObjectManager;
    TextManager textManager;

    sf::Sound bulletFireSound, asteroidHitSound;
    sf::Clock bulletClock;

    GameState gameState;
    Menu menu;
    Settings settings;
};

#endif // GAME_H