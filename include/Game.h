#pragma once
#include "Spaceship.h"
#include "Asteroid.h"
#include "Bullet.h"
#include <vector>

class Game {
public:
    sf::RenderWindow window;
    sf::Texture spaceshipTexture, asteroidTexture, bulletTexture;
    Spaceship* spaceship;
    std::vector<Asteroid> asteroids;
    std::vector<Bullet> bullets;

    Game();
    ~Game();
    void run();

private:
    void handleEvents();
    void update(float dt);
    void render();
    void spawnAsteroid(int size);
    void spawnAsteroid(int size, const sf::Vector2f& position);
    void checkCollisions();
};
