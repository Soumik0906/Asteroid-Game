#pragma once
#include <SFML/Graphics.hpp>

class Entity {
public:
    sf::Sprite sprite;
    sf::Vector2f velocity;
    bool isActive;

    Entity();
    virtual ~Entity() = default;

    virtual void update(float dt);
    virtual void draw(sf::RenderWindow &window);

    sf::FloatRect getBounds() const;
};
