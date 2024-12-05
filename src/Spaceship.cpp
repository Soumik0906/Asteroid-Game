#include "Spaceship.h"
#include <cmath>

Spaceship::Spaceship(const sf::Texture& texture) {
    sprite.setTexture(texture);
    sprite.setOrigin(static_cast<float>(texture.getSize().x) / 2.f, static_cast<float>(texture.getSize().y) / 2.f);
    sprite.setPosition(400.f, 300.f); // Initial position
    rotationSpeed = 5.f;           // Degrees per second
    acceleration = 30.f;            // Pixels per second^2
}

void Spaceship::handleInput() {
    // Rotate left (counter-clockwise)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        sprite.rotate(-rotationSpeed * 0.016f);  // Rotate by rotationSpeed degrees per frame
    }

    // Rotate right (clockwise)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        sprite.rotate(rotationSpeed * 0.016f);  // Rotate by rotationSpeed degrees per frame
    }

    // Get the current rotation of the spaceship (in radians)
    const double rotationInRadians = (sprite.getRotation() - 90.f) * M_PI / 180.f;

    const float xIncrement = static_cast<float>(cos(rotationInRadians)) * acceleration * 0.016f;
    const float yIncrement = static_cast<float>(sin(rotationInRadians)) * acceleration * 0.016f;

    // Apply thrust (move in the direction of the spaceship's rotation)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        // Thrust based on current rotation (move in the direction the spaceship is facing)
        velocity.x += xIncrement;
        velocity.y += yIncrement;
    }

    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
    //     velocity.x = std::max(velocity.x - xIncrement, 0.0f);
    //     velocity.y = std::max(velocity.y - yIncrement, 0.0f);
    // }

    // Clamp the velocity to the maximum speed (maxSpeed)
    float speed = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
    if (constexpr float maxSpeed = 300.f; speed > maxSpeed) {
        velocity.x = (velocity.x / speed) * maxSpeed;
        velocity.y = (velocity.y / speed) * maxSpeed;
    }
}

void Spaceship::update(float dt) {
    handleInput();
    Entity::update(dt);

    // Screen wrapping
    if (sprite.getPosition().x < 0)     sprite.setPosition(800.f, sprite.getPosition().y);
    if (sprite.getPosition().x > 800.f) sprite.setPosition(0.f, sprite.getPosition().y);
    if (sprite.getPosition().y < 0)     sprite.setPosition(sprite.getPosition().x, 600.f);
    if (sprite.getPosition().y > 600.f) sprite.setPosition(sprite.getPosition().x, 0.f);
}
