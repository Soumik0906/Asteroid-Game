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
    void initializeGameObjects(sf::Texture& spaceshipTexture, sf::Texture& asteroidTexture, sf::Texture& backgroundTexture, sf::RenderWindow& window);
    std::unique_ptr<Spaceship>& getSpaceship();
    std::vector<Asteroid>& getAsteroids();
    std::vector<Bullet>& getBullets();
    sf::Sprite& getBackgroundSprite();
    sf::Vector2f generateRandomVelocity();

private:
    std::unique_ptr<Spaceship> spaceship;
    std::vector<Asteroid> asteroids;
    std::vector<Bullet> bullets;
    sf::Sprite backgroundSprite;
};

#endif // GAME_OBJECT_MANAGER_H