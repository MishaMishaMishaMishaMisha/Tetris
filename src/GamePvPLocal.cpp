#include "GamePvPLocal.h"

GamePvPLocal::GamePvPLocal(uint16_t height, uint16_t width, sf::RenderWindow& win, Audio& a, sf::Sprite& backgroundSprite, sf::Font& font) :
    BaseWindow(a, backgroundSprite, win),
    game_left(height, width, win, a, backgroundSprite, font, FieldPosition::Left),
    game_right(height, width, win, a, backgroundSprite, font, FieldPosition::Right)
{
    // центральна€ лини€
    centerLine.setSize(sf::Vector2f(5, height)); // “олщина 5
    centerLine.setPosition(width / 2.f, 0.f);
    centerLine.setFillColor(sf::Color::White);

    // измен€ем тип управлени€ дл€ каждого игрока
    game_left.setControlsMode(ControlsMode::WASD);
    game_right.setControlsMode(ControlsMode::ARROWS);
}

void GamePvPLocal::draw()
{
    if (game_left.isGameOver() && game_right.isGameOver())
    {
        audio.stopMusic();
        isActive = false;
    }

    window.draw(backgroundSprite); // фон
    // пол€
    game_left.draw();
    game_right.draw();
    // центральна€ лини€
    window.draw(centerLine); 
}

void GamePvPLocal::handleEvents(sf::Event& event)
{
    game_left.handleEvents(event);
    game_right.handleEvents(event);

    if (event.type == sf::Event::KeyPressed)
    {
        if (controls.button_escape(event))
        {
            audio.playPauseEffect();
            audio.pauseMusic(true);
            isActive = false;
        }
    }
}

GameState GamePvPLocal::getNextState()
{
    if (game_left.isGameOver() && game_right.isGameOver())
    {
        return GameState::GameoverPvPMenu;
    }
    return GameState::PauseMenu;
}

void GamePvPLocal::restart()
{
    uint32_t seed = static_cast<uint32_t>(time(0));
    game_left.setSeed(seed);
    game_right.setSeed(seed);
    game_left.restart();
    game_right.restart();
    audio.stopMusic();
}

void GamePvPLocal::set_Active()
{
    audio.playMusic();
    isActive = true;
}