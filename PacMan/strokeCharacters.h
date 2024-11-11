#pragma once
#include <GL/freeglut.h>
#include <string>

class strokeCharacters
{
public:
	static const float FONT_BASEHEIGHT;
	strokeCharacters(void* Font, std::string s, float Scale, float lnw, float x, float y);
	void setPos(float x, float y);
	void displayStrokeCharacters() const;
	float getTextWidth() const;
private:
	void* font;
	std::string name;
	float scale, lnWidth, posx, posy;
};