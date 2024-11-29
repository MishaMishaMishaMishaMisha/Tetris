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
    RatingMenu,
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

// инфа сервера
struct ServerInfo
{
    const char* ip = "34.16.110.198";
    const uint16_t port_tcp = 53000;
    const uint16_t port_udp = 53001;
    const uint16_t port_db = 54000; // порт для подключения к базе данных
};