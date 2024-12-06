#pragma once
#include "Spaceship.h"
#include "Asteroid.h"
#include "Bullet.h"
#include <SFML/Audio.hpp>
#include <vector>
#include <optional>

class Game {
public:
    sf::RenderWindow window;
    sf::Texture spaceshipTexture, asteroidTexture, bulletTexture, backgroundTexture;
    sf::Sprite backgroundSprite;
    Spaceship* spaceship;
    std::vector<Asteroid> asteroids;
    std::vector<Bullet> bullets;

    sf::SoundBuffer bulletFireBuffer;
    sf::Sound bulletFireSound;

    sf::SoundBuffer asteroidHitBuffer;
    sf::Sound asteroidHitSound;

    Game();
    ~Game();
    void run();

private:
    void handleEvents();
    void update(float dt);
    void render();
    void spawnAsteroid(int size, const std::optional<sf::Vector2f>& position = std::nullopt);
    void checkCollisions();
};
