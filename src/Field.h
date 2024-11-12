#pragma once
#include "Grid.h"
#include "TetrisScore.h"
#include <functional>
#include <vector>
#include <random>

typedef std::vector<std::vector<sf::RectangleShape*>> Blocks;

class Field
{
private:
	Grid grid; // поле
	TetrisScore scoreTetris; // класс где высчитываются очки
	sf::RectangleShape figure[4]; // падающая фигура
	sf::RectangleShape figure_next[4]; // след. фигура
	sf::RectangleShape figure_swap[4]; // фигура для смены
	sf::RectangleShape figure_shadow[4]; // тень фигуры
	int choice_next = 0; // номер след. фигуры из вектора functions
	int choice_swap = 0; // номер фигуры для смены
	int choice_cur = 0; // номер текущей фигуры
	float levelSpeed = 0.5f; // скорость падения блоков в зависимости от уровня
	Blocks blocks; // матрица блоков которые остались на поле
	sf::RenderWindow& window;

	// текст для отображения счета и слов
	sf::Text text_swap;
	sf::Text text_next;
	sf::Text text_score;
	sf::Text text_lines;
	sf::Text text_level;
	sf::Text text_number_score;
	sf::Text text_number_lines;
	sf::Text text_number_level;
	sf::Font& font;

	std::vector<std::function<void()>> functions; // перечень функций для создания случайной фигуры

	// генераторы случайных чисел для выбора фигуры из вектора functions
	bool isInit = false;
	std::mt19937 generator;
	std::uniform_int_distribution<int> distribution{ 0, 6 }; // всего 7 фигур

	// функции для создания фигур
	void createI();
	void createO();
	void createT();
	void createJ();
	void createL();
	void createS();
	void createZ();

	// перевести реальные координаты в координаты, которые соответствуют полю
	std::pair<int, int> coordsTofield(const sf::Vector2f& coords);
	
	// есть ли блок на месте с координатами coords: false - есть, true - нету
	bool checkIntersect(const sf::Vector2f& coords);

	// где находится блок с координатами coords: false - за границей поля, true - внутри поля
	bool checkBoards(const sf::Vector2f& coords);

	// скопировать фигуру
	void copyFigure(sf::RectangleShape (&from)[4], sf::RectangleShape (&to)[4]);

	void placeNextFigure(); // разместить next фигурy в спец. местe за полем
	void placeSwapFigure(); // разместить swap фигурy в спец. местe за полем

public:
	Field(int height, int width, sf::RenderWindow& win, sf::Font& font, FieldPosition pos);

	// отображение поля, блоков, фигуры и счета в окне window 
	void drawFigure();
	void drawBlocks();
	void drawGrid();
	void drawScore();

	void initFigure(); // начальная инициализация фигуры

	// сдвиг фигуры: side=1 - вправо, side=-1 - влево, down=1 - вниз; 0 - сдвига нету
	void moveFigure(int side = 0, int down = 0); 

	bool checkSides(int moveSide); // можно ли сделать сдвиг в сторону
	bool checkDown(); // можно ли двигаться фигуре вниз

	void rotate(bool force = false); // поворот фигуры; force - поворот даже если фигура выйдет за границы

	void generateFigure(); // сгенерировать след. фигуру

	int checkRow(); // проверка на заполненный ряд. если такой есть, то он удаляется с поля; возвращает к-во заполненных рядов

	bool checkGameOver(); // провeрка на конец игры (если закончилось место на поле)

	void restart(); // очистка матрицы блоков и не только

	void addBlock(); // добавить блоки фигуры в матрицу blocks когда она опустилась вниз

	void fallFigure(); // опустить фигуру в самый низ

	void swapFigure(); // сменить фигуру

	void calculateSpeed(int level); // посчитать скорость падения в зависимости от уровня

	// тень нужно пересоздавать каждый раз после createNewFigure, rotate, swap, moveSide
	void createShadow();

	GameScore getScore() { return scoreTetris.getScore(); }

	float getSpeed() { return levelSpeed; }

	void setSeed(unsigned int  seed);
};

