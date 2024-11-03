#pragma once
#include "GameOverMenu.h"

// главное меню устроена по такому же принципу как меню паузы
// делаем класс наследником PauseMenu чтобы не реализовывать те же методы
class HighscoreMenu : public GameOverMenu
{

public:
    HighscoreMenu(sf::RenderWindow& win, sf::Font& font, Audio& a, sf::Sprite& backgroundSprite); // констурктор в котором нужно переопределить кнопки

    GameState getNextState() override; // этот метод переопределяем
    void handleEvents(sf::Event& event) override; // обработка нажатий во время меню
    void setUPtext() override;
};




