#pragma once
#include "Game.h";
#include "PauseMenu.h"
#include "MainMenu.h"
#include "GameOverMenu.h"
#include "HighscoreMenu.h"
#include "OptionsMenu.h"

// класс для переключения между окнами 
class GameManager
{

private:
	GameState current_state = GameState::MainMenu; // текущее окно
    int index = 0; // номер состояния (окна)
    std::vector<BaseWindow*>& windows; // вектор окон


public:
    GameManager(std::vector<BaseWindow*>& wins) : windows(wins) {}

    // вернуть номер текущего окна.
    // если текущее окно стало не активным, переключаем на след. окно
    int get_state();

    // переключение на след. окно
    void updateState();

    // установить новое окно
    void setState(GameState& state);

    // активно ли все еще текущее окно
    bool isChanged();

};

