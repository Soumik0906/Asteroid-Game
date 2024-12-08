#ifndef MENU_BASE_H
#define MENU_BASE_H

#include <SFML/Graphics.hpp>
#include <vector>

class MenuBase {
public:
    MenuBase(float width, float height, const std::vector<std::string>& items);
    virtual ~MenuBase() = default;

    void draw(sf::RenderWindow& window);
    void moveUp();
    void moveDown();
    int getSelectedItemIndex() const;

protected:
    int selectedItemIndex;
    sf::Font font;
    std::vector<sf::Text> menuItems;
};

#endif // MENU_BASE_H