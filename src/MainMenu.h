#pragma once
#include "PauseMenu.h"

// главное меню устроена по такому же принципу как меню паузы
// делаем класс наследником PauseMenu чтобы не реализовывать те же методы
class MainMenu : public PauseMenu
{
public:
    MainMenu(sf::RenderWindow& win, sf::Font& font, Audio& a, sf::Sprite& backgroundSprite);

    GameState getNextState() override; // этот метод переопределяем
    void handleEvents(sf::Event& event) override; // обработка нажатий во время меню
};

