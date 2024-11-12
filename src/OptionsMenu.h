#pragma once
#include "PauseMenu.h"
#include "Slider.h"

// ���� �����
class OptionsMenu : public PauseMenu
{
private:
    sf::RectangleShape controlsImage;
    Slider soundBar;
    Slider musicBar;

public:
    OptionsMenu(sf::RenderWindow& win, sf::Font& font, Audio& a, sf::Sprite& backgroundSprite, sf::Texture& texture_cont);

    GameState getNextState() override; // ���� ����� ��������������
    void handleEvents(sf::Event& event) override; // ��������� ������� �� ����� ����
    void draw() override;
};


