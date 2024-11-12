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
	Grid grid; // ����
	TetrisScore scoreTetris; // ����� ��� ������������� ����
	sf::RectangleShape figure[4]; // �������� ������
	sf::RectangleShape figure_next[4]; // ����. ������
	sf::RectangleShape figure_swap[4]; // ������ ��� �����
	sf::RectangleShape figure_shadow[4]; // ���� ������
	int choice_next = 0; // ����� ����. ������ �� ������� functions
	int choice_swap = 0; // ����� ������ ��� �����
	int choice_cur = 0; // ����� ������� ������
	float levelSpeed = 0.5f; // �������� ������� ������ � ����������� �� ������
	Blocks blocks; // ������� ������ ������� �������� �� ����
	sf::RenderWindow& window;

	// ����� ��� ����������� ����� � ����
	sf::Text text_swap;
	sf::Text text_next;
	sf::Text text_score;
	sf::Text text_lines;
	sf::Text text_level;
	sf::Text text_number_score;
	sf::Text text_number_lines;
	sf::Text text_number_level;
	sf::Font& font;

	std::vector<std::function<void()>> functions; // �������� ������� ��� �������� ��������� ������

	// ���������� ��������� ����� ��� ������ ������ �� ������� functions
	bool isInit = false;
	std::mt19937 generator;
	std::uniform_int_distribution<int> distribution{ 0, 6 }; // ����� 7 �����

	// ������� ��� �������� �����
	void createI();
	void createO();
	void createT();
	void createJ();
	void createL();
	void createS();
	void createZ();

	// ��������� �������� ���������� � ����������, ������� ������������� ����
	std::pair<int, int> coordsTofield(const sf::Vector2f& coords);
	
	// ���� �� ���� �� ����� � ������������ coords: false - ����, true - ����
	bool checkIntersect(const sf::Vector2f& coords);

	// ��� ��������� ���� � ������������ coords: false - �� �������� ����, true - ������ ����
	bool checkBoards(const sf::Vector2f& coords);

	// ����������� ������
	void copyFigure(sf::RectangleShape (&from)[4], sf::RectangleShape (&to)[4]);

	void placeNextFigure(); // ���������� next �����y � ����. ����e �� �����
	void placeSwapFigure(); // ���������� swap �����y � ����. ����e �� �����

public:
	Field(int height, int width, sf::RenderWindow& win, sf::Font& font, FieldPosition pos);

	// ����������� ����, ������, ������ � ����� � ���� window 
	void drawFigure();
	void drawBlocks();
	void drawGrid();
	void drawScore();

	void initFigure(); // ��������� ������������� ������

	// ����� ������: side=1 - ������, side=-1 - �����, down=1 - ����; 0 - ������ ����
	void moveFigure(int side = 0, int down = 0); 

	bool checkSides(int moveSide); // ����� �� ������� ����� � �������
	bool checkDown(); // ����� �� ��������� ������ ����

	void rotate(bool force = false); // ������� ������; force - ������� ���� ���� ������ ������ �� �������

	void generateFigure(); // ������������� ����. ������

	int checkRow(); // �������� �� ����������� ���. ���� ����� ����, �� �� ��������� � ����; ���������� �-�� ����������� �����

	bool checkGameOver(); // ����e��� �� ����� ���� (���� ����������� ����� �� ����)

	void restart(); // ������� ������� ������ � �� ������

	void addBlock(); // �������� ����� ������ � ������� blocks ����� ��� ���������� ����

	void fallFigure(); // �������� ������ � ����� ���

	void swapFigure(); // ������� ������

	void calculateSpeed(int level); // ��������� �������� ������� � ����������� �� ������

	// ���� ����� ������������� ������ ��� ����� createNewFigure, rotate, swap, moveSide
	void createShadow();

	GameScore getScore() { return scoreTetris.getScore(); }

	float getSpeed() { return levelSpeed; }

	void setSeed(unsigned int  seed);
};

