#include "Entity.h"

Entity::Entity() : velocity(0.f, 0.f), isActive(true) {}

void Entity::update(const float dt) {
    sprite.move(velocity * dt);
}

void Entity::draw(sf::RenderWindow& window) {
    if (isActive)
        window.draw(sprite);
}

sf::FloatRect Entity::getBounds() const {
    return sprite.getGlobalBounds();
}
