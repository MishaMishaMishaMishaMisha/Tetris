#include "GameManager.h"


GameManager::GameManager(std::vector<BaseWindow*>& wins) : 
    windows(wins),
    pvp_online_pause_case(false)
{

    // ������� ������ ���� PvPOnline
    index_pvpOnline = 0;
    for (auto& win : windows)
    {
        if (dynamic_cast<GamePvPOnline*>(win))
        {
            break;
        }
        index_pvpOnline++;
    }
}

size_t GameManager::get_state()
{
    if (isChanged())
    {
        updateState();
    }
    return index;
}

void GameManager::setState(GameState& state)
{
    current_state = state;
    index = static_cast<size_t>(current_state);
    windows[index]->set_Active();
}

bool GameManager::isChanged()
{
    if (!windows[index]->get_isActive())
    {
        return true;
    }
    return false;
}

void GameManager::updateState()
{
    auto prev_state = current_state;
    current_state = windows[index]->getNextState();

    // ��������� ��������� ��� ������ �� ����
    if (current_state == GameState::Exit)
    {
        index = 999;
        return;
    }

    index = static_cast<size_t>(current_state);

    // �������� � ���� ����� ������������ �� �������
    if (current_state == GameState::MainMenu)
    {
        GamePvPOnline* temp = dynamic_cast<GamePvPOnline*>(windows[index_pvpOnline]);
        temp->disconnect();
    }

    // ���� single ���� ������ �� �������� ���� ���� ���� ���� ����� - ����� �������� ������
    if ((prev_state == GameState::MainMenu || prev_state == GameState::GameoverMenu) && current_state == GameState::GamePlaying)
    {
        Game* temp = dynamic_cast<Game*>(windows[index]);
        temp->restart();
    }
    // ���� pvp (local/pvp) ���� ������ �� �������� ���� ���� ���� ���� ����� - ����� �������� ������
    else if ((prev_state == GameState::MainMenu || prev_state == GameState::GameoverPvPMenu) && (current_state == GameState::GamePlayingPvPLocal || current_state == GameState::GamePlayingPvPOnline))
    {
        GamePvPLocal* temp = dynamic_cast<GamePvPLocal*>(windows[index]);
        temp->restart();
    }
    // ���� �� pvp online ����� � ������� ���� ��� �� ����� ����� ������� � pvp online
    if (current_state == GameState::GamePlayingPvPOnline || current_state == GameState::MainMenu)
    {
        pvp_online_pause_case = false;
    }
    
    // ���� �������� �� ��������� ����, �������� ���������� ���� � ��� ����
    else if (current_state == GameState::GameoverMenu)
    {
        GameOverMenu* gameovermenu_temp = dynamic_cast<GameOverMenu*>(windows[index]);
        Game* game_temp = dynamic_cast<Game*>(windows[static_cast<size_t>(prev_state)]);
        gameovermenu_temp->setScore(game_temp->getScore()); // �������� ���������
        gameovermenu_temp->checkNewRecord(); // ��������� ����� �� ������
        gameovermenu_temp->setUPtext();
    }
    // ���� �������� �� pvp ����
    else if (current_state == GameState::GameoverPvPMenu)
    {
        GameOverPvPMenu* gameovermenu_temp = dynamic_cast<GameOverPvPMenu*>(windows[index]);
        GamePvPLocal* game_temp = dynamic_cast<GamePvPLocal*>(windows[static_cast<size_t>(prev_state)]);
        gameovermenu_temp->setScore_left(game_temp->getScore_left());
        gameovermenu_temp->setScore_right(game_temp->getScore_right());
        gameovermenu_temp->checkNewRecord(); // ��������� ����� �� ������ ����� �� �������
        gameovermenu_temp->setUPtext();
        gameovermenu_temp->setPrevState(prev_state); // online or local
    }
    // ���� ������� - ��������� � �����
    else if (current_state == GameState::HighscoreMenu)
    {
        HighscoreMenu* highscoremenu_temp = dynamic_cast<HighscoreMenu*>(windows[index]);
        highscoremenu_temp->setScore(highscoremenu_temp->readRecord());
        highscoremenu_temp->setUPtext();
    }
    // ���� ����� - �������� ����. ���� (��������� ���� ��� pvp; ���� �������� �� ��������) 
    else if (current_state == GameState::PauseMenu && prev_state != GameState::OptionsMenu)
    {
        // ���� � ����� ����� �� pvponline �� �� ���������� ����
        if (prev_state == GameState::GamePlayingPvPOnline)
        {
            pvp_online_pause_case = true;
        }
        PauseMenu* pausemenu_temp = dynamic_cast<PauseMenu*>(windows[index]);
        pausemenu_temp->setPrevState(prev_state);
    }
    // ���� ��������� - �������� ����. ���� (���� ��� �����)
    else if (current_state == GameState::OptionsMenu)
    {
        OptionsMenu* optionsmenu_temp = dynamic_cast<OptionsMenu*>(windows[index]);
        optionsmenu_temp->setPrevState(prev_state);
    }

    // ������ ����� ���� ��������
    windows[index]->set_Active();
}



void GameManager::checkPvPOnlinePauseCase()
{
    if (pvp_online_pause_case)
    {
        windows[index_pvpOnline]->draw();
    }
}