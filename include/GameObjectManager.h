#ifndef GAME_OBJECT_MANAGER_H
#define GAME_OBJECT_MANAGER_H

#include "Spaceship.h"
#include "Asteroid.h"
#include "Bullet.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

class GameObjectManager {
public:
    void initializeGameObjects(const sf::Texture& spaceshipTexture, const sf::Texture& exhaustTexture, const sf::Texture& asteroidTexture, const sf::Texture& backgroundTexture, sf::RenderWindow& window);
    void spawnAsteroid(int size, const sf::Texture& asteroidTexture, const std::optional<sf::Vector2f>& position = std::nullopt, bool checkSpaceshipPosition = false);
    std::unique_ptr<Spaceship>& getSpaceship();
    std::vector<Asteroid>& getAsteroids();
    std::vector<Bullet>& getBullets();
    sf::Sprite& getBackgroundSprite();

    static sf::Vector2f generateRandomVelocity();
    static sf::Vector2f generateRandomPosition();

private:
    std::unique_ptr<Spaceship> spaceship;
    std::vector<Asteroid> asteroids;
    std::vector<Bullet> bullets;

    sf::Sprite backgroundSprite;
};

#endif // GAME_OBJECT_MANAGER_H