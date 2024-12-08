#include "Bullet.h"
#include <cmath>
#include <Utilities.h>

Bullet::Bullet(const sf::Texture& texture, const sf::Vector2f& position, const float spaceshipRotation) {
    sprite.setTexture(texture);
    sprite.setOrigin(static_cast<float>(texture.getSize().x) / 2.f, static_cast<float>(texture.getSize().y) / 2.f);
    sprite.setPosition(position);
    sprite.setRotation(spaceshipRotation - 180.f);

    m_speed = Constants::bulletSpeed; // Fixed Speed of bullet
    const double angle = (spaceshipRotation - 90.f) * M_PI / 180.f;
    velocity = sf::Vector2f(static_cast<float>(cos(angle)) * m_speed, static_cast<float>(sin(angle)) * m_speed);
}

bool Bullet::isOutOfBounds(const sf::RenderWindow& window) const {
    const auto pos = sprite.getPosition();
    return pos.x < 0 || pos.x > static_cast<float>(Constants::windowWidth) || pos.y < 0 || pos.y > static_cast<float>(Constants::windowHeight);
}
