#pragma once
#include "Game.h"
#include "PauseMenu.h"
#include "MainMenu.h"
#include "GameOverMenu.h"
#include "HighscoreMenu.h"
#include "RatingMenu.h"
#include "OptionsMenu.h"
#include "GamePvPLocal.h"
#include "GameOverPvPMenu.h"
#include "GamePvPOnline.h"

// ����� ��� ������������ ����� ������ 
class GameManager
{

private:
	GameState current_state = GameState::MainMenu; // ������� ����
    size_t index = 0; // ����� ��������� (����)
    std::vector<BaseWindow*>& windows; // ������ �� ������ � ������


    // ���� �� ������ ����� �� ����� pvp online �������� �����
    // �� ���� ������������
    bool pvp_online_pause_case;
    size_t index_pvpOnline; // ������ � ������� ���� PvPOnline

public:
    GameManager(std::vector<BaseWindow*>& wins);

    // ������� ����� �������� ����.
    // ���� ������� ���� ����� �� ��������, ����������� �� ����. ����
    size_t get_state();

    // ������������ �� ����. ����
    void updateState();

    // ���������� ����� ����
    void setState(GameState& state);

    // ������� �� ��� ��� ������� ����
    bool isChanged();



    // ���� ���� pvp_online_pause_case �������
    // �� �� ��������� ������ ����� ����
    void checkPvPOnlinePauseCase();
};

