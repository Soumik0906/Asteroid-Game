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

    // Screen wrapping
    if (sprite.getPosition().x < 0) sprite.setPosition(800.f, sprite.getPosition().y);
    if (sprite.getPosition().x > 800.f) sprite.setPosition(0.f, sprite.getPosition().y);
    if (sprite.getPosition().y < 0) sprite.setPosition(sprite.getPosition().x, 600.f);
    if (sprite.getPosition().y > 600.f) sprite.setPosition(sprite.getPosition().x, 0.f);
}
