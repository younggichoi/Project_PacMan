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

// constant.h���� �ش� ������ �����ϸ� ��ȯ���� ������ �߻��ϱ� ������ �̰����� ����
extern std::array<Map, STAGE_NUM> maps;

extern PacMan pacman;