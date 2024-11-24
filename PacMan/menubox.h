#pragma once
#include <GL/freeglut.h>
#include <string>
#include "strokeCharacters.h"

class menubox
{
public:
	menubox(float x, float y, float r, float w, float h, unsigned int n, Vector3f color_v, strokeCharacters s = strokeCharacters{});
	void centeredText();
	void setColor(float r, float g, float b);
	void setColor(Vector3f& v);
	void drawMenubox(bool fill = false) const;
	bool checkMousePtr(float x, float y) const;
private:
	float posx, posy, radius, width, height;
	unsigned int segment_num;
	strokeCharacters name;
	Vector3f color;
};