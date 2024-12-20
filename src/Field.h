#pragma once
#include "Grid.h"
#include "TetrisScore.h"
#include <functional>
#include <vector>
#include <random>
#include <array>

typedef std::vector<std::vector<sf::RectangleShape*>> Blocks;

class FieldSender; // ������������� �����, ������� ������ �������� � ���������� ��������� ����

class Field
{
private:
	Grid grid; // ����
	TetrisScore scoreTetris; // ����� ��� ������������� ����
	sf::RectangleShape figure[4]; // �������� ������
	sf::RectangleShape figure_next[4]; // ����. ������
	sf::RectangleShape figure_swap[4]; // ������ ��� �����
	sf::RectangleShape figure_shadow[4]; // ���� ������
	sf::RectangleShape figure_last_fallen[4]; // ��������� ������� ������
	size_t choice_next = 0; // ����� ����. ������ �� ������� functions
	size_t choice_swap = 0; // ����� ������ ��� �����
	size_t choice_cur = 0; // ����� ������� ������
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
	std::uniform_int_distribution<unsigned int> distribution{ 0, 6 }; // ����� 7 �����

	// ������� ��� �������� �����
	void createI();
	void createO();
	void createT();
	void createJ();
	void createL();
	void createS();
	void createZ();

	// ��������� �������� ���������� � ����������, ������� ������������� ����
	std::pair<uint16_t, uint16_t> coordsTofield(const sf::Vector2f& coords);
	
	// ���� �� ���� �� ����� � ������������ coords: false - ����, true - ����
	bool checkIntersect(const sf::Vector2f& coords);

	// ��� ��������� ���� � ������������ coords: false - �� �������� ����, true - ������ ����
	bool checkBoards(const sf::Vector2f& coords);

	// ����������� ������
	void copyFigure(sf::RectangleShape (&from)[4], sf::RectangleShape (&to)[4]);

	void placeNextFigure(); // ���������� next �����y � ����. ����e �� �����
	void placeSwapFigure(); // ���������� swap �����y � ����. ����e �� �����

public:
	Field(uint16_t height, uint16_t width, sf::RenderWindow& win, sf::Font& font, FieldPosition pos);

	// ����������� ����, ������, ������ � ����� � ���� window 
	void drawFigure();
	void drawBlocks();
	void drawGrid();
	void drawScore();

	void initFigure(); // ��������� ������������� ������

	// ����� ������: side=1 - ������, side=-1 - �����, down=1 - ����; 0 - ������ ����
	void moveFigure(int8_t side = 0, int8_t down = 0);

	bool checkSides(int8_t moveSide); // ����� �� ������� ����� � �������
	bool checkDown(); // ����� �� ��������� ������ ����

	void rotate(bool force = false); // ������� ������; force - ������� ���� ���� ������ ������ �� �������

	void generateFigure(); // ������������� ����. ������

	int checkRow(); // �������� �� ����������� ���. ���� ����� ����, �� �� ��������� � ����; ���������� �-�� ����������� �����

	bool checkGameOver(); // ����e��� �� ����� ���� (���� ����������� ����� �� ����)

	void restart(); // ������� ������� ������ � �� ������

	void addBlock(); // �������� ����� ������ � ������� blocks ����� ��� ���������� ����

	void fallFigure(); // �������� ������ � ����� ���

	void swapFigure(); // ������� ������

	void calculateSpeed(uint8_t level); // ��������� �������� ������� � ����������� �� ������

	// ���� ����� ������������� ������ ��� ����� createNewFigure, rotate, swap, moveSide
	void createShadow();

	void setSeed(uint32_t seed);

	float getSpeed() { return levelSpeed; }

	GameScore getScore() { return scoreTetris.getScore(); }




////////////////////////////////////////////////////////////////////////////////////////////
										//ONLINE//
////////////////////////////////////////////////////////////////////////////////////////////

	friend FieldSender;

	// ����� ��������� ��������� � �����
	bool isFigureChanged;
	bool isNextFigureChanged;
	bool isSwapFigureChanged;
	bool isFigurePosChanged;
	bool isNewBlocks;
	bool isRowDestroyed;
	bool isScoresChanged;


	//// �������� �������� ��������� ���� ������� ������
	//std::array<sf::Vector2f, 4> sendFigurePosition(); // ���������� ������� ������
	//size_t sendCurFigure(); // ������� ������
	//size_t sendNextFigure(); // ����. ������
	//size_t sendSwapFigure(); // ������ ��� �����
	//GameScore sendScore(); // ����
	//Blocks sendNewBlocks(); // ������� �����
	//Blocks sendNewField(); // ����� �������� ���� ����� ����������� �����

	//// ��������� ��������� ���� ���������
	//void receiveFigurePosition(std::array<sf::Vector2f, 4> pos);
	//void receiveCurFigure(size_t choice_cur);
	//void receiveNextFigure(size_t choice_next);
	//void receiveSwapFigure(size_t choice_swap);
	//void receiveScore(GameScore gameScore);
	//void receiveNewBlocks(Blocks blocks);
	//void receiveNewField(Blocks blocks);

};

