#include "Game.h"
#include "Utilities.h"
#include <SFML/Audio.hpp>
#include <optional>
#include <memory>

Game::Game() : lives(5), score(0) {
    window = std::make_unique<sf::RenderWindow>(sf::VideoMode(Constants::SIZE_X, Constants::SIZE_Y), "Asteroids");

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

    spaceship = std::make_unique<Spaceship>(spaceshipTexture);
    spaceship->sprite.setScale(Constants::spaceShipScale, Constants::spaceShipScale);

    // Initial asteroids
    for (int i = 0; i < 7; ++i)
        spawnAsteroid(3);

    // Load font
    if (!font.loadFromFile("../../assets/fonts/arial.ttf")) {
        throw std::runtime_error("Failed to load arial.ttf");
    }

    // Set up game over text
    gameOverText.setFont(font);
    gameOverText.setString("Game Over!");
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setStyle(sf::Text::Bold);
    gameOverText.setPosition(
        Constants::SIZE_X / 2.f - gameOverText.getGlobalBounds().width / 2.f,
        Constants::SIZE_Y / 2.f - gameOverText.getGlobalBounds().height / 2.f
    );

    // Set up score text
    scoreText.setFont(font);
    scoreText.setCharacterSize(30);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10.f, 10.f);
    scoreText.setString("Score: 0");

    // Set up lives text
    livesText.setFont(font);
    livesText.setCharacterSize(30);
    livesText.setFillColor(sf::Color::White);
    livesText.setPosition(Constants::SIZE_X - 110.f, 10.f);
    livesText.setString("Lives: " + std::to_string(lives));

    // Set up win text
    winText.setFont(font);
    winText.setString("You Win!");
    winText.setCharacterSize(50);
    winText.setFillColor(sf::Color::Green);
    winText.setStyle(sf::Text::Bold);
    winText.setPosition(
        Constants::SIZE_X / 2.f - winText.getGlobalBounds().width / 2.f,
        Constants::SIZE_Y / 2.f - winText.getGlobalBounds().height / 2.f
    );
}

void Game::checkSpaceshipAsteroidCollision() {
    for (auto& asteroid : asteroids) {
        if (spaceship->isActive && asteroid.isActive) {
            float dx = spaceship->sprite.getPosition().x - asteroid.sprite.getPosition().x;
            float dy = spaceship->sprite.getPosition().y - asteroid.sprite.getPosition().y;
            float distance = std::sqrt(dx * dx + dy * dy);
            float combinedRadius = spaceship->getRadius() + asteroid.getRadius();

            if (distance < combinedRadius) {
                // Handle collision
                spaceship->isActive = false;
                //asteroid.isActive = false;
                asteroidHitSound.play();

                lives--;
                livesText.setString("Lives: " + std::to_string(lives));
                if (lives > 0) {
                    sf::sleep(sf::seconds(0.5)); // Delay before respawning the spaceship
                    spaceship->respawn();
                } else {
                    gameOver();
                }
            }
        }
    }
}

void Game::gameOver() {
    window->clear();
    window->draw(backgroundSprite);
    window->draw(gameOverText);
    window->display();

    sf::sleep(sf::seconds(3));
    window->close();
}

void Game::run() {
    sf::Clock clock;
    while (window->isOpen()) {
        const float dt = clock.restart().asSeconds();
        handleEvents();
        update(dt);
        render();
    }
}

void Game::handleEvents() {
    sf::Event event{};
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window->close();
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
                                         [this](const Bullet& b) { return b.isOutOfBounds(*window); }).begin(),
                  bullets.end());

    checkCollisions();
}

void Game::render() {
    window->clear();
    window->draw(backgroundSprite);
    spaceship->draw(*window);
    for (auto& asteroid : asteroids)
        asteroid.draw(*window);
    for (auto& bullet : bullets)
        bullet.draw(*window);
    window->draw(scoreText);
    window->draw(livesText);
    window->display();
}

sf::Vector2f generateRandomVelocity() {
    return sf::Vector2f(
        Utils::getRandomInRange(-Constants::maxAsteroidSpeed, Constants::maxAsteroidSpeed),
        Utils::getRandomInRange(-Constants::maxAsteroidSpeed, Constants::maxAsteroidSpeed)
    );
}

void Game::spawnAsteroid(int size, const std::optional<sf::Vector2f>& position, bool checkSpaceshipPosition) {
    sf::Vector2f finalPosition;
    bool validPosition = false;

    while (!validPosition) {
        finalPosition = position.value_or(sf::Vector2f(
            Utils::getRandomInRange(0.f, window->getSize().x),
            Utils::getRandomInRange(0.f, window->getSize().y)));

        if (checkSpaceshipPosition) {
            float dx = finalPosition.x - spaceship->sprite.getPosition().x;
            float dy = finalPosition.y - spaceship->sprite.getPosition().y;
            float distance = std::sqrt(dx * dx + dy * dy);

            if (distance > spaceship->getRadius() * 3) {
                validPosition = true;
            }
        } else {
            validPosition = true;
        }
    }

    sf::Vector2f velocity = generateRandomVelocity();
    asteroids.emplace_back(asteroidTexture, size, finalPosition, velocity);
}


void Game::checkCollisions() {
    checkSpaceshipAsteroidCollision();

    for (auto& bullet : bullets) {
        for (auto& asteroid : asteroids) {
            if (bullet.isActive && asteroid.isActive && bullet.getBounds().intersects(asteroid.getBounds())) {
                asteroidHitSound.play();

                bullet.isActive = false;
                asteroid.isActive = false;

                score += asteroid.size * 10;
                scoreText.setString("Score: " + std::to_string(score));

                // Generate more asteroids in the same position that are smaller
                if (asteroid.size > 1) {
                    for (int i { 0 }; i < Utils::getRandomInRange(2, 5); ++i) {
                        spawnAsteroid(asteroid.size - 1, asteroid.sprite.getPosition());
                    }
                }
            }
        }
    }

    // Remove deactivated asteroids
    asteroids.erase(std::remove_if(asteroids.begin(), asteroids.end(),
                                   [](const Asteroid& asteroid) { return !asteroid.isActive; }),
                    asteroids.end());

    checkWinGame();
}

void Game::restartGame() {
    // Clear existing asteroids and bullets
    asteroids.clear();
    bullets.clear();

    // Respawn the spaceship
    spaceship->respawn();

    // Spawn initial asteroids
    for (int i = 0; i < 7; ++i) {
        spawnAsteroid(3);
    }
}

void Game::checkWinGame() {
    if (asteroids.empty()) {
        window->clear();
        window->draw(backgroundSprite);
        window->draw(winText);
        window->display();

        sf::sleep(sf::seconds(3));
        window->close();
    }
}
