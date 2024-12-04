#include "Bullet.h"
#include <cmath>

Bullet::Bullet(sf::Texture& texture, sf::Vector2f position, float rotation) {
    sprite.setTexture(texture);
    sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
    sprite.setPosition(position);
    sprite.setRotation(rotation);

    float angle = rotation * 3.14159265f / 180.f;
    velocity = sf::Vector2f(cos(angle) * 400.f, sin(angle) * 400.f); // Fixed speed
}

bool Bullet::isOutOfBounds(sf::RenderWindow& window) {
    auto pos = sprite.getPosition();
    return pos.x < 0 || pos.x > window.getSize().x || pos.y < 0 || pos.y > window.getSize().y;
}
