#pragma once
#include <SFML/Graphics.hpp>
#include "Globals.h"

// ����� ��� �������� �����
class Grid
{
private:
    int height, width; // ������� ������
    int s; // ������ ��������
    int x0, y0; // ���������� ������ �������� ���� ����
    sf::VertexArray linesHor; // �������������� �����
    sf::VertexArray linesVer; // ������������ �����
    sf::RectangleShape shadedArea; // ������������� ��� ��������� 1 � 2 ����

    sf::RectangleShape areaSwap; // ������������� ��� ���������� figure_swap
    sf::RectangleShape areaNext; // ������������� ��� ���������� figure_next
    sf::RectangleShape areaInfo; // ������������� ��� ���������� �����, ���, ����������� �����

    int nHor = 10, nVer = 20; // ������ ���� 10x20 ���������
    int n = 42; // 21 �������������� �����
    int m = 22; // 11 ������������ �����

public:
    Grid(int height, int width, FieldPosition pos);

    void draw(sf::RenderWindow& window);

    int getS() { return s; };
    int getX0() { return x0; }
    int getY0() { return y0; }
    int getHorSize() { return nHor; }
    int getVerSize() { return nVer; }
    sf::Vector2f getAreaSwapPosition() { return areaSwap.getPosition(); }
    sf::Vector2f getAreaNextPosition() { return areaNext.getPosition(); }
    sf::Vector2f getAreaInfoPosition() { return areaInfo.getPosition(); }
};

