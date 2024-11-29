#pragma once
#include "GameOverMenu.h"

// ������� ���� �������� �� ������ �� �������� ��� ���� �����
// ������ ����� ����������� PauseMenu ����� �� ������������� �� �� ������
class HighscoreMenu : public GameOverMenu
{
private:
    sf::Text text_count_games;
    sf::Text text_count_wins;
    sf::Text text_winrate;

public:
    HighscoreMenu(sf::RenderWindow& win, sf::Font& font, Audio& a, sf::Sprite& backgroundSprite); // ����������� � ������� ����� �������������� ������

    void draw() override;
    GameState getNextState() override; // ���� ����� ��������������
    void handleEvents(sf::Event& event) override; // ��������� ������� �� ����� ����
    void setUPtext() override;
};




