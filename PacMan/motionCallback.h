#pragma once
#include "constant.h"

void motionCallback_main(int x, int y);
void motionCallback_ingame(int x, int y);
void motionCallback_end(int x, int y);
void motionCallback_savescore(int x, int y);
void motionCallback_scoreboard(int x, int y);

// definition is at mouse.cpp
float changeCorX(float x);
float changeCorY(float y);

// definition is at display.cpp
extern Vector3f MAINMENU_COLOR;
extern Vector3f SAVEMENU_COLOR;
extern Vector3f GOTO_MAIN_COLOR;