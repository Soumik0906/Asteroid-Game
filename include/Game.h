#ifndef GAME_H
#define GAME_H

#include "Spaceship.h"
#include "Asteroid.h"
#include "Bullet.h"
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
    void initializeWindow();
    void loadResources();
    void initializeGameObjects();
    void initializeText();
    void initializeTextObject(sf::Text& text, const std::string& str, unsigned int size, sf::Color color, float x, float y);

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

    std::unique_ptr<sf::RenderWindow> window;
    sf::Texture spaceshipTexture, asteroidTexture, bulletTexture, backgroundTexture;
    sf::Sprite backgroundSprite;
    std::unique_ptr<Spaceship> spaceship;
    std::vector<Asteroid> asteroids;
    std::vector<Bullet> bullets;

    sf::SoundBuffer bulletFireBuffer, asteroidHitBuffer;
    sf::Sound bulletFireSound, asteroidHitSound;

    sf::Font font;
    sf::Text pauseText, gameOverText, scoreText, livesText, winText;
    sf::Clock bulletClock;

    GameState gameState;
    Menu menu;

    Settings settings;
};

#endif // GAME_H