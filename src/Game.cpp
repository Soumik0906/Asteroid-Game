#include "Game.h"
#include "Utilities.h"
#include <SFML/Audio.hpp>
#include <optional>

Game::Game() : window(sf::VideoMode(Constants::SIZE_X, Constants::SIZE_Y), "Asteroids") {
    // Load game textures
    spaceshipTexture.loadFromFile("../../assets/images/spaceship.png");
    asteroidTexture.loadFromFile("../../assets/images/asteroid.png");
    bulletTexture.loadFromFile("../../assets/images/bullet.png");
    backgroundTexture.loadFromFile("../../assets/images/space.jpg");

    // Add background image
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(1.f, 2.f);

    // Load game sounds
    if (!bulletFireBuffer.loadFromFile("../../assets/sounds/bullet_fire.wav")) {
        throw std::runtime_error("Failed to load bullet_fire.wav");
    }
    bulletFireSound.setBuffer(bulletFireBuffer);

    if (!asteroidHitBuffer.loadFromFile("../../assets/sounds/asteroid_hit.wav")) {
        throw std::runtime_error("Failed to load asteroid_hit.wav");
    }
    asteroidHitSound.setBuffer(asteroidHitBuffer);

    spaceship = new Spaceship(spaceshipTexture);
    spaceship->sprite.setScale(Constants::spaceShipScale, Constants::spaceShipScale);

    // Initial asteroids
    for (int i = 0; i < 7; ++i)
        spawnAsteroid(3);
}

Game::~Game() {
    delete spaceship;
}

void Game::run() {
    sf::Clock clock;
    while (window.isOpen()) {
        const float dt = clock.restart().asSeconds();
        handleEvents();
        update(dt);
        render();
    }
}

void Game::handleEvents() {
    sf::Event event{};
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
            bulletFireSound.play();
            bullets.emplace_back(bulletTexture, spaceship->sprite.getPosition(), spaceship->sprite.getRotation());
        }
    }
}

void Game::update(const float dt) {
    spaceship->update(dt);

    for (auto& asteroid : asteroids) {
        asteroid.update(dt);
    }

    for (auto& bullet : bullets)
        bullet.update(dt);

    bullets.erase(std::ranges::remove_if(bullets,
                                         [this](const Bullet& b) { return b.isOutOfBounds(window); }).begin(),
                  bullets.end());

    checkCollisions();
}

void Game::render() {
    window.clear();
    window.draw(backgroundSprite);
    spaceship->draw(window);
    for (auto& asteroid : asteroids)
        asteroid.draw(window);
    for (auto& bullet : bullets)
        bullet.draw(window);
    window.display();
}

sf::Vector2f generateRandomVelocity() {
    return sf::Vector2f(
        Utils::getRandomInRange(-Constants::maxAsteroidSpeed, Constants::maxAsteroidSpeed),
        Utils::getRandomInRange(-Constants::maxAsteroidSpeed, Constants::maxAsteroidSpeed)
    );
}

void Game::spawnAsteroid(int size, const std::optional<sf::Vector2f>& position) {
    sf::Vector2f finalPosition = position.value_or(sf::Vector2f(
        Utils::getRandomInRange(0.f, window.getSize().x),
        Utils::getRandomInRange(0, window.getSize().y)));
    sf::Vector2f velocity = generateRandomVelocity();
    asteroids.emplace_back(asteroidTexture, size, finalPosition, velocity);
}


void Game::checkCollisions() {
    for (auto& bullet : bullets) {
        for (auto& asteroid : asteroids) {
            if (bullet.isActive && asteroid.isActive && bullet.getBounds().intersects(asteroid.getBounds())) {
                asteroidHitSound.play();

                bullet.isActive = false;
                asteroid.isActive = false;

                // Generate more asteroids in the same position that are smaller
                if (asteroid.size > 1) {
                    for (int i { 0 }; i < 3; ++i) {
                        spawnAsteroid(asteroid.size - 1, asteroid.sprite.getPosition());
                    }
                }
            }
        }
    }
}
