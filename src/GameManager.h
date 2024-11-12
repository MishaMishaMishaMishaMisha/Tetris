#pragma once
#include "Game.h"
#include "PauseMenu.h"
#include "MainMenu.h"
#include "GameOverMenu.h"
#include "HighscoreMenu.h"
#include "OptionsMenu.h"
#include "GamePvPLocal.h"
#include "GameOverPvPMenu.h"

// ����� ��� ������������ ����� ������ 
class GameManager
{

private:
	GameState current_state = GameState::MainMenu; // ������� ����
    size_t index = 0; // ����� ��������� (����)
    std::vector<BaseWindow*>& windows; // ������ ����


public:
    GameManager(std::vector<BaseWindow*>& wins) : windows(wins) {}

    // ������� ����� �������� ����.
    // ���� ������� ���� ����� �� ��������, ����������� �� ����. ����
    size_t get_state();

    // ������������ �� ����. ����
    void updateState();

    // ���������� ����� ����
    void setState(GameState& state);

    // ������� �� ��� ��� ������� ����
    bool isChanged();

};

