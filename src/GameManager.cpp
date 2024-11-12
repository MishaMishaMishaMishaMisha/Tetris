#include "GameManager.h"


size_t GameManager::get_state()
{
    if (isChanged())
    {
        updateState();
    }
    return index;
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

    // ���� ���� ������ �� �������� ���� ���� ���� ���� ����� - ����� �������� ������
    if ((prev_state == GameState::MainMenu || prev_state == GameState::GameoverMenu) && current_state == GameState::GamePlaying)
    {
        Game* temp = dynamic_cast<Game*>(windows[index]);
        temp->restart();
    }

    // ���� pvp local ���� ������ �� �������� ���� ���� ���� ���� ����� - ����� �������� ������
    if ((prev_state == GameState::MainMenu || prev_state == GameState::GameoverPvPMenu) && current_state == GameState::GamePlayingPvPLocal)
    {
        GamePvPLocal* temp = dynamic_cast<GamePvPLocal*>(windows[index]);
        temp->restart();
    }

    // ���� ��������, �������� ���������� ���� � ��� ����
    if (current_state == GameState::GameoverMenu)
    {
        GameOverMenu* gameovermenu_temp = dynamic_cast<GameOverMenu*>(windows[index]);
        Game* game_temp = dynamic_cast<Game*>(windows[static_cast<size_t>(prev_state)]);
        gameovermenu_temp->setScore(game_temp->getScore()); // �������� ���������
        gameovermenu_temp->checkNewRecord(); // ��������� ����� �� ������
        gameovermenu_temp->setUPtext();
    }

    // ���� �������� �� pvp ����
    if (current_state == GameState::GameoverPvPMenu)
    {
        GameOverPvPMenu* gameovermenu_temp = dynamic_cast<GameOverPvPMenu*>(windows[index]);
        GamePvPLocal* game_temp = dynamic_cast<GamePvPLocal*>(windows[static_cast<size_t>(prev_state)]);
        gameovermenu_temp->setScore_left(game_temp->getScore_left());
        gameovermenu_temp->setScore_right(game_temp->getScore_right());
        gameovermenu_temp->checkNewRecord(); // ��������� ����� �� ������ ����� �� �������
        gameovermenu_temp->setUPtext();
    }

    // ���� ������� - ��������� � �����
    if (current_state == GameState::HighscoreMenu)
    {
        HighscoreMenu* highscoremenu_temp = dynamic_cast<HighscoreMenu*>(windows[index]);
        highscoremenu_temp->setScore(highscoremenu_temp->readRecord());
        highscoremenu_temp->setUPtext();
    }

    // ���� ����� - �������� ����. ���� (��������� ���� ��� pvp, ���� �������� �� ��������) 
    if (current_state == GameState::PauseMenu && prev_state != GameState::OptionsMenu)
    {
        PauseMenu* pausemenu_temp = dynamic_cast<PauseMenu*>(windows[index]);
        pausemenu_temp->setPrevState(prev_state);
    }

    // ���� ��������� - �������� ����. ���� (���� ��� �����)
    if (current_state == GameState::OptionsMenu)
    {
        OptionsMenu* optionsmenu_temp = dynamic_cast<OptionsMenu*>(windows[index]);
        optionsmenu_temp->setPrevState(prev_state);
    }

    // ������ ����� ���� ��������
    windows[index]->set_Active();
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