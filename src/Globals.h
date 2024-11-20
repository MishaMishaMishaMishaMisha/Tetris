#pragma once
#include <cstdint>

// перечесление всех возможных состояний игры
enum class GameState
{
    MainMenu,
    GamePlaying,
    GamePlayingPvPLocal,
    GamePlayingPvPOnline,
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
    uint32_t score; // количеств набранных очков
    uint16_t lines; // количество разрушенных рядов
    uint8_t level; // уровень игры (скорость)

};

// положение игрового поля на экране
enum class FieldPosition
{
    Center,
    Left,
    Right
};
