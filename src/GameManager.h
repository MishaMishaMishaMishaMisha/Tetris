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

// класс для переключения между окнами 
class GameManager
{

private:
	GameState current_state = GameState::MainMenu; // текущее окно
    size_t index = 0; // номер состояния (окна)
    std::vector<BaseWindow*>& windows; // ссылка на вектор с окнами


    // флаг на случай когда во время pvp online ставится пауза
    // то игра продолжается
    bool pvp_online_pause_case;
    size_t index_pvpOnline; // индекс в векторе окна PvPOnline

public:
    GameManager(std::vector<BaseWindow*>& wins);

    // вернуть номер текущего окна.
    // если текущее окно стало не активным, переключаем на след. окно
    size_t get_state();

    // переключение на след. окно
    void updateState();

    // установить новое окно
    void setState(GameState& state);

    // активно ли все еще текущее окно
    bool isChanged();



    // если флаг pvp_online_pause_case активен
    // то не прерываем работу этого окна
    void checkPvPOnlinePauseCase();
};

