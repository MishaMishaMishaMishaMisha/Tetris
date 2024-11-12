#pragma once
#include <SFML/Graphics.hpp>
#include "Globals.h"

// ����� ��� �������� �����
class Grid
{
private:
    uint16_t height, width; // ������� ������
    float s; // ������ ��������
    float x0, y0; // ���������� ������ �������� ���� ����
    sf::VertexArray linesHor; // �������������� �����
    sf::VertexArray linesVer; // ������������ �����
    sf::RectangleShape shadedArea; // ������������� ��� ��������� 1 � 2 ����

    sf::RectangleShape areaSwap; // ������������� ��� ���������� figure_swap
    sf::RectangleShape areaNext; // ������������� ��� ���������� figure_next
    sf::RectangleShape areaInfo; // ������������� ��� ���������� �����, ���, ����������� �����

    const uint8_t nHor = 10, nVer = 20; // ������ ���� 10x20 ���������
    const uint8_t n = 42; // 21 �������������� �����
    const uint8_t m = 22; // 11 ������������ �����

public:
    Grid(uint16_t height, uint16_t width, FieldPosition pos);

    void draw(sf::RenderWindow& window);

    float getS() { return s; };
    float getX0() { return x0; }
    float getY0() { return y0; }
    uint8_t getHorSize() { return nHor; }
    uint8_t getVerSize() { return nVer; }
    sf::Vector2f getAreaSwapPosition() { return areaSwap.getPosition(); }
    sf::Vector2f getAreaNextPosition() { return areaNext.getPosition(); }
    sf::Vector2f getAreaInfoPosition() { return areaInfo.getPosition(); }
};

