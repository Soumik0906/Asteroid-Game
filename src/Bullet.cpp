#include "Bullet.h"
#include <cmath>

Bullet::Bullet(const sf::Texture& texture, const sf::Vector2f position, const float spaceshipRotation) {
    sprite.setTexture(texture);
    sprite.setOrigin(static_cast<float>(texture.getSize().x) / 2.f, static_cast<float>(texture.getSize().y) / 2.f);
    sprite.setPosition(position);
    sprite.setRotation(spaceshipRotation - 180.f);

    const double angle = (spaceshipRotation - 90.f) * 3.14159265f / 180.f;
    velocity = sf::Vector2f(static_cast<float>(cos(angle)) * 400.f, static_cast<float>(sin(angle)) * 400.f); // Fixed speed
}

bool Bullet::isOutOfBounds(const sf::RenderWindow& window) const {
    const auto pos = sprite.getPosition();
    return pos.x < 0 || pos.x > static_cast<float>(window.getSize().x) || pos.y < 0 || pos.y > static_cast<float>(window.getSize().y);
}
