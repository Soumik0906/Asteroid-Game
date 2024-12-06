#include "Spaceship.h"
#include "Utilities.h"
#include <cmath>

Spaceship::Spaceship(const sf::Texture& texture) {
    sprite.setTexture(texture);
    sprite.setOrigin(static_cast<float>(texture.getSize().x) / 2.f, static_cast<float>(texture.getSize().y) / 2.f);
    sprite.setPosition(Constants::SIZE_X / 2.f, Constants::SIZE_Y / 2.f); // Initial position
    rotationSpeed = Constants::rotationSpeed;
    acceleration =  Constants::acceleration;

    if (!spaceshipSoundBuffer.loadFromFile("../../assets/sounds/spaceship_engine.ogg")) {
        throw std::runtime_error("Failed to load spaceship_engine.ogg");
    }
    spaceshipSound.setBuffer(spaceshipSoundBuffer);
    spaceshipSound.setVolume(100.f);
}

void Spaceship::handleInput(const float dt) {
    // Rotate left (counter-clockwise)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        sprite.rotate(-rotationSpeed * dt);  // Rotate by rotationSpeed degrees per frame
    }

    // Rotate right (clockwise)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        sprite.rotate(rotationSpeed * dt);  // Rotate by rotationSpeed degrees per frame
    }

    // Get the current rotation of the spaceship (in radians)
    const double rotationInRadians = (sprite.getRotation() - 90.f) * M_PI / 180.f;

    const float xIncrement = static_cast<float>(cos(rotationInRadians)) * acceleration * dt;
    const float yIncrement = static_cast<float>(sin(rotationInRadians)) * acceleration * dt;

    // Apply thrust (move in the direction of the spaceship's rotation)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        if (spaceshipSound.getStatus() != sf::Sound::Playing) {
            spaceshipSound.play();
        }
        // Thrust based on current rotation (move in the direction the spaceship is facing)
        velocity.x += xIncrement;
        velocity.y += yIncrement;
    } else {
        spaceshipSound.stop();
    }

    // Clamp the velocity to the maximum speed (maxSpeed)
    if (float speed = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y); speed > Constants::maxShipSpeed) {
        velocity.x = (velocity.x / speed) * Constants::maxShipSpeed;
        velocity.y = (velocity.y / speed) * Constants::maxShipSpeed;
    }
}

void Spaceship::update(const float dt) {
    handleInput(dt);
    // Apply friction scaled by delta time
    velocity.x -= velocity.x * Constants::frictionFactor * dt;
    velocity.y -= velocity.y * Constants::frictionFactor * dt;
    Entity::update(dt);
    wrapAroundScreen();
}

void Spaceship::respawn() {
    sprite.setPosition(Constants::SIZE_X / 2.f, Constants::SIZE_Y / 2.f);
    velocity = sf::Vector2f(0.f, 0.f);
    isActive = true;
}