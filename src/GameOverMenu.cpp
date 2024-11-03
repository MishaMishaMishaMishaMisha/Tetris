#include "GameOverMenu.h"


GameOverMenu::GameOverMenu(sf::RenderWindow& win, sf::Font& font, Audio& audio, sf::Sprite& backgroundSprite, int max_size, std::initializer_list<std::string> init_list, float y_pos) :
    PauseMenu(win, font, audio, backgroundSprite, max_size, init_list)
{
    // путь к файлу с рекордом
    file_manager.setPath("Files/");
    file_manager.setFileName("record.txt");


    // info window
    // Получаем размеры окна
    auto screen_size = window.getSize();

    // Заголовок "YOUR RESULT" по центру над кнопками
    text_result.setFont(font);
    text_result.setString("YOUR RESULT");
    text_result.setCharacterSize(30);
    text_result.setFillColor(sf::Color::White);
    sf::FloatRect result_bounds = text_result.getLocalBounds();
    text_result.setPosition(screen_size.x / 2 - result_bounds.width / 2, screen_size.y / (y_pos+0.5));

    // "SCORE - <value>" над кнопками, под заголовком
    text_score.setFont(font);
    text_score.setString("SCORE - " + std::to_string(game_score.score));
    text_score.setCharacterSize(24);
    text_score.setFillColor(sf::Color::White);
    sf::FloatRect score_bounds = text_score.getLocalBounds();
    text_score.setPosition(screen_size.x / 2 - score_bounds.width / 2, text_result.getPosition().y + 40);

    // "LINES - <value>" под SCORE
    text_lines.setFont(font);
    text_lines.setString("LINES - " + std::to_string(game_score.lines));
    text_lines.setCharacterSize(24);
    text_lines.setFillColor(sf::Color::White);
    sf::FloatRect lines_bounds = text_lines.getLocalBounds();
    text_lines.setPosition(screen_size.x / 2 - lines_bounds.width / 2, text_score.getPosition().y + 30);

    // "LEVEL - <value>" под LINES
    text_level.setFont(font);
    text_level.setString("LEVEL - " + std::to_string(game_score.level));
    text_level.setCharacterSize(24);
    text_level.setFillColor(sf::Color::White);
    sf::FloatRect level_bounds = text_level.getLocalBounds();
    text_level.setPosition(screen_size.x / 2 - level_bounds.width / 2, text_lines.getPosition().y + 30);
}

void GameOverMenu::handleEvents(sf::Event& event)
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

GameState GameOverMenu::getNextState()
{
    if (selected_button == 0)
    {
        return GameState::GamePlaying;
    }
    else if (selected_button == 1)
    {
        return GameState::MainMenu;
    }
}

void GameOverMenu::draw()
{
    window.draw(backgroundSprite); // фон
    window.draw(text_result);
    window.draw(text_score);
    window.draw(text_lines);
    window.draw(text_level);

    for (int i = 0; i < max_size; i++)
    {
        window.draw(buttons[i]);
    }
}

void GameOverMenu::setUPtext()
{
    if (is_newrecord)
    {
        text_result.setString("NEW RECORD!!!");
        text_result.setFillColor(sf::Color::Yellow);
        text_result.setOutlineThickness(3);
        text_result.setOutlineColor(sf::Color::Red);
    }
    else
    {
        text_result.setString("YOUR RESULT");
        text_result.setFillColor(sf::Color::White);
        text_result.setOutlineThickness(0);
    }

    // Текст для очков
    text_score.setString("SCORE - " + std::to_string(game_score.score));

    // Текст для линий
    text_lines.setString("LINES - " + std::to_string(game_score.lines));

    // Текст для уровня
    text_level.setString("LEVEL - " + std::to_string(game_score.level));
}

GameScore GameOverMenu::readRecord()
{
    std::string line = file_manager.readLine(); // читаем строку
    std::vector<int> numbers = file_manager.splitIntoNumbers(line); // переводим в числа

    GameScore temp_score = { 0, 0, 0 };
    if (numbers.size() >= 3)
    {
        temp_score.score = numbers[0];
        temp_score.lines = numbers[1];
        temp_score.level = numbers[2];
    }
    return temp_score;
}

void GameOverMenu::writeRecord()
{
    std::string line = std::to_string(game_score.score) + " " + std::to_string(game_score.lines) + " " + std::to_string(game_score.level);
    file_manager.writeLine(line);
}

void GameOverMenu::checkNewRecord()
{
    GameScore old_record = readRecord();
    if (old_record.score < game_score.score)
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
