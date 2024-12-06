#ifndef GAME_H
#define GAME_H

#include "Spaceship.h"
#include "Asteroid.h"
#include "Bullet.h"
#include <SFML/Audio.hpp>
#include <vector>
#include <optional>
#include <memory>

class Game {
public:
    std::unique_ptr<sf::RenderWindow> window;
    sf::Texture spaceshipTexture, asteroidTexture, bulletTexture, backgroundTexture;
    sf::Sprite backgroundSprite;
    std::unique_ptr<Spaceship> spaceship;
    std::vector<Asteroid> asteroids;
    std::vector<Bullet> bullets;

    sf::SoundBuffer bulletFireBuffer;
    sf::Sound bulletFireSound;

    sf::SoundBuffer asteroidHitBuffer;
    sf::Sound asteroidHitSound;

    Game();
    ~Game() = default;
    void run();

private:
    int lives;
    void gameOver();
    sf::Text gameOverText;
    sf::Font font;

    void restartGame();
    void handleEvents();
    void update(float dt);
    void render();
    void spawnAsteroid(int size, const std::optional<sf::Vector2f>& position = std::nullopt);
    void checkCollisions();
    void checkSpaceshipAsteroidCollision();
};
#endif // GAME_H