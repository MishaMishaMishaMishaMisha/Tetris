#include "OptionsMenu.h"

OptionsMenu::OptionsMenu(sf::RenderWindow& win, sf::Font& font, Audio& a, sf::Sprite& backgroundSprite, sf::Texture& texture_cont) :
    PauseMenu(win, font, a, backgroundSprite, 3, { "MUSIC VOLUME", "SOUNDS VOLUME", "SAVE AND EXIT" }),
    soundBar(win),
    musicBar(win)
{
    // картинка с управлением
    auto win_size = window.getSize();
    controlsImage.setSize(sf::Vector2f(win_size.x / 5.f, win_size.y / 1.5f));
    controlsImage.setTexture(&texture_cont);
    float image_height = controlsImage.getSize().y;
    controlsImage.setPosition(buttons[0].getPosition().x / 4, (win_size.y - image_height) / 2);

    // ползунки громкости (положение возле надписей)
    auto button_pos = buttons[0].getPosition();
    auto button_bounds = buttons[0].getGlobalBounds();
    float width = win_size.x/4.f;
    float height = button_bounds.height;
    musicBar.setValue(audio.getMusicVolume());
    musicBar.setSize(sf::Vector2f(width, height));
    float x = button_pos.x + button_bounds.width + 50;
    float y = button_pos.y + (button_bounds.height - height) / 2 + 20;
    musicBar.setPosition(x, y);
    
    button_pos = buttons[1].getPosition();
    button_bounds = buttons[1].getGlobalBounds();
    soundBar.setValue(audio.getSoundVolume());
    soundBar.setSize(sf::Vector2f(width, height));
    soundBar.setPosition(x, button_pos.y + (button_bounds.height - height) / 2 + 20);

}

void OptionsMenu::handleEvents(sf::Event& event)
{

    if (event.type == sf::Event::KeyPressed)
    {
        if (controls.button_enter(event) && selected_button == 2)
        {
            audio.saveSettings();
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
        else if (controls.button_left(event))
        {
            if (selected_button == 0)
            {
                musicBar.decrease();
                audio.setMusicVolume(musicBar.getValue());
            }
            else if (selected_button == 1)
            {
                soundBar.decrease();
                audio.setSoundVolume(soundBar.getValue());
                audio.playSelectEffect();
            }
        }
        else if (controls.button_right(event))
        {
            if (selected_button == 0)
            {
                musicBar.increase();
                audio.setMusicVolume(musicBar.getValue());
            }
            else if (selected_button == 1)
            {
                soundBar.increase();
                audio.setSoundVolume(soundBar.getValue());
                audio.playSelectEffect();
            }
        }
    }
}

GameState OptionsMenu::getNextState()
{
    return prev_state;
}

void OptionsMenu::draw()
{
    window.draw(backgroundSprite); // фон
    window.draw(controlsImage);
    musicBar.drawBar();
    soundBar.drawBar();
    for (size_t i = 0; i < max_size; i++)
    {
        window.draw(buttons[i]);
    }
}

