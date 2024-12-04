#include "Spaceship.h"
#include <cmath>

Spaceship::Spaceship(sf::Texture& texture) {
    sprite.setTexture(texture);
    sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
    sprite.setPosition(400.f, 300.f); // Initial position
    rotationSpeed = 15.f;           // Degrees per second
    acceleration = 200.f;            // Pixels per second^2
}

void Spaceship::handleInput() {
    constexpr float maxSpeed = 200.f;
    // Get the current rotation of the spaceship (in radians)
    float rotationInRadians = sprite.getRotation() * 3.14159265f / 180.f;

    // Rotate left (counter-clockwise)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        sprite.rotate(-rotationSpeed * 0.016f);  // Rotate by rotationSpeed degrees per frame
    }

    // Rotate right (clockwise)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        sprite.rotate(rotationSpeed * 0.016f);  // Rotate by rotationSpeed degrees per frame
    }

    // Apply thrust (move in the direction of the spaceship's rotation)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        // Thrust based on current rotation (move in the direction the spaceship is facing)
        velocity.x += cos(rotationInRadians) * acceleration * 0.016f;
        velocity.y += sin(rotationInRadians) * acceleration * 0.016f;
    }

    // Clamp the velocity to the maximum speed (maxSpeed)
    float speed = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
    if (speed > maxSpeed) {
        velocity.x = (velocity.x / speed) * maxSpeed;
        velocity.y = (velocity.y / speed) * maxSpeed;
    }
}

void Spaceship::update(float dt) {
    handleInput();
    Entity::update(dt);

    // Screen wrapping
    if (sprite.getPosition().x < 0) sprite.setPosition(800.f, sprite.getPosition().y);
    if (sprite.getPosition().x > 800.f) sprite.setPosition(0.f, sprite.getPosition().y);
    if (sprite.getPosition().y < 0) sprite.setPosition(sprite.getPosition().x, 600.f);
    if (sprite.getPosition().y > 600.f) sprite.setPosition(sprite.getPosition().x, 0.f);
}
