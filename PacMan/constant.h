#pragma once
#include <list>
#include "menubox.h"

# define M_PI 3.141592653589793238462643383279502884L

// declaration is at main.cpp
extern const float WINDOW_WIDTH;
extern const float WINDOW_HEIGHT;

enum WINDOW_STATE {
	MAIN,
	INGAME,
	END,
	SAVE_SCORE,
	SCORE_BOARD
};

extern WINDOW_STATE windowState;

// declaration is at display.cpp
extern menubox PLAY_MENU;
extern menubox SCOREBOARD_MENU;
extern menubox QUIT_MENU;
extern menubox SAVE_YES_MENU;
extern menubox SAVE_NO_MENU;

extern unsigned int score;

extern bool savingState;

extern std::string player_name;

extern menubox SAVE_BUTTON;

extern const int MAX_RANK_NUM;

extern menubox GOTO_MAIN;

// declaration is at main.cpp
extern std::list<std::string> ranker_name;
extern std::list<int> ranker_score;