#pragma once
#include <string>
#include "constant.h"

void display_main();
void display_ingame();
void display_end();
void display_savescore();
void display_scoreboard();

void displayStrokeCharacters(void* font, std::string c, float scale, float lnWidth, float x, float y);
float getTextWidth(void* font, std::string c);

void drawMenubox(float x, float y, float radius, float w, float h, unsigned int segment_num);
void drawMenu(float x, float y, float radius, float w, float h, unsigned int segment_num, std::string name, float lnWidth);