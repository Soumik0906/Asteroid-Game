#pragma once
#include "Entity.h"
#include <SFML/Audio.hpp>

class Spaceship final : public Entity {
public:
    explicit Spaceship(const sf::Texture& texture);
    void handleInput();
    void update(float dt) override;

    sf::SoundBuffer spaceshipSoundBuffer;
    sf::Sound spaceshipSound;

private:
    float rotationSpeed;
    float acceleration;
};
