#pragma once
#include <string>
#include "constant.h"
#include "Map.h"
#include "Sphere.h"

void display_main();
void display_ingame();
void display_end();
void display_savescore();
void display_scoreboard();

// constant.h에서 해당 변수를 정의하면 순환참조 문제가 발생하기 때문에 이곳에서 선언
extern std::array<Map, STAGE_NUM> maps;

extern PacMan pacman;