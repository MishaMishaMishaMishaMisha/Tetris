#pragma once
#include "Game.h"

class GamePvPLocal : public BaseWindow
{
protected:
	Game game_left;
	Game game_right;

	sf::RectangleShape centerLine; // вертикальная линия по центру экрана

public:
	GamePvPLocal(uint16_t height, uint16_t width, sf::RenderWindow& win, Audio& a, sf::Sprite& backgroundSprite, sf::Font& font);

	void draw() override;
	void handleEvents(sf::Event& event) override;
	GameState getNextState() override;
	void set_Active() override;
	virtual void restart();

	GameScore getScore_left() { return game_left.getScore(); }
	// делаем виртуальным для переопределения в классе GamePvPOnline
	virtual GameScore getScore_right() { return game_right.getScore(); } 



};

