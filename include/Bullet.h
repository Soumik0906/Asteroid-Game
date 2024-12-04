#pragma once
#include "Entity.h"

class Bullet : public Entity {
public:
    Bullet(sf::Texture& texture, sf::Vector2f position, float rotation);
    bool isOutOfBounds(sf::RenderWindow& window);
};
