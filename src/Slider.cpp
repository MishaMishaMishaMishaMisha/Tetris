#include "Slider.h"

Slider::Slider(sf::RenderWindow& win) : window(win)
{
	scrollBar.setFillColor(sf::Color::White);
	background.setFillColor(sf::Color(200, 200, 200, 50));
}

void Slider::setValue(int value) 
{ 
	this->value = value; 
}

void Slider::setMaxValue(int value)
{
	this->max_value = value;
}

void Slider::setStep(int step) 
{ 
	this->step = step; 
}

void Slider::increase()
{
	if (value < max_value)
	{
		value += step;
		if (value > max_value)
		{
			value = max_value;
		}
		convert();
		setNewLength();
	}
}

void Slider::decrease()
{
	if (value > 0)
	{
		value -= step;
		if (value < 0)
		{
			value = 0;
		}
		convert();
		setNewLength();
	}
}

void Slider::setPosition(int x, int y)
{
	scrollBar.setPosition(x, y);
	background.setPosition(x, y);
}

void Slider::setSize(sf::Vector2f size)
{
	this->size = size;
	background.setSize(size);
	convert();
	setNewLength();
}

void Slider::drawBar()
{
	window.draw(background);
	window.draw(scrollBar);
}

void Slider::convert()
{
	length = static_cast<int>(value / 100.0 * size.x);
}

void Slider::setNewLength()
{
	scrollBar.setSize(sf::Vector2f(length, size.y));
}