#pragma once
#include "Field.h"
#include "Audio.h"
#include "BaseWindow.h"


// окно игры в тетрис
class Game : public BaseWindow
{
private:
	Field field;

	// переменная для сдвига блоков в стороны: 1 вправо, -1 влево, 0 на месте
	// moveDown - ускоренное падение блока
	int moveSide, moveDown;

	bool gameOver = false; // флаг окончания игры
	bool moveLast = false; // флаг задержки: когда фигура упала вниз, есть еще время чтобы ее сдвинуть в сторону
	int moveSideCount; // количество сдвигов в сторону за одну итерацию

	// привязка падения блоков ко времени
	sf::Clock clock;
	float time;

	bool isPVP = false; // одиночная или pvp игра

public:
	Game(int height, int width, sf::RenderWindow& win, Audio& a, sf::Sprite& backgroundSprite, sf::Font& font, FieldPosition f_pos = FieldPosition::Center);

	void draw() override;
	void handleEvents(sf::Event& event) override; // обработка нажатий во время игры
	void restart(); // начать все сначала

	GameState getNextState() override;

	void set_Active() override;

	GameScore getScore() { return field.getScore(); }

	void setControlsMode(ControlsMode mode); // изменить управление - стрелки/wasd/оба типа

	void setSeed(unsigned int seed);

	bool isGameOver() { return gameOver; }
};

