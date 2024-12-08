#ifndef TEXT_MANAGER_H
#define TEXT_MANAGER_H

#include "Utilities.h"
#include <SFML/Graphics.hpp>
#include <string>

class TextManager {
public:
    void initializeTextObjects(sf::Font& font, int lives);
    sf::Text& getPauseText();
    sf::Text& getGameOverText();
    sf::Text& getScoreText();
    sf::Text& getLivesText();
    sf::Text& getWinText();

private:
    sf::Text pauseText, gameOverText, scoreText, livesText, winText;
    void initializeTextObject(sf::Text& text, const std::string& str, unsigned int size, sf::Color color, float x, float y, sf::Font& font);

    static constexpr float GAME_OVER_X = Constants::SIZE_X / 2.f;
    static constexpr float GAME_OVER_Y = Constants::SIZE_Y / 2.f;
    static constexpr float SCORE_X = 60.f;
    static constexpr float SCORE_Y = 10.f;
    static constexpr float LIVES_X = Constants::SIZE_X - 60.f;
    static constexpr float LIVES_Y = 10.f;
    static constexpr float WIN_X = Constants::SIZE_X / 2.f;
    static constexpr float WIN_Y = Constants::SIZE_Y / 2.f;
    static constexpr float PAUSE_X = Constants::SIZE_X / 2.f;
    static constexpr float PAUSE_Y = Constants::SIZE_Y / 2.f;
    static constexpr unsigned int GAME_OVER_SIZE = 50;
    static constexpr unsigned int SCORE_SIZE = 30;
    static constexpr unsigned int LIVES_SIZE = 30;
    static constexpr unsigned int WIN_SIZE = 50;
    static constexpr unsigned int PAUSE_SIZE = 50;
};

#endif // TEXT_MANAGER_H