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
