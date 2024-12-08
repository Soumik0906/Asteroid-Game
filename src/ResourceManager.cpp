#include "ResourceManager.h"

void ResourceManager::loadResources() {
    if (!spaceshipTexture.loadFromFile("../../assets/images/spaceship.png") ||
        !asteroidTexture.loadFromFile("../../assets/images/asteroid.png") ||
        !bulletTexture.loadFromFile("../../assets/images/bullet.png") ||
        !backgroundTexture.loadFromFile("../../assets/images/space.jpg") ||
        !bulletFireBuffer.loadFromFile("../../assets/sounds/bullet_fire.wav") ||
        !asteroidHitBuffer.loadFromFile("../../assets/sounds/asteroid_hit.wav") ||
        !font.loadFromFile("../../assets/fonts/arial.ttf")) {
        throw std::runtime_error("Failed to load resources");
    }
}

sf::Texture& ResourceManager::getSpaceshipTexture() { return spaceshipTexture; }
sf::Texture& ResourceManager::getAsteroidTexture() { return asteroidTexture; }
sf::Texture& ResourceManager::getBulletTexture() { return bulletTexture; }
sf::Texture& ResourceManager::getBackgroundTexture() { return backgroundTexture; }
sf::SoundBuffer& ResourceManager::getBulletFireBuffer() { return bulletFireBuffer; }
sf::SoundBuffer& ResourceManager::getAsteroidHitBuffer() { return asteroidHitBuffer; }
sf::Font& ResourceManager::getFont() { return font; }