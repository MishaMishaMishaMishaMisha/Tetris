#pragma once
#include "Field.h"
#include <sstream>

class FieldSender
{
public:

	// передача текущего состояния поля другому игроку
	// параметр - поле откуда забирать изменения
	// результат - различные изменения поля в сериализованом виде
	std::string sendFigurePosition(Field& field); // координаты текущей фигуры
	std::string sendCurFigure(Field& field); // текущая фигура
	std::string sendNextFigure(Field& field); // след. фигура
	std::string sendSwapFigure(Field& field); // фигура для смены
	std::string sendScore(Field& field); // очки
	std::string sendNewBlocks(Field& field); // блоки только что упавшей фигуры
	std::string sendNewField(Field& field); // передать все упавшие блоки

	// получение состояния поля соперника
	// параметры - поле куда нужно записать полученные изменения
	// и само изменение в сериалиованом виде
	void receiveFigurePosition(Field& field, std::string& str);
	void receiveCurFigure(Field& field, std::string& str);
	void receiveNextFigure(Field& field, std::string& str);
	void receiveSwapFigure(Field& field, std::string& str);
	void receiveScore(Field& field, std::string& str);
	void receiveNewBlocks(Field& field, std::string& str);
	void receiveNewField(Field& field, std::string& str);

	// сериализация
	std::string serializeNumber(size_t n);
	std::string serializeGameScore(GameScore& gameScore);
	std::string serializeFigurePosition(std::array<sf::Vector2f, 4>& pos);
	std::string serializeFigureBlocks(std::array<sf::RectangleShape, 4>& figure);
	std::string serializeBlocks(Blocks& blocks);
	//десериализация
	size_t deserializeNumber(const std::string& str);
	GameScore deserializeGameScore(const std::string& str);
	std::array<sf::Vector2f, 4> deserializeFigurePosition(const std::string& str);
	std::array<sf::RectangleShape, 4> deserializeFigureBlocks(const std::string& str);
	void deserializeBlocks(Field& field, const std::string& str);
};

