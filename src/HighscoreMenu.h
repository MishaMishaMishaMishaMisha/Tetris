#pragma once
#include "GameOverMenu.h"

// ������� ���� �������� �� ������ �� �������� ��� ���� �����
// ������ ����� ����������� PauseMenu ����� �� ������������� �� �� ������
class HighscoreMenu : public GameOverMenu
{

public:
    HighscoreMenu(sf::RenderWindow& win, sf::Font& font, Audio& a, sf::Sprite& backgroundSprite); // ����������� � ������� ����� �������������� ������

    GameState getNextState() override; // ���� ����� ��������������
    void handleEvents(sf::Event& event) override; // ��������� ������� �� ����� ����
    void setUPtext() override;
};




