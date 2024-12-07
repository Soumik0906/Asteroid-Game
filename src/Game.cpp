#include "Game.h"
#include "Utilities.h"
#include <SFML/Audio.hpp>
#include <optional>
#include <memory>

// Constructor
Game::Game() : lives(5), score(0), paused(false), bulletCooldown(0.05f), gameState(GameState::MENU), menu(Constants::SIZE_X, Constants::SIZE_Y) {
    initializeWindow();
    loadResources();
    initializeGameObjects();
    initializeText();
    lastBulletTime = bulletClock.getElapsedTime();
}

// Initialize the game window
void Game::initializeWindow() {
    window = std::make_unique<sf::RenderWindow>(sf::VideoMode(Constants::SIZE_X, Constants::SIZE_Y), "Asteroids");
}

// Load game resources (textures, sounds, fonts)
void Game::loadResources() {
    if (!spaceshipTexture.loadFromFile("../../assets/images/spaceship.png") ||
        !asteroidTexture.loadFromFile("../../assets/images/asteroid.png") ||
        !bulletTexture.loadFromFile("../../assets/images/bullet.png") ||
        !backgroundTexture.loadFromFile("../../assets/images/space.jpg") ||
        !bulletFireBuffer.loadFromFile("../../assets/sounds/bullet_fire.wav") ||
        !asteroidHitBuffer.loadFromFile("../../assets/sounds/asteroid_hit.wav") ||
        !font.loadFromFile("../../assets/fonts/arial.ttf")) {
        throw std::runtime_error("Failed to load resources");
    }

    bulletFireSound.setBuffer(bulletFireBuffer);
    asteroidHitSound.setBuffer(asteroidHitBuffer);
}

// Initialize game objects (spaceship, asteroids, background)
void Game::initializeGameObjects() {
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(1.f, 2.f);

    spaceship = std::make_unique<Spaceship>(spaceshipTexture);
    spaceship->sprite.setScale(Constants::spaceShipScale, Constants::spaceShipScale);

    for (int i = 0; i < 7; ++i) {
        spawnAsteroid(3, std::nullopt, true);
    }
}

// Initialize text objects (game over, score, lives, win, pause)
void Game::initializeText() {
    initializeTextObject(gameOverText, "Game Over!", 50, sf::Color::Red, Constants::SIZE_X / 2.f, Constants::SIZE_Y / 2.f);
    initializeTextObject(scoreText, "Score: 0", 30, sf::Color::White, 60.f, 10.f);
    initializeTextObject(livesText, "Lives: " + std::to_string(lives), 30, sf::Color::White, Constants::SIZE_X - 60.f, 10.f);
    initializeTextObject(winText, "You Win!", 50, sf::Color::Green, Constants::SIZE_X / 2.f, Constants::SIZE_Y / 2.f);
    initializeTextObject(pauseText, "Paused", 50, sf::Color::Yellow, Constants::SIZE_X / 2.f, Constants::SIZE_Y / 2.f);
}

// Helper function to initialize a text object
void Game::initializeTextObject(sf::Text& text, const std::string& str, unsigned int size, sf::Color color, float x, float y) {
    text.setFont(font);
    text.setString(str);
    text.setCharacterSize(size);
    text.setFillColor(color);
    text.setStyle(sf::Text::Bold);
    text.setPosition(x - text.getGlobalBounds().width / 2.f, y - text.getGlobalBounds().height / 2.f);
}

// Toggle pause state
void Game::togglePause() {
    paused = !paused;
}

// Check for collisions between spaceship and asteroids
void Game::checkSpaceshipAsteroidCollision() {
    for (auto& asteroid : asteroids) {
        if (spaceship->checkCollision(asteroid)) {
            spaceship->isActive = false;
            asteroidHitSound.play();
            --lives;
            livesText.setString("Lives: " + std::to_string(lives));
            if (lives > 0) {
                spaceship->respawn();
            } else {
                gameOver();
            }
        }
    }
}

// Handle game over state
void Game::gameOver() {
    displayMessage(gameOverText);
    sf::sleep(sf::seconds(3));
    window->close();
}

// Run the game loop
void Game::run() {
    sf::Clock clock;
    while (window->isOpen()) {
        const float dt = clock.restart().asSeconds();
        handleEvents();
        if (gameState == GameState::PLAYING && !paused) {
            update(dt);
        }
        render();
    }
}

// Handle game events
void Game::handleEvents() {
    if (gameState == GameState::MENU) {
        handleMenuEvents();
    } else if (gameState == GameState::PLAYING) {
        handleGameEvents();
    }
}

// Handle menu events
void Game::handleMenuEvents() {
    sf::Event event{};
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Up) {
                menu.moveUp();
            } else if (event.key.code == sf::Keyboard::Down) {
                menu.moveDown();
            } else if (event.key.code == sf::Keyboard::Enter) {
                if (menu.getSelectedItemIndex() == 0) {
                    gameState = GameState::PLAYING;
                } else if (menu.getSelectedItemIndex() == 1) {
                    window->close();
                }
            }
        }
    }
}

// Handle game events
void Game::handleGameEvents() {
    sf::Event event{};
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::P) {
                togglePause();
            } else if (!paused && event.key.code == sf::Keyboard::Space) {
                handleBulletFire();
            }
        }
    }
}

// Handle bullet firing
void Game::handleBulletFire() {
    sf::Time currentTime = bulletClock.getElapsedTime();
    if (currentTime - lastBulletTime >= sf::seconds(bulletCooldown) && bullets.size() <= 5) {
        bulletFireSound.play();
        bullets.emplace_back(bulletTexture, spaceship->sprite.getPosition(), spaceship->sprite.getRotation());
        lastBulletTime = currentTime;
    }
}

// Update game state
void Game::update(const float dt) {
    if (spaceship->isActive) {
        spaceship->update(dt);
    }

    for (auto& asteroid : asteroids) {
        asteroid.update(dt);
    }

    for (auto& bullet : bullets) {
        bullet.update(dt);
    }

    bullets.erase(std::ranges::remove_if(bullets,
                                         [this](const Bullet& b) { return b.isOutOfBounds(*window); }).begin(),
                  bullets.end());

    checkCollisions();
}

// Render game objects
void Game::render() {
    window->clear();
    window->draw(backgroundSprite);
    if (gameState == GameState::MENU) {
        menu.draw(*window);
    } else if (gameState == GameState::PLAYING) {
        if (spaceship->isActive) {
            spaceship->draw(*window);
        }
        for (auto& asteroid : asteroids) {
            asteroid.draw(*window);
        }
        for (auto& bullet : bullets) {
            bullet.draw(*window);
        }
        window->draw(scoreText);
        window->draw(livesText);
        if (paused) {
            window->draw(pauseText);
        }
    }
    window->display();
}

// Generate random velocity for asteroids
sf::Vector2f generateRandomVelocity() {
    return sf::Vector2f(
        Utils::getRandomInRange(-Constants::maxAsteroidSpeed, Constants::maxAsteroidSpeed),
        Utils::getRandomInRange(-Constants::maxAsteroidSpeed, Constants::maxAsteroidSpeed)
    );
}

// Spawn a new asteroid
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

// Check for collisions between bullets and asteroids
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

// Check if the player has won the game
void Game::checkWinGame() {
    if (asteroids.empty()) {
        displayMessage(winText);
        sf::sleep(sf::seconds(3));
        window->close();
    }
}

// Display a message on the screen
void Game::displayMessage(const sf::Text& text) {
    window->clear();
    window->draw(backgroundSprite);
    window->draw(text);
    window->display();
}