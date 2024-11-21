#include <GL/freeglut.h>
#include "specialkey.h"
#include "Sphere.h"

extern PacMan pacman;

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