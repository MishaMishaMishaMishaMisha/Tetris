#pragma once
#include "Field.h"
#include "Audio.h"
#include "BaseWindow.h"


// ���� ���� � ������
class Game : public BaseWindow
{
private:
	Field field;

	// ���������� ��� ������ ������ � �������: 1 ������, -1 �����, 0 �� �����
	// moveDown - ���������� ������� �����
	int moveSide, moveDown;

	bool gameOver = false; // ���� ��������� ����
	bool moveLast = false; // ���� ��������: ����� ������ ����� ����, ���� ��� ����� ����� �� �������� � �������
	int moveSideCount; // ���������� ������� � ������� �� ���� ��������

	// �������� ������� ������ �� �������
	sf::Clock clock;
	float time;

	bool isPVP = false; // ��������� ��� pvp ����

public:
	Game(int height, int width, sf::RenderWindow& win, Audio& a, sf::Sprite& backgroundSprite, sf::Font& font, FieldPosition f_pos = FieldPosition::Center);

	void draw() override;
	void handleEvents(sf::Event& event) override; // ��������� ������� �� ����� ����
	void restart(); // ������ ��� �������

	GameState getNextState() override;

	void set_Active() override;

	GameScore getScore() { return field.getScore(); }

	void setControlsMode(ControlsMode mode); // �������� ���������� - �������/wasd/��� ����

	void setSeed(unsigned int seed);

	bool isGameOver() { return gameOver; }
};

