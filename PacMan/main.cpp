#include <GL/freeglut.h>
#include <array>
#include "display.h"
#include "idle.h"
#include "keyboard.h"
#include "mouse.h"
#include "specialkey.h"
#include "constant.h"
#include "Map.h"

const float WINDOW_POS_X = 300.f;
const float WINDOW_POS_Y = 40.f;

WINDOW_STATE windowState;

std::list<std::string> ranker_name{};
std::list<int> ranker_score{};

// map container
std::array<Map, STAGE_NUM> maps;

void initialize()
{
	windowState = MAIN;
	// windowState = SCORE_BOARD;
	// score = 1155;
	PLAY_MENU.centeredText();
	SCOREBOARD_MENU.centeredText();
	QUIT_MENU.centeredText();
	SAVE_YES_MENU.centeredText();
	SAVE_NO_MENU.centeredText();
	SAVE_BUTTON.centeredText();
	GOTO_MAIN.centeredText();
	read_score(ranker_name, ranker_score);

	// create stage1
	maps[0].createMap("stage1_layout.txt");
}

void display()
{
	if (windowState == MAIN)
	{
		display_main();
	}
	else if (windowState == INGAME)
	{
		display_ingame();
	}
	else if (windowState == END)
	{
		display_end();
	}
	else if (windowState == SAVE_SCORE)
	{
		display_savescore();
	}
	else if (windowState == SCORE_BOARD)
	{
		display_scoreboard();
	}
}

void keyboard(unsigned char key, int x, int y)
{
	if (windowState == MAIN)
	{
		keyboard_main(key, x, y);
	}
	else if (windowState == INGAME)
	{
		keyboard_ingame(key, x, y);
	}
	else if (windowState == END)
	{
		keyboard_end(key, x, y);
	}
	else if (windowState == SAVE_SCORE)
	{
		keyboard_savescore(key, x, y);
	}
	else if (windowState == SCORE_BOARD)
	{
		keyboard_scoreboard(key, x, y);
	}
}

void specialkey(int key, int x, int y)
{
	if (windowState == MAIN)
	{
		specialkey_main(key, x, y);
	}
	else if (windowState == INGAME)
	{
		specialkey_ingame(key, x, y);
	}
	else if (windowState == END)
	{
		specialkey_end(key, x, y);
	}
	else if (windowState == SAVE_SCORE)
	{
		specialkey_savescore(key, x, y);
	}
	else if (windowState == SCORE_BOARD)
	{
		specialkey_scoreboard(key, x, y);
	}
}

void mouse(int button, int state, int x, int y)
{
	if (windowState == MAIN)
	{
		mouse_main(button, state, x, y);
	}
	else if (windowState == INGAME)
	{
		mouse_ingame(button, state, x, y);
	}
	else if (windowState == END)
	{
		mouse_end(button, state, x, y);
	}
	else if (windowState == SAVE_SCORE)
	{
		mouse_savescore(button, state, x, y);
	}
	else if (windowState == SCORE_BOARD)
	{
		mouse_scoreboard(button, state, x, y);
	}
}

void idle()
{
	if (windowState == MAIN)
	{
		idle_main();
	}
	else if (windowState == INGAME)
	{
		idle_ingame();
	}
	else if (windowState == END)
	{
		idle_end();
	}
	else if (windowState == SAVE_SCORE)
	{
		idle_savescore();
	}
	else if (windowState == SCORE_BOARD)
	{
		idle_scoreboard();
	}
}

int main(int argc, char** argv)
{
	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(WINDOW_POS_X, WINDOW_POS_Y);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("PacMan");
	// glMatrixMode(GL_PROJECTION);
	// glOrtho(-WINDOW_WIDTH / 2, WINDOW_WIDTH / 2, -WINDOW_HEIGHT / 2, WINDOW_HEIGHT / 2, -1.f, 50.f);
	initialize();

	// register callbacks
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialkey);
	glutMouseFunc(mouse);
	glutIdleFunc(idle);

	// enter GLUT event processing cycle
	glutMainLoop();
}

