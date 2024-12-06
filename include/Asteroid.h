#ifndef ASTEROID_H
#define ASTEROID_H

#include "Entity.h"

class Asteroid final : public Entity {
public:
    int size; // 3 = Large, 2 = Medium, 1 = Small

    Asteroid(const sf::Texture& texture, int size, const sf::Vector2f& position, const sf::Vector2f& velocity);
    void update(float dt) override;
};

#endif // ASTEROID_H