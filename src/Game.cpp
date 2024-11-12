#include "Game.h"

Game::Game(int height, int width, sf::RenderWindow& win, Audio& a, sf::Sprite& backgroundSprite, sf::Font& font, FieldPosition f_pos) :
    BaseWindow(a, backgroundSprite, win),
    field(height, width, win, font, f_pos)
{
    // фигура
    field.initFigure();

    if (f_pos != FieldPosition::Center)
    {
        isPVP = true;
    }
}

void Game::restart()
{

    moveSide = 0;
    moveDown = 0;
    moveSideCount = 0;
    gameOver = false;

    field.restart();
    field.generateFigure();

    clock.restart();

    if (!isPVP)
    {
        audio.stopMusic();
    }
}

void Game::draw()
{
    if (!gameOver)
    {
        // движение фигуры вниз каждые 0.5сек (с каждым уровнем быстрее)
        // пока фигуры не опустился на самую последнюю клетку либо на другой блок
        if (field.checkDown())
        {
            time = clock.getElapsedTime().asSeconds();
            if (time > field.getSpeed())
            {
                field.moveFigure(0, 1);
                clock.restart();
            }

            // доп. движение если была нажата кнопка вниз 
            if (field.checkDown())
            {
                field.moveFigure(0, moveDown);
            }
        }
        else
        {
            if (!moveLast)
            {
                // Начало отсрочки закрепления фигуры
                moveLast = true;
                clock.restart();
            }

            // Позволяем боковое движение, если фигура еще "настраивается"
            if (moveLast && field.checkSides(moveSide) && moveSideCount < 1)
            {
                field.moveFigure(moveSide);
                moveSideCount++;

                // Если после движения в сторону фигура может падать, сбрасываем состояние "настройки"
                if (field.checkDown())
                {
                    moveLast = false;
                }
            }

            // Закрепляем фигуру, если отсрочка прошла
            if (moveLast && clock.getElapsedTime().asSeconds() > field.getSpeed())
            {
                moveLast = false;
                field.addBlock(); // сохранем позицию кубов фигуры
                if (field.checkRow()) // проверка на заполенные ряды
                {
                    audio.playDestroyRowEffect();
                }
                else
                {
                    audio.playFallFigureEffect();
                }

                // проверка на конец игры: если последняя опущенная фигура находится на y0 то game over
                if (field.checkGameOver())
                {
                    gameOver = true;
                    if (!isPVP)
                    {
                        audio.stopMusic();
                        isActive = false;
                    }
                    goto drawAll;
                }
                field.generateFigure(); // создаем новую фигуру
                clock.restart();
            }
        }

        // движение блока в стороны
        if (!moveLast && field.checkSides(moveSide) && moveSideCount < 1)
        {
            field.moveFigure(moveSide);
            moveSideCount++;
        }

        moveSide = 0;
        moveDown = 0;
        moveSideCount = 0;
    }

    // оператор goto
    drawAll:

    if (!isPVP)
    {
        window.draw(backgroundSprite); // фон
    }
    field.drawGrid(); // отобразить поле
    field.drawBlocks(); // отобразить упавшие блоки
    field.drawFigure(); // отобразить падающую, следующую фигуру и фигуру для смены 
    field.drawScore(); // отобразить поле с очками

}

void Game::handleEvents(sf::Event& event)
{

    if (event.type == sf::Event::KeyPressed)
    {
        if (controls.button_left(event))
        {
            moveSide = -1;
        }
        else if (controls.button_right(event))
        {
            moveSide = 1;
        }
        else if (controls.button_up(event))
        {
            field.rotate();
        }
        else if (controls.button_down(event))
        {
            moveDown = 1;
        }
        else if (controls.button_escape(event) && !isPVP)
        {
            audio.playPauseEffect();
            audio.pauseMusic(true);
            isActive = false;
        }
        else if (controls.button_space(event))
        {
            field.fallFigure();
        }
        else if (controls.button_Ctrl(event))
        {
            field.swapFigure();
        }
    }
}

GameState Game::getNextState()
{
    if (gameOver)
    {
        return GameState::GameoverMenu;
    }
    return GameState::PauseMenu;
}

void Game::set_Active()
{
    if (!isPVP)
    {
        audio.playMusic();
    }
    isActive = true;
}

void Game::setControlsMode(ControlsMode mode)
{
    controls.setMode(mode);
}

void Game::setSeed(unsigned int seed)
{
    field.setSeed(seed);
}
