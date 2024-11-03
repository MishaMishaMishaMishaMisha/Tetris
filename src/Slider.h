#pragma once
#include <SFML/Graphics.hpp>

// ����� ��� �������� �������� - ��������� ���������
class Slider
{
private:
	sf::RenderWindow& window;
	sf::RectangleShape scrollBar; // ��������
	sf::RectangleShape background; // ��� �������
	int value = 0; // ������� ��������
	int max_value = 100; // ������������ ��������
	int step = 5; // ��� �� ������� ���������� ��������
	int length = 0; // ������� ����� ��������
	sf::Vector2f size; // ������� ��������

	void convert(); // �� value ��������� ����� ��������: [0, 100] -> [0, size.x]
	void setNewLength(); // ���������� ����� ����� ��������

public:
	Slider(sf::RenderWindow& win);

	void setValue(int value);
	void setMaxValue(int value);
	void setStep(int step);
	int getValue() { return value; }
	void increase();
	void decrease();
	void setPosition(int x, int y);
	void setSize(sf::Vector2f size);
	void drawBar();
};

