#include <GL/freeglut.h>
#include <string>
#include "menubox.h"
#include "constant.h"
#include <cmath>

menubox::menubox(float x, float y, float r, float w, float h, unsigned int n, std::string s, float lnw)
	: posx{ x }, posy{ y }, radius{ r }, width{ w }, height{ h }, lnWidth{ lnw },
	segment_num{ n }, name{ GLUT_STROKE_ROMAN, s, width / 8.0f, lnWidth, 0, 0 } {}

void menubox::centeredText()
{
	name.setPos(posx + (width - name.getTextWidth() * width / 8.0 / strokeCharacters::FONT_BASEHEIGHT) / 2.0, posy - height + (height - width / 8.0) / 2.0);
}

void menubox::drawMenubox() const
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_POLYGON);
	for (int i = 0; i <= segment_num; i++)
		glVertex2f(posx + width - radius + radius * sin(M_PI / (2 * segment_num) * i), posy - radius + radius * cos(M_PI / (2 * segment_num) * i));
	for (int i = 0; i <= segment_num; i++)
		glVertex2f(posx + width - radius + radius * cos(M_PI / (2 * segment_num) * i), posy - height + radius - radius * sin(M_PI / (2 * segment_num) * i));
	for (int i = 0; i <= segment_num; i++)
		glVertex2f(posx + radius - radius * sin(M_PI / (2 * segment_num) * i), posy - height + radius - radius * cos(M_PI / (2 * segment_num) * i));
	for (int i = 0; i <= segment_num; i++)
		glVertex2f(posx + radius - radius * cos(M_PI / (2 * segment_num) * i), posy - radius + radius * sin(M_PI / (2 * segment_num) * i));
	glEnd();
	name.displayStrokeCharacters();
}

bool menubox::checkMousePtr(float x, float y) const
{
	if (x >= posx && x <= posx + width && y >= posy - height + radius && y <= posy - radius)
		return true;
	if (x >= posx + radius && x <= posx + width - radius && y >= posy - height && y <= posy)
		return true;
	if (pow(posx + radius - x, 2) + pow(posy - radius - y, 2) <= pow(radius, 2))
		return true;
	if (pow(posx + width - radius - x, 2) + pow(posy - radius - y, 2) <= pow(radius, 2))
		return true;
	if (pow(posx + radius - x, 2) + pow(posy - height + radius - y, 2) <= pow(radius, 2))
		return true;
	if (pow(posx + width - radius - x, 2) + pow(posy - height + radius - y, 2) <= pow(radius, 2))
		return true;
	return false;
}