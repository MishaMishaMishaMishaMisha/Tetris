#pragma once

// ������������ ���� ��������� ��������� ���������
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

// �������� ��� �������� �������� �����
struct GameScore
{
    int score; // ��������� ��������� �����
    int lines; // ���������� ����������� �����
    int level; // ������� ���� (��������)
};
