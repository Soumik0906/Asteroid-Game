#include "Spaceship.h"
#include "Utilities.h"
#include <cmath>

Spaceship::Spaceship(const sf::Texture& spaceShipTexture, const sf::Texture& exhaustTexture) {
    initializeSprite(spaceShipTexture);
    initializeSound();
    exhaustSprite.setTexture(exhaustTexture);
    exhaustSprite.setOrigin(static_cast<float>(exhaustTexture.getSize().x) / 2.f, static_cast<float>(exhaustTexture.getSize().y) / 2.f);
    exhaustSprite.setScale(1.3f, 1.3f);
}

void Spaceship::initializeSprite(const sf::Texture& texture) {
    sprite.setTexture(texture);
    sprite.setOrigin(static_cast<float>(texture.getSize().x) / 2.f, static_cast<float>(texture.getSize().y) / 2.f);
    sprite.setPosition(Constants::SIZE_X / 2.f, Constants::SIZE_Y / 2.f); // Initial position
    rotationSpeed = Constants::rotationSpeed;
    acceleration = Constants::acceleration;
}

void Spaceship::initializeSound() {
    if (!spaceshipSoundBuffer.loadFromFile("../../assets/sounds/spaceship_engine.ogg")) {
        throw std::runtime_error("Failed to load spaceship_engine.ogg");
    }
    spaceshipSound.setBuffer(spaceshipSoundBuffer);
    spaceshipSound.setVolume(100.f);
}

void Spaceship::handleInput(const float dt) {
    handleRotation(dt);
    handleThrust(dt);
    clampVelocity();
}

void Spaceship::handleRotation(const float dt) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        sprite.rotate(-rotationSpeed * dt);  // Rotate left (counter-clockwise)
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        sprite.rotate(rotationSpeed * dt);  // Rotate right (clockwise)
    }
}

void Spaceship::handleThrust(const float dt) {
    const double rotationInRadians = (sprite.getRotation() - 90.f) * M_PI / 180.f;
    const float xIncrement = static_cast<float>(cos(rotationInRadians)) * acceleration * dt;
    const float yIncrement = static_cast<float>(sin(rotationInRadians)) * acceleration * dt;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        if (spaceshipSound.getStatus() != sf::Sound::Playing) {
            spaceshipSound.play();
        }
        velocity.x += xIncrement;
        velocity.y += yIncrement;

        // Position the exhaust sprite behind the spaceship
        const float exhaustOffsetX = -std::cos(rotationInRadians) * (sprite.getGlobalBounds().height / 2.f);
        const float exhaustOffsetY = -std::sin(rotationInRadians) * (sprite.getGlobalBounds().height / 2.f);

        exhaustSprite.setPosition(sprite.getPosition().x + exhaustOffsetX, sprite.getPosition().y + exhaustOffsetY);
        exhaustSprite.setRotation(sprite.getRotation() - 180.f);
        exhaustSprite.setColor(sf::Color(255, 255, 255, 255));
    } else {
        spaceshipSound.stop();
        exhaustSprite.setColor(sf::Color(255, 255, 255, 0));
    }
}

void Spaceship::clampVelocity() {
    if (const float speed = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y); speed > Constants::maxShipSpeed) {
        velocity.x = (velocity.x / speed) * Constants::maxShipSpeed;
        velocity.y = (velocity.y / speed) * Constants::maxShipSpeed;
    }
}

void Spaceship::update(const float dt) {
    handleInput(dt);
    applyFriction(dt);
    Entity::update(dt);
    wrapAroundScreen();
}

void Spaceship::applyFriction(const float dt) {
    velocity.x -= velocity.x * Constants::frictionFactor * dt;
    velocity.y -= velocity.y * Constants::frictionFactor * dt;
}

bool Spaceship::checkCollision(const Asteroid &asteroid) const {
    if (!isActive || !asteroid.isActive) {
        return false;
    }

    const float dx = sprite.getPosition().x - asteroid.sprite.getPosition().x;
    const float dy = sprite.getPosition().y - asteroid.sprite.getPosition().y;
    const float distance = std::sqrt(dx * dx + dy * dy);
    const float combinedRadius = getRadius() + asteroid.getRadius();

    return distance < combinedRadius;
}

void Spaceship::respawn() {
    sprite.setPosition(Constants::SIZE_X / 2.f, Constants::SIZE_Y / 2.f);
    velocity = sf::Vector2f(0.f, 0.f);
    isActive = true;
}

const sf::Sprite& Spaceship::getFireSprite() const {
    return exhaustSprite;
}