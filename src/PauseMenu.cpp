#include "PauseMenu.h"

PauseMenu::PauseMenu(sf::RenderWindow& win, sf::Font& font, Audio& a, sf::Sprite& backgroundSprite, int max_size, std::initializer_list<std::string> initList, float y_pos) :
    BaseWindow(a, backgroundSprite, win),
    font(font),
    max_size(max_size),
    buttons(max_size, sf::Text()),
    names(initList)
{
    init(y_pos);
}

void PauseMenu::init(float y_pos)
{
    auto screen_size = window.getSize();

    for (int i = 0; i < max_size; i++)
    {
        buttons[i].setFont(font);
        buttons[i].setFillColor(sf::Color::White);
        buttons[i].setCharacterSize(50);
        buttons[i].setString(names[i]);
        // положение на экране
        sf::FloatRect text_bounds = buttons[i].getLocalBounds();
        buttons[i].setPosition(
            screen_size.x / 2 - text_bounds.width / 2,  // центр по горизонтали
            screen_size.y / y_pos - max_size * 50 + i * 100 // центр по вертикали с шагом
        );
    }
    highlightButton();
}

void PauseMenu::draw()
{
    window.draw(backgroundSprite); // фон
    for (int i = 0; i < max_size; i++)
    {
        window.draw(buttons[i]);
    }
}

void PauseMenu::handleEvents(sf::Event& event)
{

    if (event.type == sf::Event::KeyPressed)
    {
        if (controls.button_escape(event))
        {
            isActive = false;
            selected_button = 0;
        }
        else if (controls.button_enter(event))
        {
            isActive = false;
        }
        else if (controls.button_down(event))
        {
            moveDown();
        }
        else if (controls.button_up(event))
        {
            moveUp();
        }
    }
}

void PauseMenu::highlightButton()
{
    buttons[selected_button].setFillColor(sf::Color(170, 70, 70));
}

void PauseMenu::moveUp()
{
    audio.playSelectEffect();
    buttons[selected_button--].setFillColor(sf::Color::White);
    if (selected_button < 0)
    {
        selected_button = max_size - 1;
    }
    highlightButton();
}

void PauseMenu::moveDown()
{
    audio.playSelectEffect();
    buttons[selected_button++].setFillColor(sf::Color::White);
    if (selected_button >= max_size)
    {
        selected_button = 0;
    }
    highlightButton();
}

GameState PauseMenu::getNextState()
{
    if (selected_button == 0)
    {
        //return GameState::GamePlaying;
        return prev_state; // либо одиночная игра либо pvp
    }
    else if (selected_button == 1)
    {
        // options menu
        return GameState::OptionsMenu;
    }
    else if (selected_button == 2)
    {
        // main menu
        return GameState::MainMenu;
    }
}

void PauseMenu::resetButtonsColor()
{
    for (int i = 0; i < max_size; i++)
    {
        buttons[i].setFillColor(sf::Color::White);
    }
    selected_button = 0;
    highlightButton();
}

void PauseMenu::set_Active()
{
    resetButtonsColor();
    isActive = true;
}