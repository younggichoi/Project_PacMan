#include <GL/freeglut.h>
#include "specialkey.h"
#include "Sphere.h"
#include "constant.h"

extern PacMan pacman;
extern WINDOW_STATE windowState;
extern bool currStageClear, allStageClear, STOPFLAG;
extern int stage_num, eTime;
extern float stageClear_sTime;

// keys : GLUT_KEY_LEFT, GLUT_KEY_RIGHT, GLUT_KEY_UP, GLUT_KEY_DOWN

void specialkey_main(int key, int x, int y)
{
	// TO DO
}

void specialkey_ingame(int key, int x, int y)
{
	// TO DO
	switch (key) {
	case GLUT_KEY_LEFT:
		pacman.setNextDirection(Sphere::DIRECTION::LEFT);
		break;
	case GLUT_KEY_UP:
		pacman.setNextDirection(Sphere::DIRECTION::UP);
		break;
	case GLUT_KEY_RIGHT:
		pacman.setNextDirection(Sphere::DIRECTION::RIGHT);
		break;
	case GLUT_KEY_DOWN:
		pacman.setNextDirection(Sphere::DIRECTION::DOWN);
		break;
	case GLUT_KEY_F1:
		if (stage_num < 2) {
			currStageClear = true;
		}
		else if (stage_num == 2) {
			allStageClear = true;
		}
		STOPFLAG = true;
		stageClear_sTime = eTime;
		break;
	default:
		break;
	}

	glutPostRedisplay();
}

void specialkey_end(int key, int x, int y)
{
	// TO DO

}

void specialkey_savescore(int key, int x, int y)
{
	// TO DO
}

void specialkey_scoreboard(int key, int x, int y)
{
	// TO DO
}
