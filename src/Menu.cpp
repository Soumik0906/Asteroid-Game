#include "Menu.h"

Menu::Menu(float width, float height) : MenuBase(width, height, {"PLAY", "SETTINGS", "EXIT"}) {
    if (!backgroundMusic.openFromFile("../../assets/sounds/menu_music.ogg")) {
        throw std::runtime_error("Failed to load menu_music.ogg");
    }

    toggleMusic();
}

void Menu::toggleMusic() {
    if (backgroundMusic.getStatus() == sf::Music::Playing) {
        backgroundMusic.stop();
    } else {
        backgroundMusic.setLoop(true);
        backgroundMusic.play();
    }
}