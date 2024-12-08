#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdexcept>

class ResourceManager {
public:
    void loadResources();
    sf::Texture& getSpaceshipTexture();
    sf::Texture& getAsteroidTexture();
    sf::Texture& getBulletTexture();
    sf::Texture& getBackgroundTexture();
    sf::SoundBuffer& getBulletFireBuffer();
    sf::SoundBuffer& getAsteroidHitBuffer();
    sf::Font& getFont();

private:
    sf::Texture spaceshipTexture, asteroidTexture, bulletTexture, backgroundTexture;
    sf::SoundBuffer bulletFireBuffer, asteroidHitBuffer;
    sf::Font font;
};

#endif // RESOURCE_MANAGER_H