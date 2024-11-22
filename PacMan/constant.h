#pragma once
#include <list>
#include "menubox.h"
//#include "Map.h"

# define M_PI 3.141592653589793238462643383279502884L

inline const float WINDOW_WIDTH = 640.f;
inline const float WINDOW_HEIGHT = 750.f;

inline const float BOUNDARY_X = WINDOW_WIDTH / 2;
inline const float BOUNDARY_Y = WINDOW_HEIGHT / 2;

inline const int NUM_ROW = 30;
inline const int NUM_COL = 28;

inline const float BLOCK_SIZE = 20.f;
inline const float MOVE_SPEED = 1.f;

// map boundary
inline const float LEFT_BOUNDARY = -(NUM_COL / 2) * BLOCK_SIZE;
inline const float RIGHT_BOUNDARY = (NUM_COL / 2) * BLOCK_SIZE;
inline const float TOP_BOUNDARY = (NUM_COL / 2) * BLOCK_SIZE;
inline const float BOTTOM_BOUNDARY = -(NUM_COL / 2) * BLOCK_SIZE;

inline const int STAGE_NUM = 3;

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

extern int stage_num;

// declaration is at main.cpp
extern std::list<std::string> ranker_name;
extern std::list<int> ranker_score;

//extern std::array<Map, STAGE_NUM> maps;
