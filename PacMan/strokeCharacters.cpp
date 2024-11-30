#include <GL/freeglut.h>
#include <string>
#include "strokeCharacters.h"

const float strokeCharacters::FONT_BASEHEIGHT = 119.05;

strokeCharacters::strokeCharacters(void* Font, std::string s, Vector3f color_v, float Scale, float lnw, float x, float y)
	: font{ Font }, name{ s }, scale{ Scale }, lnWidth{ lnw }, posx{ x }, posy{ y }, color{ color_v } {}

void strokeCharacters::setColor(float r, float g, float b)
{
	color.setPos(r, g, b);
}

void strokeCharacters::setColor(Vector3f& v)
{
	color = v;
}

void strokeCharacters::setlnWidth(const float lnw)
{
	lnWidth = lnw;
}

void strokeCharacters::setPos(float x, float y)
{
	posx = x;
	posy = y;
}

void strokeCharacters::displayStrokeCharacters() const
{
	glPushMatrix();
	glColor3f(color[0], color[1], color[2]);
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