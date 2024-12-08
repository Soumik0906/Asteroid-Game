#include "Game.h"
#include "Utilities.h"
#include <SFML/Audio.hpp>
#include <optional>
#include <memory>

Game::Game()
    : windowManager(Constants::windowWidth, Constants::windowHeight, "Asteroids"),
      lives(5), score(0), paused(false), bulletCooldown(0.05f), gameState(GameState::MENU),
      menu(Constants::windowWidth, Constants::windowHeight), settings(Constants::windowWidth, Constants::windowHeight) {

    resourceManager.loadResources();
    gameObjectManager.initializeGameObjects(resourceManager.getSpaceshipTexture(), resourceManager.getExhaustTexture(), resourceManager.getAsteroidTexture(), resourceManager.getBackgroundTexture(), *windowManager.getWindow());
    textManager.initializeTextObjects(resourceManager.getFont(), lives);
    bulletFireSound.setBuffer(resourceManager.getBulletFireBuffer());
    asteroidHitSound.setBuffer(resourceManager.getAsteroidHitBuffer());
    lastBulletTime = bulletClock.getElapsedTime();
}

void Game::run() {
    sf::Clock clock;
    while (windowManager.getWindow()->isOpen()) {
        const float dt = clock.restart().asSeconds();
        handleEvents();
        if (gameState == GameState::PLAYING && !paused) {
            update(dt);
        }
        render();
    }
}

void Game::handleEvents() {
    if (gameState == GameState::MENU) {
        handleMenuEvents();
    } else if (gameState == GameState::PLAYING) {
        handleGameEvents();
    } else if (gameState == GameState::SETTINGS) {
        handleSettingsEvents();
    }
}

void Game::handleMenuEvents() {
    sf::Event event{};
    while (windowManager.getWindow()->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            windowManager.getWindow()->close();
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Up) {
                menu.moveUp();
            } else if (event.key.code == sf::Keyboard::Down) {
                menu.moveDown();
            } else if (event.key.code == sf::Keyboard::Enter) {
                if (menu.getSelectedItemIndex() == 0) {
                    gameState = GameState::PLAYING;
                    menu.toggleMusic();
                } else if (menu.getSelectedItemIndex() == 1) {
                    gameState = GameState::SETTINGS;
                } else if (menu.getSelectedItemIndex() == 2) {
                    windowManager.getWindow()->close();
                }
            }
        }
    }
}

void Game::handleGameEvents() {
    sf::Event event{};
    while (windowManager.getWindow()->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            windowManager.getWindow()->close();
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

void Game::handleBulletFire() {
    sf::Time currentTime = bulletClock.getElapsedTime();
    if (currentTime - lastBulletTime >= sf::seconds(bulletCooldown) && gameObjectManager.getBullets().size() <= 5) {
        bulletFireSound.play();
        gameObjectManager.getBullets().emplace_back(resourceManager.getBulletTexture(), gameObjectManager.getSpaceship()->sprite.getPosition(), gameObjectManager.getSpaceship()->sprite.getRotation());
        lastBulletTime = currentTime;
    }
}

void Game::update(const float dt) {
    if (gameObjectManager.getSpaceship()->isActive) {
        gameObjectManager.getSpaceship()->update(dt);
    }

    for (auto& asteroid : gameObjectManager.getAsteroids()) {
        asteroid.update(dt);
    }

    for (auto& bullet : gameObjectManager.getBullets()) {
        bullet.update(dt);
    }

    gameObjectManager.getBullets().erase(std::remove_if(gameObjectManager.getBullets().begin(), gameObjectManager.getBullets().end(),
                                                        [this](const Bullet& b) { return b.isOutOfBounds(*windowManager.getWindow()); }),
                                         gameObjectManager.getBullets().end());

    checkCollisions();
}

void Game::render() {
    windowManager.getWindow()->clear();
    windowManager.getWindow()->draw(gameObjectManager.getBackgroundSprite());
    if (gameState == GameState::MENU) {
        menu.draw(*windowManager.getWindow());
    } else if (gameState == GameState::PLAYING) {
        if (gameObjectManager.getSpaceship()->isActive) {
            gameObjectManager.getSpaceship()->draw(*windowManager.getWindow());
            windowManager.getWindow()->draw(gameObjectManager.getSpaceship()->getFireSprite());
        }
        for (auto& asteroid : gameObjectManager.getAsteroids()) {
            asteroid.draw(*windowManager.getWindow());
        }
        for (auto& bullet : gameObjectManager.getBullets()) {
            bullet.draw(*windowManager.getWindow());
        }
        windowManager.getWindow()->draw(textManager.getScoreText());
        windowManager.getWindow()->draw(textManager.getLivesText());
        if (paused) {
            windowManager.getWindow()->draw(textManager.getPauseText());
        }
    } else if (gameState == GameState::SETTINGS) {
        settings.draw(*windowManager.getWindow());
    }
    windowManager.getWindow()->display();
}

void Game::togglePause() {
    paused = !paused;
}

void Game::checkSpaceshipAsteroidCollision() {
    for (auto& asteroid : gameObjectManager.getAsteroids()) {
        if (gameObjectManager.getSpaceship()->checkCollision(asteroid)) {
            gameObjectManager.getSpaceship()->isActive = false;
            asteroidHitSound.play();
            --lives;
            textManager.getLivesText().setString("Lives: " + std::to_string(lives));
            if (lives > 0) {
                gameObjectManager.getSpaceship()->respawn();
            } else {
                gameOver();
            }
        }
    }
}

void Game::gameOver() {
    displayMessage(textManager.getGameOverText());
    sf::sleep(sf::seconds(3));
    windowManager.getWindow()->close();
}

void Game::checkCollisions() {
    checkSpaceshipAsteroidCollision();

    for (auto& bullet : gameObjectManager.getBullets()) {
        for (auto& asteroid : gameObjectManager.getAsteroids()) {
            if (bullet.isActive && asteroid.isActive && bullet.getBounds().intersects(asteroid.getBounds())) {
                asteroidHitSound.play();

                bullet.isActive = false;
                asteroid.isActive = false;

                score += asteroid.size * 10;
                textManager.getScoreText().setString("Score: " + std::to_string(score));

                if (asteroid.size > 1) {
                    for (int i { 0 }; i < Utils::getRandomInRange(2, 5); ++i) {
                        gameObjectManager.spawnAsteroid(asteroid.size - 1, resourceManager.getAsteroidTexture(), asteroid.sprite.getPosition());
                    }
                }
            }
        }
    }

    gameObjectManager.getAsteroids().erase(std::remove_if(gameObjectManager.getAsteroids().begin(), gameObjectManager.getAsteroids().end(),
                                                          [](const Asteroid& asteroid) { return !asteroid.isActive; }),
                                           gameObjectManager.getAsteroids().end());

    checkWinGame();
}

void Game::checkWinGame() {
    if (gameObjectManager.getAsteroids().empty()) {
        displayMessage(textManager.getWinText());
        sf::sleep(sf::seconds(3));
        windowManager.getWindow()->close();
    }
}

void Game::displayMessage(const sf::Text& text) {
    windowManager.getWindow()->clear();
    windowManager.getWindow()->draw(gameObjectManager.getBackgroundSprite());
    windowManager.getWindow()->draw(text);
    windowManager.getWindow()->display();
}

void Game::handleSettingsEvents() {
    sf::Event event{};
    while (windowManager.getWindow()->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            windowManager.getWindow()->close();
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Up) {
                settings.moveUp();
            } else if (event.key.code == sf::Keyboard::Down) {
                settings.moveDown();
            } else if (event.key.code == sf::Keyboard::Enter) {
                if (settings.getSelectedItemIndex() == 2) {
                    gameState = GameState::MENU;
                }
            }
        }
    }
}