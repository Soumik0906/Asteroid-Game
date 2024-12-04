#pragma once
#include "Entity.h"

class Bullet final : public Entity {
public:
    Bullet(const sf::Texture& texture, sf::Vector2f position, float spaceshipRotation);
    bool isOutOfBounds(const sf::RenderWindow& window) const;
};
