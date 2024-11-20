#pragma once
#include <GL/freeglut.h>
#include <string>

class strokeCharacters
{
public:
	static const float FONT_BASEHEIGHT;
	strokeCharacters(void* Font = GLUT_STROKE_ROMAN, std::string s = std::string{}, float Scale = 0, float lnw = 0, float x = 0, float y = 0);
	void setPos(float x, float y);
	void displayStrokeCharacters() const;
	float getTextWidth() const;
	void centeredText();
	float getScale() const;
private:
	void* font;
	std::string name;
	float scale, lnWidth, posx, posy;
};