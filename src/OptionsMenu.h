#pragma once
#include "PauseMenu.h"
#include "Slider.h"

// меню опций
class OptionsMenu : public PauseMenu
{
private:
    sf::RectangleShape controlsImage;
    Slider soundBar;
    Slider musicBar;

public:
    OptionsMenu(sf::RenderWindow& win, sf::Font& font, Audio& a, sf::Sprite& backgroundSprite, sf::Texture& texture_cont);

    GameState getNextState() override; // этот метод переопределяем
    void handleEvents(sf::Event& event) override; // обработка нажатий во время меню
    void draw() override;
};


