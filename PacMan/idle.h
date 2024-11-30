#pragma once
#include "Map.h"
#include "Sphere.h"

void idle_main();
void idle_ingame();
void idle_end();
void idle_savescore();
void idle_scoreboard();

//void updateDirection();
bool checkClear(Map& map);
void createItem(Map& map);
void deleteItem(Map& map);

void updateDirectionOfPacMan();
void updateDirectionOfGhost(Ghost& ghost, int targetX, int targetY);
void updatePacMan();
void updateGhost(Ghost& ghost);

void ingameInit();