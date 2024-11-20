#include "GameManager.h"


GameManager::GameManager(std::vector<BaseWindow*>& wins) : 
    windows(wins),
    pvp_online_pause_case(false)
{

    // считаем индекс окна PvPOnline
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

    // отдельная обработка для выхода из игры
    if (current_state == GameState::Exit)
    {
        index = 999;
        return;
    }

    index = static_cast<size_t>(current_state);

    // находясь в меню нужно отсоединится от сервера
    if (current_state == GameState::MainMenu)
    {
        GamePvPOnline* temp = dynamic_cast<GamePvPOnline*>(windows[index_pvpOnline]);
        temp->disconnect();
    }

    // если single игра начата из главного меню либо окна гейм овера - нужно сбросить фигуры
    if ((prev_state == GameState::MainMenu || prev_state == GameState::GameoverMenu) && current_state == GameState::GamePlaying)
    {
        Game* temp = dynamic_cast<Game*>(windows[index]);
        temp->restart();
    }
    // если pvp (local/pvp) игра начата из главного меню либо окна гейм овера - нужно сбросить фигуры
    else if ((prev_state == GameState::MainMenu || prev_state == GameState::GameoverPvPMenu) && (current_state == GameState::GamePlayingPvPLocal || current_state == GameState::GamePlayingPvPOnline))
    {
        GamePvPLocal* temp = dynamic_cast<GamePvPLocal*>(windows[index]);
        temp->restart();
    }
    // если из pvp online вышли в главное меню или из паузы зашли обратно в pvp online
    if (current_state == GameState::GamePlayingPvPOnline || current_state == GameState::MainMenu)
    {
        pvp_online_pause_case = false;
    }
    
    // если геймовер из одиночной игры, передаем результаты игры в это окно
    else if (current_state == GameState::GameoverMenu)
    {
        GameOverMenu* gameovermenu_temp = dynamic_cast<GameOverMenu*>(windows[index]);
        Game* game_temp = dynamic_cast<Game*>(windows[static_cast<size_t>(prev_state)]);
        gameovermenu_temp->setScore(game_temp->getScore()); // передаем результат
        gameovermenu_temp->checkNewRecord(); // проверяем побит ли рекорд
        gameovermenu_temp->setUPtext();
    }
    // если геймовер из pvp игры
    else if (current_state == GameState::GameoverPvPMenu)
    {
        GameOverPvPMenu* gameovermenu_temp = dynamic_cast<GameOverPvPMenu*>(windows[index]);
        GamePvPLocal* game_temp = dynamic_cast<GamePvPLocal*>(windows[static_cast<size_t>(prev_state)]);
        gameovermenu_temp->setScore_left(game_temp->getScore_left());
        gameovermenu_temp->setScore_right(game_temp->getScore_right());
        gameovermenu_temp->checkNewRecord(); // проверяем побит ли рекорд одним из игроков
        gameovermenu_temp->setUPtext();
        gameovermenu_temp->setPrevState(prev_state); // online or local
    }
    // если хайскор - считываем с файла
    else if (current_state == GameState::HighscoreMenu)
    {
        HighscoreMenu* highscoremenu_temp = dynamic_cast<HighscoreMenu*>(windows[index]);
        highscoremenu_temp->setScore(highscoremenu_temp->readRecord());
        highscoremenu_temp->setUPtext();
    }
    // если пауза - передаем пред. окно (одиночная игра или pvp; меню настроек не передаем) 
    else if (current_state == GameState::PauseMenu && prev_state != GameState::OptionsMenu)
    {
        // если в паузу зашли из pvponline то не прекращаем игру
        if (prev_state == GameState::GamePlayingPvPOnline)
        {
            pvp_online_pause_case = true;
        }
        PauseMenu* pausemenu_temp = dynamic_cast<PauseMenu*>(windows[index]);
        pausemenu_temp->setPrevState(prev_state);
    }
    // если настройки - передаем пред. окно (меню или пауза)
    else if (current_state == GameState::OptionsMenu)
    {
        OptionsMenu* optionsmenu_temp = dynamic_cast<OptionsMenu*>(windows[index]);
        optionsmenu_temp->setPrevState(prev_state);
    }

    // делаем новое окно активным
    windows[index]->set_Active();
}



void GameManager::checkPvPOnlinePauseCase()
{
    if (pvp_online_pause_case)
    {
        windows[index_pvpOnline]->draw();
    }
}