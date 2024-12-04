#pragma once
#include "Entity.h"

class Spaceship : public Entity {
public:
    float rotationSpeed;
    float acceleration;

    Spaceship(const sf::Texture& texture);
    void handleInput();
    void update(float dt) override;
};
