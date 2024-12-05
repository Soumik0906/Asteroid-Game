#include "Game.h"

Game::Game() : window(sf::VideoMode(800u, 600u), "Asteroids") {
    spaceshipTexture.loadFromFile("../assets/images/spaceship.png");
    asteroidTexture.loadFromFile("../assets/images/asteroid.png");
    bulletTexture.loadFromFile("../assets/images/bullet.png");

    spaceship = new Spaceship(spaceshipTexture);
    spaceship->sprite.setScale(1.5f, 1.5f);

    // Initial asteroids
    for (int i = 0; i < 5; ++i)
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
    spaceship->draw(window);
    for (auto& asteroid : asteroids)
        asteroid.draw(window);
    for (auto& bullet : bullets)
        bullet.draw(window);
    window.display();
}

void Game::spawnAsteroid(int size) {
    sf::Vector2f position(rand() % 800, rand() % 600);
    sf::Vector2f velocity(rand() % 100 - 50, rand() % 100 - 50);
    asteroids.emplace_back(asteroidTexture, size, position, velocity);
}

void Game::spawnAsteroid(int size, const sf::Vector2f& position) {
    sf::Vector2f velocity(rand() % 100 - 50, rand() % 100 - 50);
    asteroids.emplace_back(asteroidTexture, size, position, velocity);
}

void Game::checkCollisions() {
    for (auto& bullet : bullets) {
        for (auto& asteroid : asteroids) {
            if (bullet.isActive && asteroid.isActive && bullet.getBounds().intersects(asteroid.getBounds())) {
                bullet.isActive = false;
                asteroid.isActive = false;

                // Generate more asteroids in the same position that are smaller in size
                if (asteroid.size > 1) {
                    spawnAsteroid(asteroid.size - 1, asteroid.sprite.getPosition());
                    spawnAsteroid(asteroid.size - 1, asteroid.sprite.getPosition());
                }
            }
        }
    }
}
