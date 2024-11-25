#pragma once
#include "Map.h"

void idle_main();
void idle_ingame();
void idle_end();
void idle_savescore();
void idle_scoreboard();

void updateDirection();
bool checkClear(Map& map);
void createItem(Map& map);
void deleteItem(Map& map);