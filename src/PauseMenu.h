#pragma once
#include "BaseWindow.h"
#include <initializer_list>

class PauseMenu : public BaseWindow
{
protected:
	sf::Font& font; // ����� ������ �� �������
	uint8_t max_size; // ���������� ������ �� ������ �����
	std::vector<sf::Text> buttons;
	std::vector<std::string> names; // �������� ������
	int8_t selected_button = 0;

	void highlightButton(); // �������� ��������� ������ ������ ������
	void resetButtonsColor(); // ������� �������� �����
	void init(float y_pos); // ������������� ������;

	// ����. ����, ����� ����� ������ ����� � ���� ����� - �� ��������� ���� ��� pvp ����
	GameState prev_state = GameState::MainMenu;

public:
	PauseMenu(sf::RenderWindow& win, sf::Font& font, Audio& a, sf::Sprite& backgroundSprite, uint8_t max_size = 3, std::initializer_list<std::string> initList = { "CONTINUE", "OPTIONS", "MAIN MENU" }, float y_pos = 2.0f);

	void draw() override;
	void handleEvents(sf::Event& event) override;
	GameState getNextState() override;
	void set_Active() override;

	void moveUp(); // ����������� �� ������ ����
	void moveDown(); // ����������� �� ������ ����

	void setPrevState(GameState prev) { prev_state = prev; }
};

