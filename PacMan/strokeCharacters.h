#pragma once
#include <GL/freeglut.h>
#include <string>
#include "Vector3f.h"

class strokeCharacters
{
public:
	static const float FONT_BASEHEIGHT;
	strokeCharacters(void* Font = GLUT_STROKE_ROMAN, std::string s = std::string{}, Vector3f color_v = Vector3f{}, float Scale = 0, float lnw = 0, float x = 0, float y = 0);
	void setColor(float r, float g, float b);
	void setColor(Vector3f& v);
	void setPos(float x, float y);
	void displayStrokeCharacters() const;
	float getTextWidth() const;
	void centeredText();
	float getScale() const;
private:
	void* font;
	std::string name;
	float scale, lnWidth, posx, posy;
	Vector3f color;
};