#pragma once
#include "PauseMenu.h"
#include "FileManager.h"

class GameOverPvPMenu : public PauseMenu
{
private:
	GameScore game_score_left;
	GameScore game_score_right;
	GameScore winner;

	sf::Text text_result_left;
	sf::Text text_score_left;
	sf::Text text_lines_left;
	sf::Text text_level_left;

	sf::Text text_result_right;
	sf::Text text_score_right;
	sf::Text text_lines_right;
	sf::Text text_level_right;

	// ���� ���� �� ������� ����� ������� �� ������� ����
	FileManager file_manager;
	bool is_newrecord = false;

public:
	GameOverPvPMenu(sf::RenderWindow& win, sf::Font& font, Audio& audio, sf::Sprite& backgroundSprite, uint8_t max_size = 2, std::initializer_list<std::string> init_list = { "PLAY AGAIN", "BACK TO MENU" }, float y_pos = 4.0f);

	void draw() override; // �������������� ����� ��� ����������� ���������� ����
	GameState getNextState() override;
	void handleEvents(sf::Event& event) override; // ��������� ������� �� ����� ���� ���������

	void setScore_left(GameScore score) { this->game_score_left = score; }
	void setScore_right(GameScore score) { this->game_score_right = score; }

	// ��������� ����� � ����� ���� � ���� ������
	void setUPtext();

	// �������� �� �� ����� �� ������
	GameScore readRecord(); // ��������� ������ �� ����� � ������� ���
	void writeRecord(); // �������� ����� ������
	void checkNewRecord(); // ��������� ��� �� ����� ������
};

