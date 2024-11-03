#include "GameManager.h"


int GameManager::get_state()
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

    // отдельная обработка для выхода из игры
    if (current_state == GameState::Exit)
    {
        index = -1;
        return;
    }

    index = static_cast<int>(current_state);

    // если игра начата из главного меню либо окна гейм овера - нужно сбросить фигуры
    if ((prev_state == GameState::MainMenu || prev_state == GameState::GameoverMenu) && current_state == GameState::GamePlaying)
    {
        Game* temp = dynamic_cast<Game*>(windows[index]);
        temp->restart();
    }

    // если геймовер, передаем результаты игры в это окно
    if (current_state == GameState::GameoverMenu)
    {
        GameOverMenu* gameovermenu_temp = dynamic_cast<GameOverMenu*>(windows[index]);
        Game* game_temp = dynamic_cast<Game*>(windows[static_cast<int>(prev_state)]);
        gameovermenu_temp->setScore(game_temp->getScore()); // передаем результат
        gameovermenu_temp->checkNewRecord(); // проверяем побит ли рекорд
        gameovermenu_temp->setUPtext();
    }

    // если хайскор - считываем с файла
    if (current_state == GameState::HighscoreMenu)
    {
        HighscoreMenu* highscoremenu_temp = dynamic_cast<HighscoreMenu*>(windows[index]);
        highscoremenu_temp->setScore(highscoremenu_temp->readRecord());
        highscoremenu_temp->setUPtext();
    }

    // если настройки - передаем пред. окно (меню или пауза)
    if (current_state == GameState::OptionsMenu)
    {
        OptionsMenu* optionsmenu_temp = dynamic_cast<OptionsMenu*>(windows[index]);
        optionsmenu_temp->setPrevState(prev_state);
    }

    // делаем новое окно активным
    windows[index]->set_Active();
}

void GameManager::setState(GameState& state)
{
    current_state = state;
    index = static_cast<int>(current_state);
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