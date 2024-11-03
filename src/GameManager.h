#pragma once
#include "Game.h";
#include "PauseMenu.h"
#include "MainMenu.h"
#include "GameOverMenu.h"
#include "HighscoreMenu.h"
#include "OptionsMenu.h"

// ����� ��� ������������ ����� ������ 
class GameManager
{

private:
	GameState current_state = GameState::MainMenu; // ������� ����
    int index = 0; // ����� ��������� (����)
    std::vector<BaseWindow*>& windows; // ������ ����


public:
    GameManager(std::vector<BaseWindow*>& wins) : windows(wins) {}

    // ������� ����� �������� ����.
    // ���� ������� ���� ����� �� ��������, ����������� �� ����. ����
    int get_state();

    // ������������ �� ����. ����
    void updateState();

    // ���������� ����� ����
    void setState(GameState& state);

    // ������� �� ��� ��� ������� ����
    bool isChanged();

};

