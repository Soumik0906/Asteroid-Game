#include "ResourceManager.h"

void ResourceManager::loadResources() {
    if (!spaceshipTexture.loadFromFile(ROOT_DIR "/assets/images/spaceship.png") ||
        !asteroidTexture.loadFromFile(ROOT_DIR "/assets/images/asteroid.png") ||
        !bulletTexture.loadFromFile(ROOT_DIR "/assets/images/bullet.png") ||
        !backgroundTexture.loadFromFile(ROOT_DIR "/assets/images/space.jpg") ||
        !exhaustTexture.loadFromFile(ROOT_DIR "/assets/gifs/blue_fire.gif") ||
        !bulletFireBuffer.loadFromFile(ROOT_DIR "/assets/sounds/bullet_fire.wav") ||
        !asteroidHitBuffer.loadFromFile(ROOT_DIR "/assets/sounds/asteroid_hit.wav") ||
        !font.loadFromFile(ROOT_DIR "/assets/fonts/arial.ttf")) {
        throw std::runtime_error("Failed to load resources");
    }
}

sf::Texture& ResourceManager::getSpaceshipTexture() { return spaceshipTexture; }
sf::Texture& ResourceManager::getAsteroidTexture() { return asteroidTexture; }
sf::Texture& ResourceManager::getBulletTexture() { return bulletTexture; }
sf::Texture& ResourceManager::getBackgroundTexture() { return backgroundTexture; }
sf::Texture &ResourceManager::getExhaustTexture() { return exhaustTexture; }

sf::SoundBuffer& ResourceManager::getBulletFireBuffer() { return bulletFireBuffer; }
sf::SoundBuffer& ResourceManager::getAsteroidHitBuffer() { return asteroidHitBuffer; }
sf::Font& ResourceManager::getFont() { return font; }