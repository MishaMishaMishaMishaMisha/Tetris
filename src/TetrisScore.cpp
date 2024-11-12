#include "TetrisScore.h"

void TetrisScore::addScore(uint16_t clearedLines) 
{
    if (!clearedLines)
    {
        return;
    }
 
    isUpdate = true;
    uint32_t points = 0;
    switch (clearedLines) 
    {
    case 1: points = 40 * (game_score.level + 1); break;
    case 2: points = 100 * (game_score.level + 1); break;
    case 3: points = 300 * (game_score.level + 1); break;
    case 4: points = 1200 * (game_score.level + 1); break;
    }
    game_score.score += points;
    game_score.lines += clearedLines;

    // Увеличение уровня при достижении linesPerLevel строк
    if (game_score.lines >= game_score.level * linesPerLevel)
    {
        game_score.level++;
    }
}

void TetrisScore::reset()
{
    game_score.score = 0;
    game_score.lines = 0;
    game_score.level = 1;
    isUpdate = true;
}