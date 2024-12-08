#ifndef MENU_H
#define MENU_H

#include "MenuBase.h"
#include <SFML/Audio.hpp>

class Menu : public MenuBase {
public:
    Menu(float width, float height);
    void toggleMusic();

private:
    sf::Music backgroundMusic;
};

#endif // MENU_H