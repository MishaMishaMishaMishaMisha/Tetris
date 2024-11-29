#include "HighscoreMenu.h"

HighscoreMenu::HighscoreMenu(sf::RenderWindow& win, sf::Font& font, Audio& a, sf::Sprite& backgroundSprite) :
    GameOverMenu(win, font, a, backgroundSprite, 2, { "RATING LIST", "BACK" }, 6) // 6 - это y_pos - откуда начинать рисовать текст (window.size.y / y_pos)
{

    // изменяем надпись
    text_result.setString("YOUR RECORD");

    // Добавляем инфу об pvp победах
    auto screen_size = window.getSize();
    // text_count_games
    text_count_games.setFont(font);
    text_count_games.setString("PvP ONLINE GAMES - 0");
    text_count_games.setCharacterSize(24);
    text_count_games.setFillColor(sf::Color::White);
    sf::FloatRect level_bounds = text_count_games.getLocalBounds();
    text_count_games.setPosition(screen_size.x / 2 - level_bounds.width / 2, text_level.getPosition().y + 30);
    // text_count_wins
    text_count_wins.setFont(font);
    text_count_wins.setString("PvP ONLINE WINS - 0");
    text_count_wins.setCharacterSize(24);
    text_count_wins.setFillColor(sf::Color::White);
    level_bounds = text_count_wins.getLocalBounds();
    text_count_wins.setPosition(screen_size.x / 2 - level_bounds.width / 2, text_count_games.getPosition().y + 30);
    // text_winrate
    text_winrate.setFont(font);
    text_winrate.setString("PvP ONLINE WINRATE - 0%");
    text_winrate.setCharacterSize(24);
    text_winrate.setFillColor(sf::Color::White);
    level_bounds = text_winrate.getLocalBounds();
    text_winrate.setPosition(screen_size.x / 2 - level_bounds.width / 2, text_count_wins.getPosition().y + 30);
}

void HighscoreMenu::draw()
{
    window.draw(backgroundSprite); // фон
    window.draw(text_result);
    window.draw(text_score);
    window.draw(text_lines);
    window.draw(text_level);
    window.draw(text_count_games);
    window.draw(text_count_wins);
    window.draw(text_winrate);

    for (size_t i = 0; i < max_size; i++)
    {
        window.draw(buttons[i]);
    }
}

void HighscoreMenu::handleEvents(sf::Event& event)
{

    if (event.type == sf::Event::KeyPressed)
    {
        if (controls.button_escape(event))
        {
            isActive = false;
            selected_button = 1;
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

GameState HighscoreMenu::getNextState()
{
    if (selected_button == 0)
    {
        return GameState::RatingMenu;
    }
    else
    {
        return GameState::MainMenu;
    }
}

void HighscoreMenu::setUPtext()
{
    text_result.setString("YOUR RECORD");
    text_score.setString("SCORE - " + std::to_string(game_score.score));
    text_lines.setString("LINES - " + std::to_string(game_score.lines));
    text_level.setString("LEVEL - " + std::to_string(game_score.level));

    // pvp wins
    std::string line = file_manager.readLine();
    std::vector<unsigned int> numbers = file_manager.splitIntoNumbers(line);

    if (numbers.size() >= 5)
    {
        text_count_games.setString("PvP ONLINE GAMES - " + std::to_string(numbers[3]));
        text_count_wins.setString("PvP ONLINE WINS - " + std::to_string(numbers[4]));
        if (numbers[3])
        {
            text_winrate.setString("PvP ONLINE WINRATE - " + std::to_string(numbers[4] * 100 / numbers[3]) + "%");
        }
        else
        {
            text_winrate.setString("PvP ONLINE WINRATE - 0%");
        }
    }
    else
    {
        text_count_games.setString("PvP ONLINE GAMES - 0");
        text_count_wins.setString("PvP ONLINE WINS - 0");
        text_winrate.setString("PvP ONLINE WINRATE - 0%");
    }
}