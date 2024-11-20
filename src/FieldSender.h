#pragma once
#include "Field.h"
#include <sstream>

class FieldSender
{
public:

	// �������� �������� ��������� ���� ������� ������
	// �������� - ���� ������ �������� ���������
	// ��������� - ��������� ��������� ���� � �������������� ����
	std::string sendFigurePosition(Field& field); // ���������� ������� ������
	std::string sendCurFigure(Field& field); // ������� ������
	std::string sendNextFigure(Field& field); // ����. ������
	std::string sendSwapFigure(Field& field); // ������ ��� �����
	std::string sendScore(Field& field); // ����
	std::string sendNewBlocks(Field& field); // ����� ������ ��� ������� ������
	std::string sendNewField(Field& field); // �������� ��� ������� �����

	// ��������� ��������� ���� ���������
	// ��������� - ���� ���� ����� �������� ���������� ���������
	// � ���� ��������� � ������������� ����
	void receiveFigurePosition(Field& field, std::string& str);
	void receiveCurFigure(Field& field, std::string& str);
	void receiveNextFigure(Field& field, std::string& str);
	void receiveSwapFigure(Field& field, std::string& str);
	void receiveScore(Field& field, std::string& str);
	void receiveNewBlocks(Field& field, std::string& str);
	void receiveNewField(Field& field, std::string& str);

	// ������������
	std::string serializeNumber(size_t n);
	std::string serializeGameScore(GameScore& gameScore);
	std::string serializeFigurePosition(std::array<sf::Vector2f, 4>& pos);
	std::string serializeFigureBlocks(std::array<sf::RectangleShape, 4>& figure);
	std::string serializeBlocks(Blocks& blocks);
	//��������������
	size_t deserializeNumber(const std::string& str);
	GameScore deserializeGameScore(const std::string& str);
	std::array<sf::Vector2f, 4> deserializeFigurePosition(const std::string& str);
	std::array<sf::RectangleShape, 4> deserializeFigureBlocks(const std::string& str);
	void deserializeBlocks(Field& field, const std::string& str);
};

