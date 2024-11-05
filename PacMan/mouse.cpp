#include <GL/freeglut.h>
#include "mouse.h"
#include "constant.h"

// buttons : GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, GLUT_RIGHT_BUTTON
// states : GLUT_DOWN, GLUT_UP

float changeCorX(float x)
{
	return x - WINDOW_WIDTH / 2.0;
}

float changeCorY(float y)
{
	return WINDOW_HEIGHT / 2.0 - y;
}

void mouse_main(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		x = changeCorX(x);
		y = changeCorY(y);
		if (PLAY_MENU.checkMousePtr(x, y))
			windowState = INGAME;
		if (SCOREBOARD_MENU.checkMousePtr(x, y))
			windowState = SCORE_BOARD;
		if (QUIT_MENU.checkMousePtr(x, y))
			glutLeaveMainLoop();
	}
	glutPostRedisplay();
}

void mouse_ingame(int button, int state, int x, int y)
{
	// TO DO
}

void mouse_end(int button, int state, int x, int y)
{
	// TO DO
}

void mouse_savescore(int button, int state, int x, int y)
{
	// TO DO
}

void mouse_scoreboard(int button, int state, int x, int y)
{
	// TO DO
}