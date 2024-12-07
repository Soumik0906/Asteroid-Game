#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>


class Menu {
public:
    Menu(float width, float height);
    void draw(sf::RenderWindow& window);
    void moveUp();
    void moveDown();
    int getSelectedItemIndex() const;
    void toggleMusic();

private:
    int selectedItemIndex;
    sf::Font font;
    std::vector<sf::Text> menuItems;
    sf::Music backgroundMusic;
};

#endif // MENU_H