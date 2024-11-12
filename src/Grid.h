#pragma once
#include <SFML/Graphics.hpp>
#include "Globals.h"

// класс для создания сетки
class Grid
{
private:
    int height, width; // размеры экрана
    int s; // размер квадрата
    int x0, y0; // координаты левого верхнего угла поля
    sf::VertexArray linesHor; // горизонтальные линии
    sf::VertexArray linesVer; // вертикальные линии
    sf::RectangleShape shadedArea; // прямоугольник для выделения 1 и 2 ряда

    sf::RectangleShape areaSwap; // прямоугольник для размещения figure_swap
    sf::RectangleShape areaNext; // прямоугольник для размещения figure_next
    sf::RectangleShape areaInfo; // прямоугольник для размещения очков, лвл, разрушенных рядов

    int nHor = 10, nVer = 20; // размер поля 10x20 квадратов
    int n = 42; // 21 горизонтальных линий
    int m = 22; // 11 вертикальных линий

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

