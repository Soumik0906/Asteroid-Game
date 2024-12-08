#include "TextManager.h"

void TextManager::initializeTextObjects(sf::Font& font, int lives) {
    initializeTextObject(gameOverText, "Game Over!", GAME_OVER_SIZE, sf::Color::Red, GAME_OVER_X, GAME_OVER_Y, font);
    initializeTextObject(scoreText, "Score: 0", SCORE_SIZE, sf::Color::White, SCORE_X, SCORE_Y, font);
    initializeTextObject(livesText, "Lives: " + std::to_string(lives), LIVES_SIZE, sf::Color::White, LIVES_X, LIVES_Y, font);
    initializeTextObject(winText, "You Win!", WIN_SIZE, sf::Color::Green, WIN_X, WIN_Y, font);
    initializeTextObject(pauseText, "Paused", PAUSE_SIZE, sf::Color::Yellow, PAUSE_X, PAUSE_Y, font);
}

void TextManager::initializeTextObject(sf::Text& text, const std::string& str, unsigned int size, sf::Color color, float x, float y, sf::Font& font) {
    text.setFont(font);
    text.setString(str);
    text.setCharacterSize(size);
    text.setFillColor(color);
    text.setStyle(sf::Text::Bold);
    text.setPosition(x - text.getGlobalBounds().width / 2.f, y - text.getGlobalBounds().height / 2.f);
}

sf::Text& TextManager::getPauseText() { return pauseText; }
sf::Text& TextManager::getGameOverText() { return gameOverText; }
sf::Text& TextManager::getScoreText() { return scoreText; }
sf::Text& TextManager::getLivesText() { return livesText; }
sf::Text& TextManager::getWinText() { return winText; }