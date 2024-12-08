#include "Entity.h"
#include "Utilities.h"

Entity::Entity() : velocity(0.f, 0.f), isActive(true) {}

void Entity::update(const float dt) {
    sprite.move(velocity * dt);
}

float Entity::getRadius() const {
    return sprite.getGlobalBounds().width / 2.f;
}

void Entity::wrapAroundScreen() {
    if (sprite.getPosition().x < 0.f) sprite.setPosition(Constants::windowWidth, sprite.getPosition().y);
    if (sprite.getPosition().x > Constants::windowWidth) sprite.setPosition(0.f, sprite.getPosition().y);
    if (sprite.getPosition().y < 0.f) sprite.setPosition(sprite.getPosition().x, Constants::windowHeight);
    if (sprite.getPosition().y > Constants::windowHeight) sprite.setPosition(sprite.getPosition().x, 0.f);
}

void Entity::draw(sf::RenderWindow& window) {
    if (isActive) {
        window.draw(sprite);
    }
}

sf::FloatRect Entity::getBounds() const {
    return sprite.getGlobalBounds();
}
