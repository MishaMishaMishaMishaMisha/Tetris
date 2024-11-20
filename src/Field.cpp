#include "Field.h"

Field::Field(uint16_t height, uint16_t width, sf::RenderWindow& win, sf::Font& font, FieldPosition pos) :
    grid(height, width, pos), 
    blocks(grid.getVerSize(), std::vector<sf::RectangleShape*>(grid.getHorSize(), nullptr)), 
    window(win), 
    font(font),
    isFigureChanged(false),
    isNextFigureChanged(false),
    isSwapFigureChanged(false),
    isFigurePosChanged(false),
    isNewBlocks(false),
    isRowDestroyed(false),
    isScoresChanged(false)
{
    setSeed(0);

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
    float x = areaPos.x + (6*grid.getS() - textRect.width) / 2 - textRect.left;
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
    for (size_t i = 0; i < 4; i++)
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
    for (size_t i = 0; i < 4; i++)
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
    for (size_t i = 0; i < 4; i++)
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
    for (size_t i = 0; i < 4; i++)
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
    for (size_t i = 0; i < 4; i++)
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
    for (size_t i = 0; i < 4; i++)
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
    for (size_t i = 0; i < 4; i++)
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
    for (size_t i = 0; i < 4; i++)
    {
        window.draw(figure[i]);
        window.draw(figure_next[i]);
        window.draw(figure_swap[i]);
        window.draw(figure_shadow[i]);
    }
}

void Field::drawBlocks() 
{
    for (size_t y = 0; y < grid.getVerSize(); y++)
    {
        for (size_t x = 0; x < grid.getHorSize(); x++)
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
        float x = areaPos.x + (6 * grid.getS() - textRect.width) / 2 - textRect.left;
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
    for (size_t i = 0; i < 4; i++)
    {
        figure[i] = sf::RectangleShape(sf::Vector2f(grid.getS() - 1, grid.getS() - 1));
        figure[i].setOutlineThickness(1);

        figure_next[i] = sf::RectangleShape(sf::Vector2f(grid.getS() - 1, grid.getS() - 1));
        figure_next[i].setOutlineThickness(1);

        figure_swap[i] = sf::RectangleShape(sf::Vector2f(grid.getS() - 1, grid.getS() - 1));
        figure_swap[i].setOutlineThickness(1);

        figure_shadow[i] = sf::RectangleShape(sf::Vector2f(grid.getS() - 1, grid.getS() - 1));

        figure_last_fallen[i] = sf::RectangleShape(sf::Vector2f(grid.getS() - 1, grid.getS() - 1));
        figure_last_fallen[i].setOutlineThickness(1);
    }
}

void Field::moveFigure(int8_t side, int8_t down)
{
    for (size_t i = 0; i < 4; i++)
    {
        figure[i].move(side * grid.getS(), down * grid.getS());
    }
    if (side)
    {
        createShadow();
    }
    isFigurePosChanged = true;
}

std::pair<uint16_t, uint16_t> Field::coordsTofield(const sf::Vector2f& coords)
{
    uint16_t x = static_cast<uint16_t>((coords.x - grid.getX0()) / grid.getS());
    uint16_t y = static_cast<uint16_t>((coords.y - grid.getY0()) / grid.getS());
    return std::make_pair(x, y);
}

bool Field::checkIntersect(const sf::Vector2f& coords)
{
    std::pair<uint16_t, uint16_t> x_y = coordsTofield(coords);
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

bool Field::checkSides(int8_t moveSide)
{
    for (size_t i = 0; i < 4; i++)
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
    for (size_t i = 0; i < 4; i++)
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
    for (size_t i = 1; i < 4; i++)
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
        for (size_t i = 0; i < 3; i++)
        {
            if (!checkBoards(newPos[i]) || !checkIntersect(newPos[i]))
            {
                return;
            }
        }
    }

    // Устанавливаем новые координаты для фигуры (три блока, центр остается на месте)
    for (size_t i = 1; i < 4; i++)
    {
        figure[i].setPosition(newPos[i - 1].x, newPos[i - 1].y);
    }
    createShadow();
    isFigurePosChanged = true;
}

void Field::generateFigure()
{
    if (!isInit)
    {
        // выбор след. фигуры
        //choice_next = rand() % functions.size();
        choice_next = static_cast<size_t>(distribution(generator));

        // создание фигуры для смены
        //int choice = rand() % functions.size();
        size_t choice = static_cast<size_t>(distribution(generator));
        functions[choice]();
        copyFigure(figure, figure_swap);
        placeSwapFigure();
        choice_swap = choice;

        isInit = true;

        isSwapFigureChanged = true;
    }

    //int choice = rand() % functions.size();
    size_t choice = distribution(generator);
    functions[choice]();
    copyFigure(figure, figure_next);
    placeNextFigure();
    functions[choice_next]();
    choice_cur = choice_next;
    choice_next = choice;

    createShadow();

    isFigureChanged = true;
    isNextFigureChanged = true;
}

int Field::checkRow()
{
    size_t height = blocks.size();       // Количество рядов (20 в данном примере)
    size_t width = blocks[0].size();     // Количество столбцов (10 в данном примере)

    uint16_t lines = 0;

    for (int row = static_cast<int>(height - 1); row >= 0; --row)
    {
        // Начинаем проверку с нижнего ряда
        bool isFull = true;

        // Проверяем, заполнен ли текущий ряд
        for (size_t col = 0; col < width; ++col)
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
            for (size_t col = 0; col < width; ++col)
            {
                delete blocks[row][col];
                blocks[row][col] = nullptr;
            }

            // Сдвигаем все блоки выше на одну строку вниз
            for (size_t r = row; r > 0; --r)
            {
                for (size_t col = 0; col < width; ++col)
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
            for (size_t col = 0; col < width; ++col)
            {
                blocks[0][col] = nullptr;
            }

            // Проверяем тот же ряд снова, так как теперь на его месте новый ряд
            ++row;
        }
    }

    scoreTetris.addScore(lines);
    calculateSpeed(scoreTetris.getScore().level);

    if (lines > 0)
    {
        isScoresChanged = true;
        isRowDestroyed = true;
    }

    return lines;
}

bool Field::checkGameOver()
{
    for (size_t i = 0; i < 4; i++)
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
    for (size_t i = 0; i < blocks.size(); i++)
    {
        for (size_t j = 0; j < blocks[0].size(); j++)
        {
            if (blocks[i][j])
            {
                delete blocks[i][j];
                blocks[i][j] = nullptr;
            }
        }
    }

    isInit = false;

    scoreTetris.reset();
    calculateSpeed(1);
}

void Field::addBlock()
{
    for (size_t i = 0; i < 4; ++i)
    {
        figure_last_fallen[i].setFillColor(figure[i].getFillColor());
        figure_last_fallen[i].setPosition(figure[i].getPosition());

        std::pair<uint16_t, uint16_t> x_y = coordsTofield(figure[i].getPosition());
        blocks[x_y.second][x_y.first] = new sf::RectangleShape(figure[i]);
    }
    isNewBlocks = true;
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
    for (size_t i = 0; i < 4; i++)
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
    // координаты area_next   
    sf::Vector2f nextAreaPos = grid.getAreaNextPosition();
    // начальные координаты фигуры
    sf::Vector2f blockPos = figure_next[0].getPosition();
    // координаты куда нужно переместить фигуру
    float offsetX = nextAreaPos.x + 2 * grid.getS();
    float offsetY = nextAreaPos.y + 2 * grid.getS();
    // сдвиг
    float moveX = offsetX - blockPos.x;
    float moveY = offsetY - blockPos.y;

    for (size_t i = 0; i < 4; i++)
    {
        figure_next[i].move(moveX, moveY);
    }
}

void Field::placeSwapFigure()
{
    sf::Vector2f nextAreaPos = grid.getAreaSwapPosition();
    sf::Vector2f blockPos = figure_swap[0].getPosition();

    float offsetX = nextAreaPos.x + 2 * grid.getS();
    float offsetY = nextAreaPos.y + 2 * grid.getS();

    float moveX = offsetX - blockPos.x;
    float moveY = offsetY - blockPos.y;

    for (size_t i = 0; i < 4; i++)
    {
        figure_swap[i].move(moveX, moveY);
    }
}

void Field::swapFigure()
{
    // запоминаем текущую позицию
    sf::Vector2f real_pos[4];
    for (size_t i = 0; i < 4; i++)
    {
        real_pos[i] = figure[i].getPosition();
    }

    // создаем ту же фигуру чтобы поместить ее в исходное положение
    functions[choice_cur]();

    // считаем на сколько она сместилась
    float x_dif = real_pos[0].x - figure[0].getPosition().x;
    float y_dif = real_pos[0].y - figure[0].getPosition().y;

    // заменяем figure_swap на figure в окошке слева
    copyFigure(figure, figure_swap);

    // создаем теперь swap фигуру
    functions[choice_swap]();

    // смещаем ее используя пред. величины
    for (size_t i = 0; i < 4; i++)
    {
        figure[i].move(x_dif, y_dif);
    }

    // проверяем не пересекается ли новая фигура с другими блоками и не выходит за поле
    // если пересекает - пробуем повернуть фигуру
    bool isIntersect;
    for (size_t rotate = 0; rotate < 4; rotate++)
    {
        isIntersect = false; // допускаем что пересечений нету
        for (size_t i = 0; i < 4; i++)
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
        for (size_t i = 0; i < 4; i++)
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

        isSwapFigureChanged = true;
    }
}

void Field::calculateSpeed(uint8_t level) {
    // Базовая скорость для 1 уровня: 0.5 секунд
    float baseSpeed = 0.5f;
    // Коэффициент уменьшения задержки на каждом уровне (например, 20%)
    float reductionFactor = 0.8f;

    // Задержка будет уменьшаться на 20% с каждым уровнем
    levelSpeed = baseSpeed * static_cast<float>(std::pow(reductionFactor, level - 1));

    // Минимальная скорость, чтобы блоки не падали слишком быстро
    if (levelSpeed < 0.1f) levelSpeed = 0.1f;

}

void Field::createShadow()
{
    // копируем фигуру
    copyFigure(figure, figure_shadow);

    // делаем фигуру полупрозрачной
    for (size_t i = 0; i < 4; i++)
    {
        figure_shadow[i].setFillColor(sf::Color(200, 200, 200, 50));
    }

    // опускаем в самый низ
    bool isMoveDown = true;
    uint16_t y_count = 0;
    while (isMoveDown && y_count < 20)
    {
        for (size_t i = 0; i < 4; i++)
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
    for (size_t i = 0; i < 4; i++)
    {
        figure_shadow[i].move(0, y_count * grid.getS());
    }

}

void Field::setSeed(uint32_t seed)
{
    if (seed == 0)
    {
        seed = static_cast<uint32_t>(time(0));
    }
    generator.seed(seed);
}








//// передача текущего состояния поля другому игроку
//
//// координаты текущей фигуры
//std::array<sf::Vector2f, 4> Field::sendFigurePosition()
//{
//    isFigurePosChanged = false;
//    return { figure[0].getPosition(),
//            figure[1].getPosition(),
//            figure[2].getPosition(),
//            figure[3].getPosition() };
//}
//// текущая фигура
//size_t Field::sendCurFigure()
//{
//    isFigureChanged = false;
//    return choice_cur;
//}
//// след. фигура
//size_t Field::sendNextFigure()
//{
//    isNextFigureChanged = false;
//    return choice_next;
//}
//// фигура для смены
//size_t Field::sendSwapFigure()
//{
//    isSwapFigureChanged = false;
//    return choice_swap;
//}
//// очки
//GameScore Field::sendScore()
//{
//    isScoresChanged = false;
//    return scoreTetris.getScore();
//}
//// упавшие блоки
//Blocks Field::sendNewBlocks()
//{
//    isNewBlocks = false;
//    return blocks;
//}
//// поле после уничтожения рядов
//Blocks Field::sendNewField()
//{
//    isRowDestroyed = false;
//    return blocks;
//}
//
//// получение состояния поля соперника
//
//// координаты текущей фигуры
//void Field::receiveFigurePosition(std::array<sf::Vector2f, 4> pos)
//{
//    for (size_t i = 0; i < 4; ++i)
//    {
//        // сдвигаем блоки на правое поле:
//        pos[i].x += 12 * grid.getS();
//        figure[i].setPosition(pos[i]);
//    }
//    createShadow();
//}
//// текущая фигура
//void Field::receiveCurFigure(size_t choice_cur)
//{
//    this->choice_cur = choice_cur;
//    functions[choice_cur]();
//    createShadow();
//}
//// след. фигура
//void Field::receiveNextFigure(size_t choice_next)
//{
//    this->choice_next = choice_next;
//    functions[choice_next]();
//    copyFigure(figure, figure_next);
//    placeNextFigure();
//}
//// фигура для смены
//void Field::receiveSwapFigure(size_t choice_swap)
//{
//    this->choice_swap = choice_swap;
//    functions[choice_swap]();
//    copyFigure(figure, figure_swap);
//    placeSwapFigure();
//}
//// очки
//void Field::receiveScore(GameScore gameScore)
//{
//    this->scoreTetris.isUpdate = true;
//    this->scoreTetris.setScore(gameScore);
//}
//// упавшие блоки
//void Field::receiveNewBlocks(Blocks blocks)
//{
//    for (size_t i = 0; i < blocks.size(); i++)
//    {
//        for (size_t j = 0; j < blocks[0].size(); j++)
//        {
//            if (blocks[i][j] && !this->blocks[i][j])
//            {
//                this->blocks[i][j] = new sf::RectangleShape(*blocks[i][j]);
//                // сдвиг на правое поле
//                this->blocks[i][j]->move(12 * grid.getS(), 0);
//            }
//        }
//    }
//}
//// нопое поле после уничтожения рядов
//void Field::receiveNewField(Blocks blocks)
//{
//    for (size_t i = 0; i < blocks.size(); i++)
//    {
//        for (size_t j = 0; j < blocks[0].size(); j++)
//        {
//            if (this->blocks[i][j])
//            {
//                delete this->blocks[i][j];
//                this->blocks[i][j] = nullptr;
//            }
//            if (blocks[i][j])
//            {
//                this->blocks[i][j] = new sf::RectangleShape(*blocks[i][j]);
//                // сдвиг на правое поле
//                this->blocks[i][j]->move(12 * grid.getS(), 0);
//            }
//        }
//    }
//}