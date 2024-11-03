#include "HighscoreMenu.h"

HighscoreMenu::HighscoreMenu(sf::RenderWindow& win, sf::Font& font, Audio& a, sf::Sprite& backgroundSprite) :
    GameOverMenu(win, font, a, backgroundSprite, 1, { "BACK" })
{
    // выделяем кнопку
    buttons[0].setFillColor(sf::Color(170, 70, 70));
    // изменяем надпись
    text_result.setString("YOUR RECORD");
}

void HighscoreMenu::handleEvents(sf::Event& event)
{

    if (event.type == sf::Event::KeyPressed)
    {
        if (controls.button_enter(event) || controls.button_escape(event))
        {
            isActive = false;
        }
    }
}

GameState HighscoreMenu::getNextState()
{
    return GameState::MainMenu;
}

void HighscoreMenu::setUPtext()
{
    text_result.setString("YOUR RECORD");
    text_score.setString("SCORE - " + std::to_string(game_score.score));
    text_lines.setString("LINES - " + std::to_string(game_score.lines));
    text_level.setString("LEVEL - " + std::to_string(game_score.level));
}