#pragma once
#include "PauseMenu.h"
#include "FileManager.h"
#include "Audio.h"

// по аналогии с MainMenu делаем класс наследником от PauseMenu с некоторыми изменениями
class GameOverMenu : public PauseMenu
{
protected:
    // результат игры который будет отображен в этом окне
    GameScore game_score = { 0, 0, 1 };
    // поля текста для вывода на экран
    sf::Text text_result;
    sf::Text text_score;
    sf::Text text_lines;
    sf::Text text_level;
    bool is_newrecord = false;

    FileManager file_manager;

public:
    // в констуркторе переопределяем кнопки и инициализируем поля текста
    GameOverMenu(sf::RenderWindow& win, sf::Font& font, Audio& audio, sf::Sprite& backgroundSprite, int max_size = 2, std::initializer_list<std::string> init_list = { "PLAY AGAIN", "BACK TO MENU" }, float y_pos = 4.0f);

    void draw() override; // переопределяем метод для отображения результата игры
    GameState getNextState() override;
    void handleEvents(sf::Event& event) override; // обработка нажатий во время меню геймовера

    void setScore(GameScore score) { this->game_score = score; }

    // установка счета в конце игры в поля текста
    virtual void setUPtext();

    GameScore readRecord(); // прочитать рекорд из файла и вернуть его

    void writeRecord(); // записать новый рекорд

    void checkNewRecord(); // проверить был ли побит рекорд
};

