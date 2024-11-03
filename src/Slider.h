#pragma once
#include <SFML/Graphics.hpp>

// класс для создания ползунка - регулятор громкости
class Slider
{
private:
	sf::RenderWindow& window;
	sf::RectangleShape scrollBar; // ползунок
	sf::RectangleShape background; // фон позунка
	int value = 0; // текущее значение
	int max_value = 100; // максимальное значение
	int step = 5; // шаг на который изменяется значение
	int length = 0; // текущая длина ползунка
	sf::Vector2f size; // размеры ползунка

	void convert(); // по value посчитать длину ползунка: [0, 100] -> [0, size.x]
	void setNewLength(); // установить новую длину ползунка

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

