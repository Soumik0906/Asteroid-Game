#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "Entity.h"
#include "Asteroid.h"
#include <SFML/Audio.hpp>

class Spaceship final : public Entity {
public:
    explicit Spaceship(const sf::Texture& texture);
    void handleInput(float dt);
    void update(float dt) override;
    bool checkCollision(const Asteroid& asteroid) const;
    void respawn();

private:
    void initializeSprite(const sf::Texture& texture);
    void initializeSound();
    void handleRotation(float dt);
    void handleThrust(float dt);
    void handleFriction(float dt);
    void clampVelocity();
    void applyFriction(float dt);

    sf::SoundBuffer spaceshipSoundBuffer;
    sf::Sound spaceshipSound;
    float rotationSpeed{};
    float acceleration{};
};

#endif // SPACESHIP_H