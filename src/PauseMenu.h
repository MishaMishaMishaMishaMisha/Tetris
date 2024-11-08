#pragma once
#include "BaseWindow.h"
#include <initializer_list>

class PauseMenu : public BaseWindow
{
protected:
	sf::RenderWindow& window;
	sf::Font& font; // ����� ������ �� �������
	int max_size; // ���������� ������ �� ������ �����
	std::vector<sf::Text> buttons;
	std::vector<std::string> names; // �������� ������
	int selected_button = 0;

	void highlightButton(); // �������� ��������� ������ ������ ������
	void resetButtonsColor(); // ������� �������� �����
	void init(float y_pos); // ������������� ������;

public:
	PauseMenu(sf::RenderWindow& win, sf::Font& font, Audio& a, sf::Sprite& backgroundSprite, int max_size = 3, std::initializer_list<std::string> initList = { "CONTINUE", "OPTIONS", "MAIN MENU" }, float y_pos = 2.0f);

	void draw() override;
	void handleEvents(sf::Event& event) override;
	GameState getNextState() override;
	void set_Active() override;

	void moveUp(); // ����������� �� ������ ����
	void moveDown(); // ����������� �� ������ ����
};

