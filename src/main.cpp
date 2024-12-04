#include "Game.h"
#include <filesystem>
#include <iostream>

int main() {
    std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;
    Game game;
    game.run();
    return 0;
}
