#pragma once
#include "Entity.h"

class Spaceship : public Entity {
private:
    float rotationSpeed;
    float acceleration;

public:
    Spaceship(const sf::Texture& texture);
    void handleInput();
    void update(float dt) override;
};
