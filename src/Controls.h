#pragma once
#include <SFML/Graphics.hpp>

// класс для управления игрой
class Controls
{
public:
	bool button_up(sf::Event& event);
	bool button_down(sf::Event& event);
	bool button_right(sf::Event& event);
	bool button_left(sf::Event& event);
	bool button_space(sf::Event& event); // fall down figure
	bool button_enter(sf::Event& event);
	bool button_escape(sf::Event& event);
	bool button_Ctrl(sf::Event& event); // swap figure
};

