#pragma once
#include <list>
#include "menubox.h"

# define M_PI 3.141592653589793238462643383279502884L

inline const float WINDOW_WIDTH = 640.f;
inline const float WINDOW_HEIGHT = 750.f;

inline const float BOUNDARY_X = WINDOW_WIDTH / 2;
inline const float BOUNDARY_Y = WINDOW_HEIGHT / 2;

inline const int NUM_ROW = 30;
inline const int NUM_COL = 28;

inline const float BLOCK_SIZE = 20.f;
inline const float MOVE_SPEED = 1.f;
// frightened state, slow item
inline const float SLOW_SPEED = 0.5f;

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

extern bool savingState;

extern std::string player_name;

extern menubox SAVE_BUTTON;

extern const int MAX_RANK_NUM;

extern menubox GOTO_MAIN;

extern int stage_num;

extern int high_score;

extern bool drawGhost;
extern bool drawPacman;
extern bool drawSurroundings;
extern bool stageReady;
extern bool respone;
extern bool stageFail;

extern bool STOPFLAG;
extern float stageReady_sTime;
extern float respone_sTime;
extern float stageFail_sTime;

// motionCallback.cpp에서 사용하는 const variable
inline const float MENU_MAIN_lnWIDTH = 1.0;
inline const float MENU_SAVESCORE_lnWIDTH = 1.0;
inline const float SAVE_BUTTON_lnWIDTH = 1.0;
inline const float MENU_SCOREBOARD_lnWIDTH = 1.2;

extern strokeCharacters READY_TEXT;

// declaration is at main.cpp
extern std::list<std::string> ranker_name;
extern std::list<int> ranker_score;

// declaration is at idle.cpp
extern float chase_scatter_sTime;