#include "GameOverPvPMenu.h"

GameOverPvPMenu::GameOverPvPMenu(sf::RenderWindow& win, sf::Font& font, Audio& audio, sf::Sprite& backgroundSprite, uint8_t max_size, std::initializer_list<std::string> init_list, float y_pos) :
    PauseMenu(win, font, audio, backgroundSprite, max_size, init_list)
{

    winner = { 0, 0, 0 };

    // путь к файлу с рекордом
    file_manager.setPath("Files/");
    //file_manager.setFileName("record.txt");
    file_manager.setFileName("record.bin");

    auto screen_size = window.getSize();

    // Заголовок "PLAYER1 RESULT" по центру над кнопками
    text_result_left.setFont(font);
    text_result_left.setString("PLAYER1 RESULT");
    text_result_left.setCharacterSize(30);
    text_result_left.setFillColor(sf::Color::White);
    sf::FloatRect result_bounds = text_result_left.getLocalBounds();
    text_result_left.setPosition(screen_size.x / 4 - result_bounds.width / 2, screen_size.y / (y_pos + 0.5f));

    // "SCORE - <value>" над кнопками, под заголовком
    text_score_left.setFont(font);
    text_score_left.setString("SCORE - " + std::to_string(game_score_left.score));
    text_score_left.setCharacterSize(24);
    text_score_left.setFillColor(sf::Color::White);
    sf::FloatRect score_bounds = text_score_left.getLocalBounds();
    text_score_left.setPosition(screen_size.x / 4 - score_bounds.width / 2, text_result_left.getPosition().y + 40);

    // "LINES - <value>" под SCORE
    text_lines_left.setFont(font);
    text_lines_left.setString("LINES - " + std::to_string(game_score_left.lines));
    text_lines_left.setCharacterSize(24);
    text_lines_left.setFillColor(sf::Color::White);
    sf::FloatRect lines_bounds = text_lines_left.getLocalBounds();
    text_lines_left.setPosition(screen_size.x / 4 - lines_bounds.width / 2, text_score_left.getPosition().y + 30);

    // "LEVEL - <value>" под LINES
    text_level_left.setFont(font);
    text_level_left.setString("LEVEL - " + std::to_string(game_score_left.level));
    text_level_left.setCharacterSize(24);
    text_level_left.setFillColor(sf::Color::White);
    sf::FloatRect level_bounds = text_level_left.getLocalBounds();
    text_level_left.setPosition(screen_size.x / 4 - level_bounds.width / 2, text_lines_left.getPosition().y + 30);


 
    // Заголовок "PLAYER2 RESULT" по центру над кнопками
    text_result_right.setFont(font);
    text_result_right.setString("PLAYER2 RESULT");
    text_result_right.setCharacterSize(30);
    text_result_right.setFillColor(sf::Color::White);
    result_bounds = text_result_right.getLocalBounds();
    text_result_right.setPosition(screen_size.x / 2 + screen_size.x / 4 - result_bounds.width / 2, screen_size.y / (y_pos + 0.5f));

    // "SCORE - <value>" над кнопками, под заголовком
    text_score_right.setFont(font);
    text_score_right.setString("SCORE - " + std::to_string(game_score_left.score));
    text_score_right.setCharacterSize(24);
    text_score_right.setFillColor(sf::Color::White);
    score_bounds = text_score_right.getLocalBounds();
    text_score_right.setPosition(screen_size.x / 2 + screen_size.x / 4 - score_bounds.width / 2, text_result_right.getPosition().y + 40);

    // "LINES - <value>" под SCORE
    text_lines_right.setFont(font);
    text_lines_right.setString("LINES - " + std::to_string(game_score_left.lines));
    text_lines_right.setCharacterSize(24);
    text_lines_right.setFillColor(sf::Color::White);
    lines_bounds = text_lines_right.getLocalBounds();
    text_lines_right.setPosition(screen_size.x / 2 + screen_size.x / 4 - lines_bounds.width / 2, text_score_right.getPosition().y + 30);

    // "LEVEL - <value>" под LINES
    text_level_right.setFont(font);
    text_level_right.setString("LEVEL - " + std::to_string(game_score_right.level));
    text_level_right.setCharacterSize(24);
    text_level_right.setFillColor(sf::Color::White);
    level_bounds = text_level_right.getLocalBounds();
    text_level_right.setPosition(screen_size.x / 2 + screen_size.x / 4 - level_bounds.width / 2, text_lines_right.getPosition().y + 30);

}

void GameOverPvPMenu::handleEvents(sf::Event& event)
{

    if (event.type == sf::Event::KeyPressed)
    {
        if (controls.button_enter(event))
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

GameState GameOverPvPMenu::getNextState()
{
    if (selected_button == 0)
    {
        //return GameState::GamePlayingPvPLocal;
        return prev_state; // online or local
    }
    //else if (selected_button == 1)
    else
    {
        return GameState::MainMenu;
    }
}

void GameOverPvPMenu::draw()
{
    window.draw(backgroundSprite); // фон
    window.draw(text_result_left);
    window.draw(text_score_left);
    window.draw(text_lines_left);
    window.draw(text_level_left);
    window.draw(text_result_right);
    window.draw(text_score_right);
    window.draw(text_lines_right);
    window.draw(text_level_right);

    for (size_t i = 0; i < max_size; i++)
    {
        window.draw(buttons[i]);
    }
}

void GameOverPvPMenu::setUPtext()
{
    if (is_newrecord)
    {
        if (winner.score == game_score_left.score || prev_state == GameState::GamePlayingPvPOnline)
        {
            text_result_left.setString("PLAYER1 NEW RECORD!!!");
            text_result_left.setFillColor(sf::Color::Yellow);
            text_result_left.setOutlineThickness(3);
            text_result_left.setOutlineColor(sf::Color::Red);
        }
        else
        {
            text_result_right.setString("PLAYER2 NEW RECORD!!!");
            text_result_right.setFillColor(sf::Color::Yellow);
            text_result_right.setOutlineThickness(3);
            text_result_right.setOutlineColor(sf::Color::Red);
        }
    }
    else
    {
        text_result_left.setString("PLAYER1 RESULT");
        text_result_left.setFillColor(sf::Color::White);
        text_result_left.setOutlineThickness(0);

        text_result_right.setString("PLAYER2 RESULT");
        text_result_right.setFillColor(sf::Color::White);
        text_result_right.setOutlineThickness(0);
    }

    text_score_left.setString("SCORE - " + std::to_string(game_score_left.score));
    text_lines_left.setString("LINES - " + std::to_string(game_score_left.lines));
    text_level_left.setString("LEVEL - " + std::to_string(game_score_left.level));

    text_score_right.setString("SCORE - " + std::to_string(game_score_right.score));
    text_lines_right.setString("LINES - " + std::to_string(game_score_right.lines));
    text_level_right.setString("LEVEL - " + std::to_string(game_score_right.level));
}


GameScore GameOverPvPMenu::readRecord()
{
    std::string line = file_manager.readLine(); // читаем строку
    std::vector<unsigned int> numbers = file_manager.splitIntoNumbers(line); // переводим в числа

    GameScore temp_score = { 0, 0, 0 };
    if (numbers.size() >= 3)
    {
        temp_score.score = numbers[0];
        temp_score.lines = numbers[1];
        temp_score.level = numbers[2];
    }
    return temp_score;
}

void GameOverPvPMenu::writeRecord()
{
    std::string line = std::to_string(winner.score) + " " + std::to_string(winner.lines) + " " + std::to_string(winner.level);
    file_manager.writeLine(line);
}

void GameOverPvPMenu::checkNewRecord()
{
    GameScore old_record = readRecord();
    if (game_score_left.score > game_score_right.score)
    {
        winner = game_score_left;
    }
    else
    {
        winner = game_score_right;
    }

    if (old_record.score < winner.score)
    {
        is_newrecord = true;
        writeRecord();
        audio.playNewRecordEffect();
    }
    else
    {
        is_newrecord = false;
        audio.playGameoverEffect();
    }
}

