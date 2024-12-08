#include "GameObjectManager.h"
#include "Utilities.h"

void GameObjectManager::initializeGameObjects(sf::Texture& spaceshipTexture, sf::Texture& asteroidTexture, sf::Texture& backgroundTexture, sf::RenderWindow& window) {
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(1.f, 2.f);

    spaceship = std::make_unique<Spaceship>(spaceshipTexture);
    spaceship->sprite.setScale(2.f, 2.f);

    for (int i = 0; i < 7; ++i) {
        sf::Vector2f position(Utils::getRandomInRange(0.f, window.getSize().x), Utils::getRandomInRange(0.f, window.getSize().y));
        sf::Vector2f velocity = generateRandomVelocity();
        asteroids.emplace_back(asteroidTexture, 3, position, velocity);
    }
}

sf::Vector2f GameObjectManager::generateRandomVelocity() {
    float angle = Utils::getRandomInRange(0.f, 360.f);
    float speed = Utils::getRandomInRange(50.f, 150.f);

    return {speed * std::cos(angle), speed * std::sin(angle)};
}

std::unique_ptr<Spaceship>& GameObjectManager::getSpaceship() { return spaceship; }
std::vector<Asteroid>& GameObjectManager::getAsteroids() { return asteroids; }
std::vector<Bullet>& GameObjectManager::getBullets() { return bullets; }
sf::Sprite& GameObjectManager::getBackgroundSprite() { return backgroundSprite; }