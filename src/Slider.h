#pragma once
#include <SFML/Graphics.hpp>

// класс для создания ползунка - регулятор громкости
class Slider
{
private:
	sf::RenderWindow& window;
	sf::RectangleShape scrollBar; // ползунок
	sf::RectangleShape background; // фон позунка
	uint8_t value = 0; // текущее значение
	uint8_t max_value = 100; // максимальное значение
	uint8_t step = 5; // шаг на который изменяется значение
	uint16_t length = 0; // текущая длина ползунка
	sf::Vector2f size; // размеры ползунка

	void convert(); // по value посчитать длину ползунка: [0, 100] -> [0, size.x]
	void setNewLength(); // установить новую длину ползунка

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

