#include "GameObjectManager.h"
#include "Utilities.h"

void GameObjectManager::initializeGameObjects(sf::Texture& spaceshipTexture, const sf::Texture& asteroidTexture, const sf::Texture& backgroundTexture, sf::RenderWindow& window) {
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(1.f, 2.f);

    spaceship = std::make_unique<Spaceship>(spaceshipTexture);
    spaceship->sprite.setScale(2.f, 2.f);

    for (int i = 0; i < 7; ++i) {
        spawnAsteroid(3, asteroidTexture, std::nullopt, true);
    }
}

void GameObjectManager::spawnAsteroid(int size, const sf::Texture& asteroidTexture, const std::optional<sf::Vector2f>& position, bool checkSpaceshipPosition) {
    sf::Vector2f finalPosition;
    bool validPosition = false;

    while (!validPosition) {
        finalPosition = position.value_or(generateRandomPosition());

        if (checkSpaceshipPosition) {
            float dx = finalPosition.x - spaceship->sprite.getPosition().x;
            float dy = finalPosition.y - spaceship->sprite.getPosition().y;
            float distance = std::sqrt(dx * dx + dy * dy);

            if (distance > spaceship->getRadius() * 3) {
                validPosition = true;
            }
        } else {
            validPosition = true;
        }
    }

    sf::Vector2f randomVelocity{ generateRandomVelocity() };
    asteroids.emplace_back(asteroidTexture, size, finalPosition, randomVelocity);
}


sf::Vector2f GameObjectManager::generateRandomPosition() {
    return {
        Utils::getRandomInRange(0.f, Constants::windowWidth),
        Utils::getRandomInRange(0.f, Constants::windowHeight)
    };
}

sf::Vector2f GameObjectManager::generateRandomVelocity() {
    return {
        Utils::getRandomInRange(-Constants::maxAsteroidSpeed, Constants::maxAsteroidSpeed),
        Utils::getRandomInRange(-Constants::maxAsteroidSpeed, Constants::maxAsteroidSpeed)
    };
}

std::unique_ptr<Spaceship>& GameObjectManager::getSpaceship() { return spaceship; }
std::vector<Asteroid>& GameObjectManager::getAsteroids() { return asteroids; }
std::vector<Bullet>& GameObjectManager::getBullets() { return bullets; }
sf::Sprite& GameObjectManager::getBackgroundSprite() { return backgroundSprite; }