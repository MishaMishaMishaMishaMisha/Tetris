#pragma once
#include "PauseMenu.h"

// ������� ���� �������� �� ������ �� �������� ��� ���� �����
// ������ ����� ����������� PauseMenu ����� �� ������������� �� �� ������
class MainMenu : public PauseMenu
{
public:
    MainMenu(sf::RenderWindow& win, sf::Font& font, Audio& a, sf::Sprite& backgroundSprite);

    GameState getNextState() override; // ���� ����� ��������������
    void handleEvents(sf::Event& event) override; // ��������� ������� �� ����� ����
};

