#pragma once
#include <SFML/Graphics.hpp>

// ����� ��� �������� �������� - ��������� ���������
class Slider
{
private:
	sf::RenderWindow& window;
	sf::RectangleShape scrollBar; // ��������
	sf::RectangleShape background; // ��� �������
	uint8_t value = 0; // ������� ��������
	uint8_t max_value = 100; // ������������ ��������
	uint8_t step = 5; // ��� �� ������� ���������� ��������
	uint16_t length = 0; // ������� ����� ��������
	sf::Vector2f size; // ������� ��������

	void convert(); // �� value ��������� ����� ��������: [0, 100] -> [0, size.x]
	void setNewLength(); // ���������� ����� ����� ��������

public:
	Slider(sf::RenderWindow& win);

	void setValue(uint8_t value);
	void setMaxValue(uint8_t value);
	void setStep(uint8_t step);
	uint8_t getValue() { return value; }
	void increase();
	void decrease();
	void setPosition(float x, float y);
	void setSize(sf::Vector2f size);
	void drawBar();
};

