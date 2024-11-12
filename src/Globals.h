#pragma once

// ������������ ���� ��������� ��������� ���������
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

// �������� ��� �������� �������� �����
struct GameScore
{
    int score; // ��������� ��������� �����
    int lines; // ���������� ����������� �����
    int level; // ������� ���� (��������)
};

// ��������� �������� ���� �� ������
enum class FieldPosition
{
    Center,
    Left,
    Right
};
