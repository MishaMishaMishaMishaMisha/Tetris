#include "Grid.h"

Grid::Grid(int height, int width, FieldPosition pos)
{
    this->height = height;
    this->width = width;

    s = std::min(width / nHor - 1, height / nVer - 1);

    if (pos == FieldPosition::Left)
    {
        x0 = (width - nHor * s) / 2 - s * 6;  // Сдвиг влево
    }
    else if (pos == FieldPosition::Right)
    {
        x0 = (width - nHor * s) / 2 + s * 6;  // Сдвиг вправо
    }
    else
    {
        x0 = (width - nHor * s) / 2;                 // По центру
    }
    y0 = 1;

    // Инициализация горизонтальных и вертикальных линий сетки
    linesHor.setPrimitiveType(sf::Lines);
    linesHor.resize(n);
    linesVer.setPrimitiveType(sf::Lines);
    linesVer.resize(m);
    for (int i = 0, y = 0; i < n; i += 2, y += s)
    {
        linesHor[i].position = sf::Vector2f(x0, y0 + y);
        linesHor[i + 1].position = sf::Vector2f(x0 + nHor * s, y0 + y);
    }
    for (int i = 0, x = 0; i < m; i += 2, x += s)
    {
        linesVer[i].position = sf::Vector2f(x0 + x, y0);
        linesVer[i + 1].position = sf::Vector2f(x0 + x, y0 + nVer * s);
    }

    shadedArea.setSize(sf::Vector2f(nHor * s, 2 * s));
    shadedArea.setPosition(x0, y0);
    shadedArea.setFillColor(sf::Color(200, 200, 200, 50));

    // зоны для next_figure, swap_figure, scores
    if (pos == FieldPosition::Center)
    {
        areaSwap.setSize(sf::Vector2f(s * 6, s * 4));
        int mid = (int)x0 / 2;
        int y = y0 + s * nVer / 2 - s * 2;
        areaSwap.setPosition(mid - 3 * s, y);
        areaSwap.setFillColor(sf::Color(200, 200, 200, 50));
        areaSwap.setOutlineThickness(5);
        areaSwap.setOutlineColor(sf::Color::White);

        areaNext.setSize(sf::Vector2f(s * 6, s * 4));
        areaNext.setPosition(x0 + nHor * s + mid - 3 * s, y - 4 * s);
        areaNext.setFillColor(sf::Color(200, 200, 200, 50));
        areaNext.setOutlineThickness(5);
        areaNext.setOutlineColor(sf::Color::White);

        areaInfo.setSize(sf::Vector2f(s * 6, s * 6));
        areaInfo.setPosition(x0 + nHor * s + mid - 3 * s, y + s);
        areaInfo.setFillColor(sf::Color(200, 200, 200, 50));
        areaInfo.setOutlineThickness(5);
        areaInfo.setOutlineColor(sf::Color::White);
    }
    else
    {
        // Координаты зон для отображения слева или справа от сетки
        float areaOffset = (pos == FieldPosition::Left) ? -7 * s : nHor * s + s;
        float yCenter = y0 + s * nVer / 2 - s * 2;

        areaSwap.setSize(sf::Vector2f(s * 6, s * 4));
        areaSwap.setPosition(x0 + areaOffset, yCenter - 5 * s);
        areaSwap.setFillColor(sf::Color(200, 200, 200, 50));
        areaSwap.setOutlineThickness(5);
        areaSwap.setOutlineColor(sf::Color::White);

        areaNext.setSize(sf::Vector2f(s * 6, s * 4));
        areaNext.setPosition(x0 + areaOffset, yCenter);
        areaNext.setFillColor(sf::Color(200, 200, 200, 50));
        areaNext.setOutlineThickness(5);
        areaNext.setOutlineColor(sf::Color::White);

        areaInfo.setSize(sf::Vector2f(s * 6, s * 6));
        areaInfo.setPosition(x0 + areaOffset, yCenter + 6 * s);
        areaInfo.setFillColor(sf::Color(200, 200, 200, 50));
        areaInfo.setOutlineThickness(5);
        areaInfo.setOutlineColor(sf::Color::White);
    }
}

void Grid::draw(sf::RenderWindow& window)
{
    window.draw(linesHor);
    window.draw(linesVer);
    window.draw(shadedArea);
    window.draw(areaSwap);
    window.draw(areaNext);
    window.draw(areaInfo);
}