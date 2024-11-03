#pragma once
#include "Globals.h"

class TetrisScore {
private:
    GameScore game_score;
    const int linesPerLevel = 10; // �-�� ����������� ����� ��� �������� �� ����. �������

public:
    TetrisScore()
    {
        game_score.level = 1;
        game_score.lines = 0;
        game_score.score = 0;
        isUpdate = true;
    }

    void addScore(int clearedLines);
    void reset();

    GameScore getScore() const { return game_score; }

    bool isUpdate; // ���������� �� �-�� �����. ����� ����� �� ������ �������� �� ����������� position � ������ drawScore ������ Field
};
