#pragma once
#include "Entity.h"

class Asteroid : public Entity {
public:
    int size; // 3 = Large, 2 = Medium, 1 = Small

    Asteroid(const sf::Texture& texture, int size, sf::Vector2f position, sf::Vector2f velocity);
    void update(float dt) override;
};
