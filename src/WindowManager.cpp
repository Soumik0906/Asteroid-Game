#include "WindowManager.h"

WindowManager::WindowManager(const unsigned int width, const unsigned int height, const std::string& title) {
    window = std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height), title);
}

std::unique_ptr<sf::RenderWindow>& WindowManager::getWindow() {
    return window;
}