#include <GL/freeglut.h>
#include <string>
#include "strokeCharacters.h"

const float strokeCharacters::FONT_BASEHEIGHT = 119.05;

strokeCharacters::strokeCharacters(void* Font, std::string s, float Scale, float lnw, float x, float y)
	: font{ Font }, name{ s }, scale{ Scale }, lnWidth{ lnw }, posx{ x }, posy{ y } {}

void strokeCharacters::setPos(float x, float y)
{
	posx = x;
	posy = y;
}

void strokeCharacters::displayStrokeCharacters() const
{
	glPushMatrix();
	glLineWidth(lnWidth);
	glTranslatef(posx, posy, 0.0f);
	glScalef(scale / FONT_BASEHEIGHT, scale / FONT_BASEHEIGHT, scale / FONT_BASEHEIGHT);
	for (int i = 0; i < name.size(); i++)
		glutStrokeCharacter(font, name[i]);
	glPopMatrix();
}

float strokeCharacters::getTextWidth() const
{
	float width{};
	for (char s : name)
		width += glutStrokeWidth(font, s);
	return width;
}

void strokeCharacters::centeredText()
{
	setPos( -getTextWidth() * scale / FONT_BASEHEIGHT / 2.0, posy);
}

float strokeCharacters::getScale() const
{
	return scale;
}