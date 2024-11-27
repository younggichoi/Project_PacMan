#pragma once
#include <string>
#include <list>
#include "constant.h"
#include "Sphere.h"
#include "Map.h"

void mouse_main(int button, int state, int x, int y);
void mouse_ingame(int button, int state, int x, int y);
void mouse_end(int button, int state, int x, int y);
void mouse_savescore(int button, int state, int x, int y);
void mouse_scoreboard(int button, int state, int x, int y);

float changeCorX(float x);
float changeCorY(float y);

void save_score(std::string& name, unsigned int scr);
void read_score(std::list<std::string>& str, std::list<int>& scr);

extern PacMan pacman;

extern Ghost::STATE ghost_state;

extern std::array<Map, STAGE_NUM> maps;

// definition is at idle.cpp
void createItem(Map& map);
void deleteItem(Map& map);