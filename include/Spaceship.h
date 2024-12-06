#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "Entity.h"
#include <SFML/Audio.hpp>

class Spaceship final : public Entity {
public:
    explicit Spaceship(const sf::Texture& texture);
    void handleInput(float dt);
    void update(float dt) override;
    void respawn();

    sf::SoundBuffer spaceshipSoundBuffer;
    sf::Sound spaceshipSound;

private:
    float rotationSpeed;
    float acceleration;
};

#endif // SPACESHIP_H