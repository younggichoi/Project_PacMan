#include <GL/freeglut.h>
#include "display.h"
#include <string>
#include <cmath>
#include "strokeCharacters.h"
#include "menubox.h"

const float TITLE_SCALE = 80.0;
const float TITLE_lnWIDTH = 2.0;
const float TITLE_HEIGHT_POS = WINDOW_HEIGHT / 4.0;

const std::string TITLE = "Pac Man";
const std::string PLAY = "PLAY";
const std::string SCOREBOARD = "SCOREBOARD";
const std::string QUIT = "QUIT";

const float	MENUBOX_HEIGHT = WINDOW_HEIGHT / 9.0;
const float MENUBOX_WIDTH = WINDOW_WIDTH / 2.0;
const float MENUBOX_GAP = WINDOW_HEIGHT / 20.0;
const float MENUBOX_RADIUS = 20.0;
const float MENU_lnWIDTH = 1.0;
const unsigned int MENUBOX_SEGMENT_NUM = 10;

strokeCharacters TITLE_CHAR{ GLUT_STROKE_ROMAN, TITLE, TITLE_SCALE, TITLE_lnWIDTH, 0, 0 };

menubox PLAY_MENU{ -MENUBOX_WIDTH / 2, 0, MENUBOX_RADIUS, MENUBOX_WIDTH, MENUBOX_HEIGHT, MENUBOX_SEGMENT_NUM, PLAY, MENU_lnWIDTH };
menubox SCOREBOARD_MENU{ -MENUBOX_WIDTH / 2, -MENUBOX_HEIGHT - MENUBOX_GAP, MENUBOX_RADIUS, MENUBOX_WIDTH, MENUBOX_HEIGHT, MENUBOX_SEGMENT_NUM, SCOREBOARD, MENU_lnWIDTH };
menubox QUIT_MENU{ -MENUBOX_WIDTH / 2, -(MENUBOX_HEIGHT + MENUBOX_GAP) * 2 , MENUBOX_RADIUS, MENUBOX_WIDTH, MENUBOX_HEIGHT, MENUBOX_SEGMENT_NUM, QUIT, MENU_lnWIDTH };

void display_main()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-WINDOW_WIDTH / 2.0, WINDOW_WIDTH / 2.0, -WINDOW_HEIGHT / 2.0, WINDOW_HEIGHT / 2.0, -100.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(0.0f, 1.0f, 0.0f);
	
	TITLE_CHAR.setPos( -TITLE_CHAR.getTextWidth() * TITLE_SCALE / strokeCharacters::FONT_BASEHEIGHT / 2.0, TITLE_HEIGHT_POS);
	TITLE_CHAR.displayStrokeCharacters();
	
	PLAY_MENU.drawMenubox();
	SCOREBOARD_MENU.drawMenubox();
	QUIT_MENU.drawMenubox();
	glutSwapBuffers();
}

void display_ingame()
{
	// TO DO
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-WINDOW_WIDTH / 2.0, WINDOW_WIDTH / 2.0, -WINDOW_HEIGHT / 2.0, WINDOW_HEIGHT / 2.0, -100.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(0.0f, 1.0f, 0.0f);
	glutSwapBuffers();
}

void display_end()
{
	// TO DO
}

void display_savescore()
{
	// TO DO
}

void display_scoreboard()
{
	// TO DO
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-WINDOW_WIDTH / 2.0, WINDOW_WIDTH / 2.0, -WINDOW_HEIGHT / 2.0, WINDOW_HEIGHT / 2.0, -100.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(0.0f, 1.0f, 0.0f);
	glutSwapBuffers();
}