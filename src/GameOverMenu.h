#pragma once
#include "PauseMenu.h"
#include "FileManager.h"
#include "Audio.h"

// �� �������� � MainMenu ������ ����� ����������� �� PauseMenu � ���������� �����������
class GameOverMenu : public PauseMenu
{
protected:
    // ��������� ���� ������� ����� ��������� � ���� ����
    GameScore game_score = { 0, 0, 1 };
    // ���� ������ ��� ������ �� �����
    sf::Text text_result;
    sf::Text text_score;
    sf::Text text_lines;
    sf::Text text_level;
    bool is_newrecord = false;

    FileManager file_manager;

public:
    // � ������������ �������������� ������ � �������������� ���� ������
    GameOverMenu(sf::RenderWindow& win, sf::Font& font, Audio& audio, sf::Sprite& backgroundSprite, int max_size = 2, std::initializer_list<std::string> init_list = { "PLAY AGAIN", "BACK TO MENU" }, float y_pos = 4.0f);

    void draw() override; // �������������� ����� ��� ����������� ���������� ����
    GameState getNextState() override;
    void handleEvents(sf::Event& event) override; // ��������� ������� �� ����� ���� ���������

    void setScore(GameScore score) { this->game_score = score; }

    // ��������� ����� � ����� ���� � ���� ������
    virtual void setUPtext();

    GameScore readRecord(); // ��������� ������ �� ����� � ������� ���

    void writeRecord(); // �������� ����� ������

    void checkNewRecord(); // ��������� ��� �� ����� ������
};

