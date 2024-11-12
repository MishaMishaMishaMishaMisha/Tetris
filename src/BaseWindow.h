#pragma once
#include "Controls.h"
#include "Globals.h"
#include "Audio.h"

// базовый интерфейс всех окон
class BaseWindow
{
protected:
	bool isActive = false; // флаг - активное окно или нет
	Controls controls;
	Audio& audio;
	sf::Sprite& backgroundSprite; // фон
	sf::RenderWindow& window;

public:
	BaseWindow(Audio& a, sf::Sprite& bs, sf::RenderWindow& win) : audio(a), backgroundSprite(bs), window(win) {};

	virtual void draw() = 0; // вывод на экран
	virtual void handleEvents(sf::Event& event) = 0; // обработка нажатий
	virtual void set_Active() { isActive = true; }
	virtual GameState getNextState() = 0; // какое меню будет вызвано из текущего окна

	bool get_isActive() const { return isActive; }
};

