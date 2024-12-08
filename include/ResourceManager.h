#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class ResourceManager {
public:
    void loadResources();
    sf::Texture& getSpaceshipTexture();
    sf::Texture& getAsteroidTexture();
    sf::Texture& getBulletTexture();
    sf::Texture& getBackgroundTexture();
    sf::Texture& getExhaustTexture();
    sf::SoundBuffer& getBulletFireBuffer();
    sf::SoundBuffer& getAsteroidHitBuffer();
    sf::Font& getFont();

private:
    sf::Texture spaceshipTexture, asteroidTexture, bulletTexture, backgroundTexture, exhaustTexture;
    sf::SoundBuffer bulletFireBuffer, asteroidHitBuffer;
    sf::Font font;
};

#endif // RESOURCE_MANAGER_H