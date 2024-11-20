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
	int8_t moveSide, moveDown;

	bool gameOver = false; // ���� ��������� ����
	bool moveLast = false; // ���� ��������: ����� ������ ����� ����, ���� ��� ����� ����� �� �������� � �������
	uint16_t moveSideCount; // ���������� ������� � ������� �� ���� ��������

	// �������� ������� ������ �� �������
	sf::Clock clock;
	float time;

	bool isPVP = false; // ��������� ��� pvp ����

public:
	Game(uint16_t height, uint16_t width, sf::RenderWindow& win, Audio& a, sf::Sprite& backgroundSprite, sf::Font& font, FieldPosition f_pos = FieldPosition::Center);

	void draw() override;
	void handleEvents(sf::Event& event) override; // ��������� ������� �� ����� ����
	void restart(); // ������ ��� �������

	GameState getNextState() override;

	void set_Active() override;

	GameScore getScore() { return field.getScore(); }

	void setControlsMode(ControlsMode mode); // �������� ���������� - �������/wasd/��� ����

	void setSeed(uint32_t seed);

	bool isGameOver() { return gameOver; }



	Field& getField() { return field; }
};

