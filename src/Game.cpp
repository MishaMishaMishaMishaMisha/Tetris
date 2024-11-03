#include "Game.h"

Game::Game(int height, int width, sf::RenderWindow& win, Audio& a, sf::Sprite& backgroundSprite, sf::Font& font) :
    BaseWindow(a, backgroundSprite),
    field(height, width, win, font), 
    window(win)
{
    // ������
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
    // �������� ������ ���� ������ 0.5��� (� ������ ������� �������)
    // ���� ������ �� ��������� �� ����� ��������� ������ ���� �� ������ ����
    if (field.checkDown())
    {
        time = clock.getElapsedTime().asSeconds();
        if (time > field.getSpeed())
        {
            field.moveFigure(0, 1);
            clock.restart();
        }

        // ���. �������� ���� ���� ������ ������ ���� 
        if (field.checkDown())
        {
            field.moveFigure(0, moveDown);
        }
    }
    else
    {
        if (!moveLast)
        {
            // ������ �������� ����������� ������
            moveLast = true;
            clock.restart();
        }

        // ��������� ������� ��������, ���� ������ ��� "�������������"
        if (moveLast && field.checkSides(moveSide) && moveSideCount < 1)
        {
            field.moveFigure(moveSide);
            moveSideCount++;

            // ���� ����� �������� � ������� ������ ����� ������, ���������� ��������� "���������"
            if (field.checkDown())
            {
                moveLast = false;
            }
        }

        // ���������� ������, ���� �������� ������
        if (moveLast && clock.getElapsedTime().asSeconds() > field.getSpeed())
        {
            moveLast = false;
            field.addBlock(); // �������� ������� ����� ������
            if (field.checkRow()) // �������� �� ���������� ����
            {
                audio.playDestroyRowEffect();
            }
            else
            {
                audio.playFallFigureEffect();
            }

            // �������� �� ����� ����: ���� ��������� ��������� ������ ��������� �� y0 �� game over
            if (field.checkGameOver())
            {
                //restart();
                gameOver = true;
                audio.stopMusic();
                isActive = false;
            }
            field.generateFigure(); // ������� ����� ������
            clock.restart();
        }
    }

    // �������� ����� � �������
    if (!moveLast && field.checkSides(moveSide) && moveSideCount < 1)
    {
        field.moveFigure(moveSide);
        moveSideCount++;
    }

    moveSide = 0;
    moveDown = 0;
    moveSideCount = 0;

    //window.clear();
    window.draw(backgroundSprite); // ���
    field.drawGrid(); // ���������� ����
    field.drawBlocks(); // ���������� ������� �����
    field.drawFigure(); // ���������� ��������, ��������� ������ � ������ ��� ����� 
    field.drawScore(); // ���������� ���� � ������
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
