#pragma once
#include <cstdint>

// ������������ ���� ��������� ��������� ����
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

// �������� ��� �������� �������� �����
struct GameScore
{
    uint32_t score; // ��������� ��������� �����
    uint16_t lines; // ���������� ����������� �����
    uint8_t level; // ������� ���� (��������)

};

// ��������� �������� ���� �� ������
enum class FieldPosition
{
    Center,
    Left,
    Right
};

// ���� �������
struct ServerInfo
{
    const char* ip = "34.16.110.198";
    const uint16_t port_tcp = 53000;
    const uint16_t port_udp = 53001;
    const uint16_t port_db = 54000; // ���� ��� ����������� � ���� ������
};