#pragma once
#include <SFML/Graphics.hpp>

// тип управление: wasd - управление через wasd,
// arrows - управление через стрелки, both - управление через wasd либо стрелки
enum ControlsMode { WASD, ARROWS, BOTH};

// класс для управления игрой
class Controls
{
private:
	ControlsMode mode = ControlsMode::BOTH; // режим по-умолч.

public:
	bool button_up(sf::Event& event); // rotate figure - W or arrow_up
	bool button_down(sf::Event& event); // move figure down faster - S or arrow_down
	bool button_right(sf::Event& event); // move figure right - D or arrow_right
	bool button_left(sf::Event& event);  // move figure left - A or arrow_left
	bool button_space(sf::Event& event); // fall down figure - space or Numpad0
	bool button_enter(sf::Event& event); // enter or delete
	bool button_escape(sf::Event& event); // escape or backspace
	bool button_Ctrl(sf::Event& event); // swap figure - Left_control or Right_control

	void setMode(ControlsMode mode) { this->mode = mode; }
};

