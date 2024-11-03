#pragma once

// перечесление всех возможных состояний программы
enum class GameState
{
    MainMenu,
    GamePlaying,
    PauseMenu,
    HighscoreMenu,
    GameoverMenu,
    OptionsMenu,
    Exit
};

// струтура для удобного хранения счета
struct GameScore
{
    int score; // количеств набранных очков
    int lines; // количество разрушенных рядов
    int level; // уровень игры (скорость)
};
