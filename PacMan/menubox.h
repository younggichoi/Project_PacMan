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
	void setTextColor(float r, float g, float b);
	void setTextColor(Vector3f& v);
	void setlnWidth(const float lnw);
	void setTextlnWidth(const float lnw);
	void drawMenubox(bool fill = false) const;
	bool checkMousePtr(float x, float y) const;
private:
	float posx, posy, radius, width, height;
	float lnWidth = 1.f;
	unsigned int segment_num;
	strokeCharacters name;
	Vector3f color;
};