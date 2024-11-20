#include "MainMenu.h"

// передаем в констуктор PauseMenu количество кнопок - 6 и их названия, изменяем положение на экране - y_pos=1.4, 
MainMenu::MainMenu(sf::RenderWindow& win, sf::Font& font, Audio& a, sf::Sprite& backgroundSprite) :
    PauseMenu(win, font, a, backgroundSprite, 6, { "PLAY", "PLAY PVP LOCAL", "PLAY PVP ONLINE", "OPTIONS", "HIGHSCORES", "EXIT"}, 1.4f) {}

void MainMenu::handleEvents(sf::Event& event)
{

    if (event.type == sf::Event::KeyPressed)
    {
        if (controls.button_enter(event))
        {
            isActive = false;
        }
        else if (controls.button_down(event))
        {
            moveDown();
        }
        else if (controls.button_up(event))
        {
            moveUp();
        }
    }
}

GameState MainMenu::getNextState()
{
    if (selected_button == 0)
    {
        // начать игру
        return GameState::GamePlaying;
    }
    else if (selected_button == 1)
    {
        // pvp local
        return GameState::GamePlayingPvPLocal;
    }
    else if (selected_button == 2)
    {
        // pvp online
        return GameState::GamePlayingPvPOnline;
    }
    else if (selected_button == 3)
    {
        // настройки
        return GameState::OptionsMenu;
    }
    else if (selected_button == 4)
    {
        // highscore menu
        return GameState::HighscoreMenu;
    }
    //else if (selected_button == 5)
    else
    {
        // выход
        return GameState::Exit;
    }
}

