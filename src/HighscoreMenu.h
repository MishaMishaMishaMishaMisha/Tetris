#pragma once
#include "GameOverMenu.h"

// главное меню устроена по такому же принципу как меню паузы
// делаем класс наследником PauseMenu чтобы не реализовывать те же методы
class HighscoreMenu : public GameOverMenu
{
private:
    sf::Text text_count_games;
    sf::Text text_count_wins;
    sf::Text text_winrate;

public:
    HighscoreMenu(sf::RenderWindow& win, sf::Font& font, Audio& a, sf::Sprite& backgroundSprite); // констурктор в котором нужно переопределить кнопки

    void draw() override;
    GameState getNextState() override; // этот метод переопределяем
    void handleEvents(sf::Event& event) override; // обработка нажатий во время меню
    void setUPtext() override;
};




