#pragma once
#include "PauseMenu.h"
#include "Slider.h"

// меню опций
class OptionsMenu : public PauseMenu
{
private:
    GameState prev_state = GameState::MainMenu; // пред. окно, чтобы знать откуда зашли в настройки - из меню или паузы
    sf::RectangleShape controlsImage;
    Slider soundBar;
    Slider musicBar;

public:
    OptionsMenu(sf::RenderWindow& win, sf::Font& font, Audio& a, sf::Sprite& backgroundSprite, sf::Texture& texture_cont);

    GameState getNextState() override; // этот метод переопределяем
    void handleEvents(sf::Event& event) override; // обработка нажатий во время меню
    void draw() override;
    void setPrevState(GameState prev) { prev_state = prev; }
};


