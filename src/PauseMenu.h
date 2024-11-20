#pragma once
#include "BaseWindow.h"
#include <initializer_list>

class PauseMenu : public BaseWindow
{
protected:
	sf::Font& font; // шрифт текста на кнопках
	uint8_t max_size; // количество кнопок на экране паузы
	std::vector<sf::Text> buttons;
	std::vector<std::string> names; // названия кнопок
	int8_t selected_button = 0;

	void highlightButton(); // выделить выбранную кнопку другим цветом
	void resetButtonsColor(); // вернуть исходные цвета
	void init(float y_pos); // инициализация кнопок;

	// пред. окно, чтобы знать откуда зашли в меню паузы - из одиночной игры или pvp игры
	GameState prev_state = GameState::MainMenu;

public:
	PauseMenu(sf::RenderWindow& win, sf::Font& font, Audio& a, sf::Sprite& backgroundSprite, uint8_t max_size = 3, std::initializer_list<std::string> initList = { "CONTINUE", "OPTIONS", "MAIN MENU" }, float y_pos = 2.0f);

	void draw() override;
	void handleEvents(sf::Event& event) override;
	GameState getNextState() override;
	void set_Active() override;

	void moveUp(); // переключить на кнопку ниже
	void moveDown(); // переключить на кнопку выше

	void setPrevState(GameState prev) { prev_state = prev; }
};

