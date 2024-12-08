#include "MenuBase.h"

MenuBase::MenuBase(float width, float height, const std::vector<std::string>& items) : selectedItemIndex(0) {
    if (!font.loadFromFile("../../assets/fonts/arial.ttf")) {
        throw std::runtime_error("Failed to load arial.ttf");
    }

    for (size_t i = 0; i < items.size(); ++i) {
        sf::Text text;
        text.setFont(font);
        text.setString(items[i]);
        text.setCharacterSize(50);
        text.setFillColor(i == 0 ? sf::Color::Red : sf::Color::White);
        text.setPosition(sf::Vector2f(width / 2.f - text.getGlobalBounds().width / 2.f, height / (items.size() + 1) * (i + 1)));
        menuItems.push_back(text);
    }
}

void MenuBase::draw(sf::RenderWindow& window) {
    for (const auto& item : menuItems) {
        window.draw(item);
    }
}

void MenuBase::moveUp() {
    menuItems[selectedItemIndex].setFillColor(sf::Color::White);
    selectedItemIndex = (selectedItemIndex - 1 + menuItems.size()) % menuItems.size();
    menuItems[selectedItemIndex].setFillColor(sf::Color::Red);
}

void MenuBase::moveDown() {
    menuItems[selectedItemIndex].setFillColor(sf::Color::White);
    selectedItemIndex = (selectedItemIndex + 1) % menuItems.size();
    menuItems[selectedItemIndex].setFillColor(sf::Color::Red);
}

int MenuBase::getSelectedItemIndex() const {
    return selectedItemIndex;
}