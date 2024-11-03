#include "Game.h"

Game::Game(int height, int width, sf::RenderWindow& win, Audio& a, sf::Sprite& backgroundSprite, sf::Font& font) :
    BaseWindow(a, backgroundSprite),
    field(height, width, win, font), 
    window(win)
{
    // фигура
    field.initFigure();

}

void Game::restart()
{
    moveSide = 0;
    moveDown = 0;
    moveSideCount = 0;
    gameOver = false;

    field.restart();
    field.generateFigure();

    audio.stopMusic();
    clock.restart();

}

void Game::draw()
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
                //restart();
                gameOver = true;
                audio.stopMusic();
                isActive = false;
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

    //window.clear();
    window.draw(backgroundSprite); // фон
    field.drawGrid(); // отобразить поле
    field.drawBlocks(); // отобразить упавшие блоки
    field.drawFigure(); // отобразить падающую, следующую фигуру и фигуру для смены 
    field.drawScore(); // отобразить поле с очками
    //window.display();


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
        else if (controls.button_escape(event))
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
    audio.playMusic();
    isActive = true;
}
