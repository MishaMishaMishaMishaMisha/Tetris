#pragma once
#include <SFML/Graphics.hpp>
#include "Globals.h"

// класс для создания сетки
class Grid
{
private:
    uint16_t height, width; // размеры экрана
    float s; // размер квадрата
    float x0, y0; // координаты левого верхнего угла поля
    sf::VertexArray linesHor; // горизонтальные линии
    sf::VertexArray linesVer; // вертикальные линии
    sf::RectangleShape shadedArea; // прямоугольник для выделения 1 и 2 ряда

    sf::RectangleShape areaSwap; // прямоугольник для размещения figure_swap
    sf::RectangleShape areaNext; // прямоугольник для размещения figure_next
    sf::RectangleShape areaInfo; // прямоугольник для размещения очков, лвл, разрушенных рядов

    const uint8_t nHor = 10, nVer = 20; // размер поля 10x20 квадратов
    const uint8_t n = 42; // 21 горизонтальных линий
    const uint8_t m = 22; // 11 вертикальных линий

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

