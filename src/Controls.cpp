#include "Controls.h"

bool Controls::button_up(sf::Event& event)
{
    switch (mode)
    {
    case ControlsMode::WASD:
        return event.key.code == sf::Keyboard::W;
    case ControlsMode::ARROWS:
        return event.key.code == sf::Keyboard::Up;
    case ControlsMode::BOTH:
        return event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up;
    default:
        return false;
    }
}

bool Controls::button_down(sf::Event& event)
{
    switch (mode)
    {
    case ControlsMode::WASD:
        return event.key.code == sf::Keyboard::S;
    case ControlsMode::ARROWS:
        return event.key.code == sf::Keyboard::Down;
    case ControlsMode::BOTH:
        return event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down;
    default:
        return false;
    }
}

bool Controls::button_right(sf::Event& event)
{
    switch (mode)
    {
    case ControlsMode::WASD:
        return event.key.code == sf::Keyboard::D;
    case ControlsMode::ARROWS:
        return event.key.code == sf::Keyboard::Right;
    case ControlsMode::BOTH:
        return event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right;
    default:
        return false;
    }
}

bool Controls::button_left(sf::Event& event)
{
    switch (mode)
    {
    case ControlsMode::WASD:
        return event.key.code == sf::Keyboard::A;
    case ControlsMode::ARROWS:
        return event.key.code == sf::Keyboard::Left;
    case ControlsMode::BOTH:
        return event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left;
    default:
        return false;
    }
}

bool Controls::button_space(sf::Event& event)
{
    switch (mode)
    {
    case ControlsMode::WASD:
        return event.key.code == sf::Keyboard::Space;
    case ControlsMode::ARROWS:
        return event.key.code == sf::Keyboard::Numpad0;
    case ControlsMode::BOTH:
        return event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::Numpad0;
    default:
        return false;
    }
}

bool Controls::button_enter(sf::Event& event)
{
    switch (mode)
    {
    case ControlsMode::WASD:
        return event.key.code == sf::Keyboard::Return;
    case ControlsMode::ARROWS:
        return event.key.code == sf::Keyboard::Delete;
    case ControlsMode::BOTH:
        return event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Delete;
    default:
        return false;
    }
}

bool Controls::button_escape(sf::Event& event)
{
    switch (mode)
    {
    case ControlsMode::WASD:
        return event.key.code == sf::Keyboard::Escape;
    case ControlsMode::ARROWS:
        return event.key.code == sf::Keyboard::Backspace;
    case ControlsMode::BOTH:
        return event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::Backspace;
    default:
        return false;
    }
}

bool Controls::button_Ctrl(sf::Event& event)
{
    switch (mode)
    {
    case ControlsMode::WASD:
        return event.key.code == sf::Keyboard::LControl;
    case ControlsMode::ARROWS:
        return event.key.code == sf::Keyboard::RControl;
    case ControlsMode::BOTH:
        return event.key.code == sf::Keyboard::LControl || event.key.code == sf::Keyboard::RControl;
    default:
        return false;
    }
}