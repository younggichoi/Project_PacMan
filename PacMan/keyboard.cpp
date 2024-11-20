#include <GL/freeglut.h>
#include <cctype>
#include "keyboard.h"
#include "constant.h"

/* constants for savescore */
const unsigned int MAX_LENGTH = 10;

void keyboard_main(unsigned char key, int x, int y)
{
	// TO DO
}

void keyboard_ingame(unsigned char key, int x, int y)
{
	// TO DO
}

void keyboard_end(unsigned char key, int x, int y)
{
	// TO DO
}

void keyboard_savescore(unsigned char key, int x, int y)
{
	// TO DO
	if (savingState)
	{
		if (key == 8 && player_name.length() != 0)
			player_name.erase(player_name.end() - 1);
		else if (player_name.length() < MAX_LENGTH && (isalpha(key) || isdigit(key)))
			player_name += key;
	}
	glutPostRedisplay();
}

void keyboard_scoreboard(unsigned char key, int x, int y)
{
	// TO DO
}