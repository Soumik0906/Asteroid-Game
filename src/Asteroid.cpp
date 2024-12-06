#include "Asteroid.h"

Asteroid::Asteroid(const sf::Texture& texture, const int size, const sf::Vector2f& position, const sf::Vector2f& velocity)
    : size(size) {
    sprite.setTexture(texture);
    sprite.setOrigin(static_cast<float>(texture.getSize().x) / 2.f, static_cast<float>(texture.getSize().y) / 2.f);
    sprite.setScale(static_cast<float>(size) / 5.f, static_cast<float>(size) / 5.f); // Scale based on size
    sprite.setPosition(position);
    this->velocity = velocity;
}

void Asteroid::update(const float dt) {
    Entity::update(dt);
    wrapAroundScreen();
}
