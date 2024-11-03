#include "Controls.h"

bool Controls::button_up(sf::Event& event)
{
    if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
    {
        return true;
    }
    return false;
}

bool Controls::button_down(sf::Event& event)
{
    if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
    {
        return true;
    }
    return false;
}

bool Controls::button_right(sf::Event& event)
{
    if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right)
    {
        return true;
    }
    return false;
}

bool Controls::button_left(sf::Event& event)
{
    if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left)
    {
        return true;
    }
    return false;
}

bool Controls::button_space(sf::Event& event)
{
    if (event.key.code == sf::Keyboard::Space)
    {
        return true;
    }
    return false;
}

bool Controls::button_enter(sf::Event& event)
{
    if (event.key.code == sf::Keyboard::Return)
    {
        return true;
    }
    return false;
}

bool Controls::button_escape(sf::Event& event)
{
    if (event.key.code == sf::Keyboard::Escape)
    {
        return true;
    }
    return false;
}

bool Controls::button_Ctrl(sf::Event& event)
{
    if (event.key.code == sf::Keyboard::LControl || event.key.code == sf::Keyboard::RControl)
    {
        return true;
    }
    return false;
}