#include "Field.h"

Field::Field(int height, int width, sf::RenderWindow& win, sf::Font& font) : 
    grid(height, width), 
    blocks(grid.getVerSize(), std::vector<sf::RectangleShape*>(grid.getHorSize(), nullptr)), 
    window(win), 
    font(font)
{

    functions = {   std::bind(&Field::createI, this),
                    std::bind(&Field::createO, this),
                    std::bind(&Field::createL, this),
                    std::bind(&Field::createJ, this),
                    std::bind(&Field::createT, this),
                    std::bind(&Field::createS, this),
                    std::bind(&Field::createZ, this)
                };

    // создание текста
    //текст SWAP
    text_swap.setFont(font);
    text_swap.setFillColor(sf::Color::White);
    text_swap.setCharacterSize(50);
    text_swap.setString("SWAP");
    // размещение текста
    sf::FloatRect textRect = text_swap.getLocalBounds();
    auto areaPos = grid.getAreaSwapPosition();
    int x = areaPos.x + (6*grid.getS() - textRect.width) / 2 - textRect.left;
    text_swap.setPosition(x, areaPos.y);

    //текст NEXT
    text_next.setFont(font);
    text_next.setFillColor(sf::Color::White);
    text_next.setCharacterSize(50);
    text_next.setString("NEXT");
    // размещение текста
    textRect = text_next.getLocalBounds();
    areaPos = grid.getAreaNextPosition();
    x = areaPos.x + (6 * grid.getS() - textRect.width) / 2 - textRect.left;
    text_next.setPosition(x, areaPos.y);

    // текст INFO
    // SCORE
    text_score.setFont(font);
    text_score.setFillColor(sf::Color::White);
    text_score.setCharacterSize(50);
    text_score.setString("SCORE");
    text_number_score.setFont(font);
    text_number_score.setFillColor(sf::Color::White);
    text_number_score.setCharacterSize(50);
    // размещение текста
    textRect = text_score.getLocalBounds();
    areaPos = grid.getAreaInfoPosition();
    x = areaPos.x + (6 * grid.getS() - textRect.width) / 2 - textRect.left;
    text_score.setPosition(x, areaPos.y);
    // LINES
    text_lines.setFont(font);
    text_lines.setFillColor(sf::Color::White);
    text_lines.setCharacterSize(50);
    text_lines.setString("LINES");
    text_number_lines.setFont(font);
    text_number_lines.setFillColor(sf::Color::White);
    text_number_lines.setCharacterSize(50);
    // размещение текста
    textRect = text_lines.getLocalBounds();
    x = areaPos.x + (6 * grid.getS() - textRect.width) / 2 - textRect.left;
    text_lines.setPosition(x, areaPos.y + 2*grid.getS());
    // LEVEL
    text_level.setFont(font);
    text_level.setFillColor(sf::Color::White);
    text_level.setCharacterSize(50);
    text_level.setString("LEVEL");
    text_number_level.setFont(font);
    text_number_level.setFillColor(sf::Color::White);
    text_number_level.setCharacterSize(50);
    // размещение текста
    textRect = text_level.getLocalBounds();
    x = areaPos.x + (6 * grid.getS() - textRect.width) / 2 - textRect.left;
    text_level.setPosition(x, areaPos.y + 4*grid.getS());

}

void Field::createI()
{
    for (int i = 0; i < 4; i++)
    {
        figure[i].setFillColor(sf::Color::Blue);
        //figure[i].setPosition(grid.getX0() + (3 + i) * grid.getS(), grid.getY0());
    }
    figure[0].setPosition(grid.getX0() + 4 * grid.getS(), grid.getY0());
    figure[1].setPosition(grid.getX0() + 3 * grid.getS(), grid.getY0());
    figure[2].setPosition(grid.getX0() + 5 * grid.getS(), grid.getY0());
    figure[3].setPosition(grid.getX0() + 6 * grid.getS(), grid.getY0());
}
void Field::createO()
{
    for (int i = 0; i < 4; i++)
    {
        figure[i].setFillColor(sf::Color::Red);
    }
    figure[0].setPosition(grid.getX0() + 4 * grid.getS(), grid.getY0());
    figure[1].setPosition(grid.getX0() + 5 * grid.getS(), grid.getY0());
    figure[2].setPosition(grid.getX0() + 4 * grid.getS(), grid.getY0() + grid.getS());
    figure[3].setPosition(grid.getX0() + 5 * grid.getS(), grid.getY0() + grid.getS());
}
void Field::createT()
{
    //figure[0].setPosition(grid.getX0() + 5 * grid.getS(), grid.getY0());
    for (int i = 0; i < 4; i++)
    {
        figure[i].setFillColor(sf::Color::Green);
        //if (i > 0)
        //{
        //    figure[i].setPosition(grid.getX0() + (3 + i) * grid.getS(), grid.getY0() + grid.getS());
        //}
    }
    figure[0].setPosition(grid.getX0() + 5 * grid.getS(), grid.getY0() + grid.getS());
    figure[1].setPosition(grid.getX0() + 5 * grid.getS(), grid.getY0());
    figure[2].setPosition(grid.getX0() + 4 * grid.getS(), grid.getY0() + grid.getS());
    figure[3].setPosition(grid.getX0() + 6 * grid.getS(), grid.getY0() + grid.getS());
}
void Field::createL()
{
    //figure[0].setPosition(grid.getX0() + 4 * grid.getS(), grid.getY0());
    for (int i = 0; i < 4; i++)
    {
        figure[i].setFillColor(sf::Color::Yellow);
        //if (i > 0)
        //{
        //    figure[i].setPosition(grid.getX0() + (3 + i) * grid.getS(), grid.getY0() + grid.getS());
        //}
    }
    figure[0].setPosition(grid.getX0() + 5 * grid.getS(), grid.getY0() + grid.getS());
    figure[1].setPosition(grid.getX0() + 4 * grid.getS(), grid.getY0());
    figure[2].setPosition(grid.getX0() + 4 * grid.getS(), grid.getY0() + grid.getS());
    figure[3].setPosition(grid.getX0() + 6 * grid.getS(), grid.getY0() + grid.getS());
}
void Field::createJ()
{
    //figure[0].setPosition(grid.getX0() + 6 * grid.getS(), grid.getY0());
    for (int i = 0; i < 4; i++)
    {
        figure[i].setFillColor(sf::Color::Cyan);
        //if (i > 0)
        //{
        //    figure[i].setPosition(grid.getX0() + (3 + i) * grid.getS(), grid.getY0() + grid.getS());
        //}
    }
    figure[0].setPosition(grid.getX0() + 5 * grid.getS(), grid.getY0() + grid.getS());
    figure[1].setPosition(grid.getX0() + 6 * grid.getS(), grid.getY0());
    figure[2].setPosition(grid.getX0() + 4 * grid.getS(), grid.getY0() + grid.getS());
    figure[3].setPosition(grid.getX0() + 6 * grid.getS(), grid.getY0() + grid.getS());
}
void Field::createS()
{
    for (int i = 0; i < 4; i++)
    {
        figure[i].setFillColor(sf::Color::Magenta);
    }
    figure[3].setPosition(grid.getX0() + 5 * grid.getS(), grid.getY0());
    figure[1].setPosition(grid.getX0() + 6 * grid.getS(), grid.getY0());
    figure[2].setPosition(grid.getX0() + 4 * grid.getS(), grid.getY0() + grid.getS());
    figure[0].setPosition(grid.getX0() + 5 * grid.getS(), grid.getY0() + grid.getS());
}
void Field::createZ()
{
    for (int i = 0; i < 4; i++)
    {
        figure[i].setFillColor(sf::Color::Magenta);
    }
    figure[2].setPosition(grid.getX0() + 4 * grid.getS(), grid.getY0());
    figure[1].setPosition(grid.getX0() + 5 * grid.getS(), grid.getY0());
    figure[0].setPosition(grid.getX0() + 5 * grid.getS(), grid.getY0() + grid.getS());
    figure[3].setPosition(grid.getX0() + 6 * grid.getS(), grid.getY0() + grid.getS());
}

void Field::drawFigure()
{
    for (int i = 0; i < 4; i++)
    {
        window.draw(figure[i]);
        window.draw(figure_next[i]);
        window.draw(figure_swap[i]);
        window.draw(figure_shadow[i]);
    }
}

void Field::drawBlocks() 
{
    for (int y = 0; y < grid.getVerSize(); y++)
    {
        for (int x = 0; x < grid.getHorSize(); x++)
        {
            if (blocks[y][x])
            {
                window.draw(*blocks[y][x]);
            }
        }
    }
}

void Field::drawGrid()
{
    grid.draw(window);
    window.draw(text_swap);
    window.draw(text_next);
    window.draw(text_score);
    window.draw(text_lines);
    window.draw(text_level);
}

void Field::drawScore()
{
    if (scoreTetris.isUpdate)
    {
        text_number_score.setString(std::to_string(scoreTetris.getScore().score));
        text_number_lines.setString(std::to_string(scoreTetris.getScore().lines));
        text_number_level.setString(std::to_string(scoreTetris.getScore().level));

        auto textRect = text_number_score.getLocalBounds();
        auto areaPos = grid.getAreaInfoPosition();
        int x = areaPos.x + (6 * grid.getS() - textRect.width) / 2 - textRect.left;
        text_number_score.setPosition(x, areaPos.y + grid.getS());

        textRect = text_number_lines.getLocalBounds();
        x = areaPos.x + (6 * grid.getS() - textRect.width) / 2 - textRect.left;
        text_number_lines.setPosition(x, areaPos.y + 3 * grid.getS());

        textRect = text_number_level.getLocalBounds();
        x = areaPos.x + (6 * grid.getS() - textRect.width) / 2 - textRect.left;
        text_number_level.setPosition(x, areaPos.y + 5 * grid.getS());

        scoreTetris.isUpdate = false;
    }

    window.draw(text_number_score);
    window.draw(text_number_lines);
    window.draw(text_number_level);
}

void Field::initFigure()
{
    for (int i = 0; i < 4; i++)
    {
        figure[i] = sf::RectangleShape(sf::Vector2f(grid.getS() - 1, grid.getS() - 1));
        figure[i].setOutlineThickness(1);

        figure_next[i] = sf::RectangleShape(sf::Vector2f(grid.getS() - 1, grid.getS() - 1));
        figure_next[i].setOutlineThickness(1);

        figure_swap[i] = sf::RectangleShape(sf::Vector2f(grid.getS() - 1, grid.getS() - 1));
        figure_swap[i].setOutlineThickness(1);

        figure_shadow[i] = sf::RectangleShape(sf::Vector2f(grid.getS() - 1, grid.getS() - 1));
    }

    // выбор след. фигуры
    choice_next = rand() % functions.size();

    // создание фигуры для смены
    int choice = rand() % functions.size();
    functions[choice]();
    copyFigure(figure, figure_swap);
    placeSwapFigure();
    choice_swap = choice;
}

void Field::moveFigure(int side, int down)
{
    for (int i = 0; i < 4; i++)
    {
        figure[i].move(side * grid.getS(), down * grid.getS());
    }
    if (side)
    {
        createShadow();
    }
}

std::pair<int, int> Field::coordsTofield(const sf::Vector2f& coords)
{
    int x = (coords.x - grid.getX0()) / grid.getS();
    int y = (coords.y - grid.getY0()) / grid.getS();
    return std::make_pair(x, y);
}

bool Field::checkIntersect(const sf::Vector2f& coords)
{
    std::pair<int, int> x_y = coordsTofield(coords);
    if (blocks[x_y.second][x_y.first])
    {
        return false;
    }
    return true;
}

bool Field::checkBoards(const sf::Vector2f& coords)
{
    // стороны
    if (coords.x < grid.getX0() || coords.x > grid.getX0() + grid.getS() * (grid.getHorSize() - 1))
    {
        return false;
    }
    // верх и низ
    if (coords.y < grid.getY0() || coords.y > grid.getY0() + grid.getS() * (grid.getVerSize() - 1))
    {
        return false;
    }

    return true;
}

bool Field::checkSides(int moveSide)
{
    for (int i = 0; i < 4; i++)
    {
        auto next_pos = figure[i].getPosition();
        next_pos.x += moveSide * grid.getS();
        if (!checkBoards(next_pos) || !checkIntersect(next_pos))
        {
            return false;
        }
    }
    return true;
}

bool Field::checkDown()
{
    for (int i = 0; i < 4; i++)
    {
        auto next_pos = figure[i].getPosition();
        next_pos.y += grid.getS();
        if (!checkBoards(next_pos) || !checkIntersect(next_pos))
        {
            return false;
        }
    }
    return true;
}

void Field::rotate(bool force)
{
    // если фигура это квадрат то поворот не делаем
    sf::Vector2f pos = figure[0].getPosition();
    if (pos.x + grid.getS() == figure[1].getPosition().x && pos.y + grid.getS() == figure[2].getPosition().y)
    {
        return;
    }

    // Находим центр вращения (первая часть фигуры)
    sf::Vector2f center = figure[0].getPosition();

    // сначала сохраняем новые координаты квадратов после поворота
    sf::Vector2f newPos[3];
    for (int i = 1; i < 4; i++)
    {
        // Получаем координаты фигуры относительно центра
        sf::Vector2f relativePosition = figure[i].getPosition() - center;

        // Поворачиваем на 90 градусов по часовой стрелке: (x', y') = (-y, x)
        float newX = -relativePosition.y;
        float newY = relativePosition.x;

        newPos[i - 1].x = center.x + newX;
        newPos[i - 1].y = center.y + newY;
    }

    if (!force)
    {
        // если все квадраты на новых координатах не пересекают границы и другие квадраты то записываем их в figure
        for (int i = 0; i < 3; i++)
        {
            if (!checkBoards(newPos[i]) || !checkIntersect(newPos[i]))
            {
                return;
            }
        }
    }

    // Устанавливаем новые координаты для фигуры (три блока, центр остается на месте)
    for (int i = 1; i < 4; i++)
    {
        figure[i].setPosition(newPos[i - 1].x, newPos[i - 1].y);
    }
    createShadow();
}

void Field::generateFigure()
{
    int choice = rand() % functions.size();
    functions[choice]();
    copyFigure(figure, figure_next);
    placeNextFigure();
    functions[choice_next]();
    choice_cur = choice_next;
    choice_next = choice;

    createShadow();
}

int Field::checkRow()
{
    int height = blocks.size();       // Количество рядов (20 в данном примере)
    int width = blocks[0].size();     // Количество столбцов (10 в данном примере)

    int lines = 0;

    for (int row = height - 1; row >= 0; --row)
    {
        // Начинаем проверку с нижнего ряда
        bool isFull = true;

        // Проверяем, заполнен ли текущий ряд
        for (int col = 0; col < width; ++col)
        {
            if (blocks[row][col] == nullptr)
            {
                isFull = false;
                break;
            }
        }

        // Если ряд заполнен, удаляем его блоки и сдвигаем все выше
        if (isFull)
        {
            lines++;

            // Удаляем все блоки в текущем ряду
            for (int col = 0; col < width; ++col)
            {
                delete blocks[row][col];
                blocks[row][col] = nullptr;
            }

            // Сдвигаем все блоки выше на одну строку вниз
            for (int r = row; r > 0; --r)
            {
                for (int col = 0; col < width; ++col)
                {
                    blocks[r][col] = blocks[r - 1][col]; // Копируем указатель на блок вниз
                    if (blocks[r][col] != nullptr)
                    {
                        // Сдвигаем визуально каждый блок вниз на размер одного квадрата
                        blocks[r][col]->move(0, grid.getS());
                    }
                }
            }

            // ???
            // Очищаем самый верхний ряд, так как его блоки уже смещены вниз
            for (int col = 0; col < width; ++col)
            {
                blocks[0][col] = nullptr;
            }

            // Проверяем тот же ряд снова, так как теперь на его месте новый ряд
            ++row;
        }
    }

    scoreTetris.addScore(lines);
    calculateSpeed(scoreTetris.getScore().level);
    return lines;
}

bool Field::checkGameOver()
{
    for (int i = 0; i < 4; i++)
    {
        if (figure[i].getPosition().y == grid.getY0())
        {
            return true;
        }
    }
    return false;
}

void Field::restart()
{
    for (int i = 0; i < blocks.size(); i++)
    {
        for (int j = 0; j < blocks[0].size(); j++)
        {
            if (blocks[i][j])
            {
                delete blocks[i][j];
                blocks[i][j] = nullptr;
            }
        }
    }

    scoreTetris.reset();
    calculateSpeed(1);
}

void Field::addBlock()
{
    for (int i = 0; i < 4; ++i)
    {
        std::pair<int, int> x_y = coordsTofield(figure[i].getPosition());
        blocks[x_y.second][x_y.first] = new sf::RectangleShape(figure[i]);
    }

}

void Field::fallFigure()
{
    while (checkDown())
    {
        moveFigure(0, 1);
    }
}

void Field::copyFigure(sf::RectangleShape (&from)[4], sf::RectangleShape (&to)[4])
{
    for (int i = 0; i < 4; i++)
    {
        //figure_next[i].setPosition(figure[i].getPosition());
        //figure_next[i].move(grid.getS() * 10, grid.getS() * 6);
        //figure_next[i].setFillColor(figure[i].getFillColor());
        to[i].setPosition(from[i].getPosition());
        to[i].setFillColor(from[i].getFillColor());
    }
}

void Field::placeNextFigure()
{
    for (int i = 0; i < 4; i++)
    {
        figure_next[i].move(grid.getS() * 11, grid.getS() * 6);
    }
}

void Field::placeSwapFigure()
{
    for (int i = 0; i < 4; i++)
    {
        figure_swap[i].move(grid.getS() * (-12), grid.getS() * 10);
    }
}

void Field::swapFigure()
{
    // запоминаем текущую позицию
    sf::Vector2f real_pos[4];
    for (int i = 0; i < 4; i++)
    {
        real_pos[i] = figure[i].getPosition();
    }

    // создаем ту же фигуру чтобы поместить ее в исходное положение
    functions[choice_cur]();

    // считаем на сколько она сместилась
    int x_dif = real_pos[0].x - figure[0].getPosition().x;
    int y_dif = real_pos[0].y - figure[0].getPosition().y;

    // заменяем figure_swap на figure в окошке слева
    copyFigure(figure, figure_swap);

    // создаем теперь swap фигуру
    functions[choice_swap]();

    // смещаем ее используя пред. величины
    for (int i = 0; i < 4; i++)
    {
        figure[i].move(x_dif, y_dif);
    }

    // проверяем не пересекается ли новая фигура с другими блоками и не выходит за поле
    // если пересекает - пробуем повернуть фигуру
    bool isIntersect;
    for (int rotate = 0; rotate < 4; rotate++)
    {
        isIntersect = false; // допускаем что пересечений нету
        for (int i = 0; i < 4; i++)
        {
            if (!checkBoards(figure[i].getPosition()) || !checkIntersect(figure[i].getPosition()))
            {
                isIntersect = true;
                break;
            }
        }
        if (!isIntersect)
        {
            break;
        }
        this->rotate(true);
    }

    // если ни одно из положений не подходит - возвращаем старую фигуру и ничего не меняем
    if (isIntersect)
    {
        functions[choice_swap]();
        copyFigure(figure, figure_swap);
        placeSwapFigure();

        functions[choice_cur]();
        for (int i = 0; i < 4; i++)
        {
            figure[i].setPosition(real_pos[i]);
        }
    }
    else
    {
        // если нужное положение найдено - заменяем figure_swap на текущую фигуру
        placeSwapFigure();
        std::swap(choice_cur, choice_swap);
        createShadow();
    }
}

void Field::calculateSpeed(int level) {
    // Базовая скорость для 1 уровня: 0.5 секунд
    float baseSpeed = 0.5f;
    // Коэффициент уменьшения задержки на каждом уровне (например, 20%)
    float reductionFactor = 0.8f;

    // Задержка будет уменьшаться на 20% с каждым уровнем
    levelSpeed = baseSpeed * std::pow(reductionFactor, level - 1);

    // Минимальная скорость, чтобы блоки не падали слишком быстро
    if (levelSpeed < 0.1f) levelSpeed = 0.1f;

}

void Field::createShadow()
{
    // копируем фигуру
    copyFigure(figure, figure_shadow);

    // делаем фигуру полупрозрачной
    for (int i = 0; i < 4; i++)
    {
        figure_shadow[i].setFillColor(sf::Color(200, 200, 200, 50));
    }

    // опускаем в самый низ
    bool isMoveDown = true;
    int y_count = 0;
    while (isMoveDown && y_count < 20)
    {
        for (int i = 0; i < 4; i++)
        {
            auto next_pos = figure_shadow[i].getPosition();
            next_pos.y += (y_count + 1) * grid.getS();
            if (!checkBoards(next_pos) || !checkIntersect(next_pos))
            {
                isMoveDown = false;
                break;
            }
        }
        if (isMoveDown)
        {
            y_count++;
        }
    }
    for (int i = 0; i < 4; i++)
    {
        figure_shadow[i].move(0, y_count * grid.getS());
    }

}