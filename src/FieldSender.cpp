#include "FieldSender.h"


// передача текущего состояния поля другому игроку

// координаты текущей фигуры
std::string FieldSender::sendFigurePosition(Field& field)
{
    field.isFigurePosChanged = false;
    std::array<sf::Vector2f, 4> pos = {    field.figure[0].getPosition(),
                                            field.figure[1].getPosition(),
                                            field.figure[2].getPosition(),
                                            field.figure[3].getPosition() };
    return serializeFigurePosition(pos);
}
// текущая фигура
std::string FieldSender::sendCurFigure(Field& field)
{
    field.isFigureChanged = false;
    return serializeNumber(field.choice_cur);
}
// след. фигура
std::string FieldSender::sendNextFigure(Field& field)
{
    field.isNextFigureChanged = false;
    return serializeNumber(field.choice_next);
}
// фигура для смены
std::string FieldSender::sendSwapFigure(Field& field)
{
    field.isSwapFigureChanged = false;
    return serializeNumber(field.choice_swap);
}
// очки
std::string FieldSender::sendScore(Field& field)
{
    field.isScoresChanged = false;
    GameScore gs = field.scoreTetris.getScore();
    return serializeGameScore(gs);
}
// упавшие блоки
std::string FieldSender::sendNewBlocks(Field& field)
{
    field.isNewBlocks = false;
    std::array<sf::RectangleShape, 4> figure;
    for (size_t i = 0; i < 4; i++)
    {
        figure[i] = field.figure_last_fallen[i];

        auto temp = field.figure_last_fallen[i].getPosition().x;
        temp = field.figure_last_fallen[i].getPosition().y;
        temp = figure[i].getPosition().x;
        temp = figure[i].getPosition().y;
        temp = 0;
    }
    return serializeFigureBlocks(figure);
}
// поле после уничтожения рядов
std::string FieldSender::sendNewField(Field& field)
{
    field.isRowDestroyed = false;
    return serializeBlocks(field.blocks);
}

// получение состояния поля соперника

// координаты текущей фигуры
void FieldSender::receiveFigurePosition(Field& field, std::string& str)
{
    std::array<sf::Vector2f, 4> pos = deserializeFigurePosition(str);

    for (size_t i = 0; i < 4; ++i)
    {
        // сдвигаем блоки на правое поле:
        pos[i].x += 12 * field.grid.getS();
        field.figure[i].setPosition(pos[i]);
    }
    field.createShadow();
}
// текущая фигура
void FieldSender::receiveCurFigure(Field& field, std::string& str)
{
    size_t choice_cur = deserializeNumber(str);

    field.choice_cur = choice_cur;
    field.functions[choice_cur]();
    field.createShadow();
}
// след. фигура
void FieldSender::receiveNextFigure(Field& field, std::string& str)
{
    size_t choice_next = deserializeNumber(str);

    field.choice_next = choice_next;
    field.functions[choice_next]();
    field.copyFigure(field.figure, field.figure_next);
    field.placeNextFigure();
}
// фигура для смены
void FieldSender::receiveSwapFigure(Field& field, std::string& str)
{
    //size_t choice_swap = deserializeNumber(str);

    //field.choice_swap = choice_swap;
    //field.functions[choice_swap]();
    //field.copyFigure(field.figure, field.figure_swap);
    //field.placeSwapFigure();
    size_t choice_swap = deserializeNumber(str);
    field.swapFigure();
}
// очки
void FieldSender::receiveScore(Field& field, std::string& str)
{
    GameScore gameScore = deserializeGameScore(str);

    field.scoreTetris.isUpdate = true;
    field.scoreTetris.setScore(gameScore);
}
// упавшие блоки
void FieldSender::receiveNewBlocks(Field& field, std::string& str)
{
    auto figure = deserializeFigureBlocks(str);

    for (size_t i = 0; i < 4; i++)
    {
        auto temp = figure[i].getPosition().x;
        temp = figure[i].getPosition().y;
        
        uint16_t x = static_cast<uint16_t>((figure[i].getPosition().x - field.grid.getX0() + 12 * field.grid.getS()) / field.grid.getS());
        uint16_t y = static_cast<uint16_t>((figure[i].getPosition().y - field.grid.getY0()) / field.grid.getS());

        field.blocks[y][x] = new sf::RectangleShape(figure[i]);
        // сдвиг на правое поле
        field.blocks[y][x]->move(12 * field.grid.getS(), 0);
    }
}
// новое поле после уничтожения рядов
void FieldSender::receiveNewField(Field& field, std::string& str)
{
    deserializeBlocks(field, str);
    //field.blocks = deserializeBlocks(str);
    //for (size_t i = 0; i < field.blocks.size(); i++)
    //{
    //    for (size_t j = 0; j < field.blocks[0].size(); j++)
    //    {
    //        if (field.blocks[i][j])
    //        {
    //            // сдвиг на правое поле
    //            field.blocks[i][j]->move(12 * field.grid.getS(), 0);
    //        }
    //    }
    //}

    //for (size_t i = 0; i < blocks.size(); i++)
    //{
    //    for (size_t j = 0; j < blocks[0].size(); j++)
    //    {
    //        if (field.blocks[i][j])
    //        {
    //            delete field.blocks[i][j];
    //            field.blocks[i][j] = nullptr;
    //        }
    //        if (blocks[i][j])
    //        {
    //            field.blocks[i][j] = new sf::RectangleShape(*blocks[i][j]);
    //            // сдвиг на правое поле
    //            field.blocks[i][j]->move(12 * field.grid.getS(), 0);
    //        }
    //    }
    //}
}


// сериализация

std::string FieldSender::serializeNumber(size_t n)
{
    std::ostringstream oss;
    oss << n;
    return oss.str();
}

std::string FieldSender::serializeGameScore(GameScore& gameScore)
{
    std::ostringstream oss;
    oss << gameScore.level << " " << gameScore.lines << " " << gameScore.score;
    return oss.str();
}

std::string FieldSender::serializeFigurePosition(std::array<sf::Vector2f, 4>& pos)
{
    std::ostringstream oss;
    for (auto& el : pos)
    {
        oss << el.x << " " << el.y << '\n';
    }
    return oss.str();
}

std::string FieldSender::serializeFigureBlocks(std::array<sf::RectangleShape, 4>& figure)
{
    std::ostringstream oss;
    // передаем все характеристики объекта RectangleShape кроме позиции:
    // size
    oss << figure[0].getSize().x << " " << figure[0].getSize().y << " ";
    // outlinethickness
    oss << figure[0].getOutlineThickness() << " ";
    // color
    oss << figure[0].getFillColor().toInteger();
    oss << '\n';
    
    // positions:
    for (size_t i = 0; i < 4; ++i)
    {
        auto temp = figure[i].getPosition().x;
        temp = figure[i].getPosition().y;

        oss << figure[i].getPosition().x << " " << figure[i].getPosition().y;
        oss << '\n';
    }

    return oss.str();
}

std::string FieldSender::serializeBlocks(Blocks& blocks)
{
    std::ostringstream oss;
    oss << blocks.size() << " ";
    oss << blocks[0].size() << '\n';

    for (const auto& innerVec : blocks) 
    {
        for (const auto& block : innerVec) 
        {
            if (!block)
            {
                oss << "nullptr";
            }
            else
            {
                // передаем все характеристики объекта RectangleShape:
                // size
                oss << block->getSize().x << " " << block->getSize().y << " ";
                // outlinethickness
                oss << block->getOutlineThickness() << " ";
                // position
                oss << block->getPosition().x << " " << block->getPosition().y << " ";
                // color
                oss << block->getFillColor().toInteger();            }
            oss << '\n';
        }
    }
    return oss.str();
}


// десериализация

size_t FieldSender::deserializeNumber(const std::string& str)
{
    std::istringstream iss(str);
    size_t n;
    iss >> n;
    return n;
}

GameScore FieldSender::deserializeGameScore(const std::string& str)
{
    std::istringstream iss(str);
    GameScore gameScore;
    iss >> gameScore.level >> gameScore.lines >> gameScore.score;
    return gameScore;
}

std::array<sf::Vector2f, 4> FieldSender::deserializeFigurePosition(const std::string& str)
{
    std::istringstream iss(str);
    std::array<sf::Vector2f, 4> pos;
    for (size_t i = 0; i < 4; i++)
    {
        iss >> pos[i].x >> pos[i].y;
        iss.ignore();
    }
    return pos;
}

std::array<sf::RectangleShape, 4> FieldSender::deserializeFigureBlocks(const std::string& str)
{
    std::istringstream iss(str);
    float size_x, size_y, outlineThick;
    sf::Uint32 color;
    iss >> size_x >> size_y >> outlineThick >> color;
    iss.ignore();

    std::array<sf::RectangleShape, 4> figure;

    for (size_t i = 0; i < 4; ++i)
    {
        sf::RectangleShape block;
        block.setSize({ size_x, size_y });
        block.setOutlineThickness(outlineThick);
        block.setFillColor(sf::Color(color));
        float x, y;
        iss >> x >> y;
        block.setPosition({ x, y });
        iss.ignore();

        figure[i] = block;
    }
    return figure;
}

void FieldSender::deserializeBlocks(Field& field, const std::string& str)
{
    std::istringstream iss(str);
    size_t outer, inner;
    iss >> outer >> inner;
    iss.ignore();

    //Blocks blocks(outer, std::vector<sf::RectangleShape*>(inner, nullptr));

    for (size_t i = 0; i < outer; ++i) 
    {
        for (size_t j = 0; j < inner; ++j) 
        {

            std::string token;
            iss >> token;


            if (token == "nullptr")
            {
                if (field.blocks[i][j])
                {
                    delete field.blocks[i][j];
                    field.blocks[i][j] = nullptr;
                }
                iss.ignore();
                continue;
            }

            // Если не nullptr, читаем параметры объекта RectangleShape
            float sizeX, sizeY, outlineThickness, posX, posY;
            sf::Uint32 color;

            sizeX = std::stof(token);
            iss >> sizeY >> outlineThickness >> posX >> posY >> color;

            if (field.blocks[i][j])
            {
                if (field.blocks[i][j]->getFillColor().toInteger() != color)
                {
                    field.blocks[i][j]->setFillColor(sf::Color(color));
                }
                continue;
            }

            auto* block = new sf::RectangleShape();
            block->setSize({ sizeX, sizeY });
            block->setOutlineThickness(outlineThickness);
            block->setPosition({ posX, posY });
            block->setFillColor(sf::Color(color));

            //blocks[i][j] = block;
            field.blocks[i][j] = block;
            auto temp = field.blocks[i][j]->getPosition().x;
            // сдвиг на правое поле
            field.blocks[i][j]->move(12 * field.grid.getS(), 0);

            iss.ignore();
        }
    }

}