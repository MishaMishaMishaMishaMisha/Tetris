#pragma once

// перечесление всех возможных состояний программы
enum class GameState
{
    MainMenu,
    GamePlaying,
    GamePlayingPvPLocal,
    PauseMenu,
    HighscoreMenu,
    GameoverMenu,
    GameoverPvPMenu,
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

// положение игрового поля на экране
enum class FieldPosition
{
    Center,
    Left,
    Right
};
