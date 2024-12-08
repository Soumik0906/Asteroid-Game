#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include <SFML/Graphics.hpp>
#include <memory>

class WindowManager {
public:
    WindowManager(unsigned int width, unsigned int height, const std::string& title);
    std::unique_ptr<sf::RenderWindow>& getWindow();

private:
    std::unique_ptr<sf::RenderWindow> window;
};

#endif // WINDOW_MANAGER_H