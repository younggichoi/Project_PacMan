#pragma once
#include <GL/freeglut.h>
#include <string>
#include "strokeCharacters.h"

class menubox
{
public:
	menubox(float x, float y, float r, float w, float h, unsigned int n, std::string s, float lnw);
	void centeredText();
	void drawMenubox() const;
	bool checkMousePtr(float x, float y) const;
private:
	float posx, posy, radius, width, height, lnWidth;
	unsigned int segment_num;
	strokeCharacters name;
};