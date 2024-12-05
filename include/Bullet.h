#pragma once
#include "Entity.h"

class Bullet final : public Entity {
private:
    float m_speed;
public:
    Bullet(const sf::Texture& texture, const sf::Vector2f& position, float spaceshipRotation);
    bool isOutOfBounds(const sf::RenderWindow& window) const;
};
