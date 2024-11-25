#include <GL/freeglut.h>
#include <array>
#include "display.h"
#include "idle.h"
#include "keyboard.h"
#include "mouse.h"
#include "specialkey.h"
#include "constant.h"
#include "Map.h"
#include "Sphere.h"
#include "Light.h"

const float WINDOW_POS_X = 300.f;
const float WINDOW_POS_Y = 40.f;

const float PACMAN_RADIUS = BLOCK_SIZE / 2;
const float GHOST_RADIUS = BLOCK_SIZE / 2;

WINDOW_STATE windowState;

std::list<std::string> ranker_name{};
std::list<int> ranker_score{};

// map container
std::array<Map, STAGE_NUM> maps;

// map color
const float BLOCK_COLOR_R = 0.098;
const float BLOCK_COLOR_G = 0.098;
const float BLOCK_COLOR_B = 0.439;

const float DOT_COLOR_R = 1.0;
const float DOT_COLOR_G = 0.95;
const float DOT_COLOR_B = 0.8;

// pacman
PacMan pacman(PACMAN_RADIUS, 10, 10, 0);

// ghosts
Ghost blinky(GHOST_RADIUS, 10, 10, Ghost::BLINKY, Ghost::CHASE);
Ghost pinky(GHOST_RADIUS, 10, 10, Ghost::PINKY, Ghost::CHASE);
Ghost inky(GHOST_RADIUS, 10, 10, Ghost::INKY, Ghost::CHASE);
Ghost clyde(GHOST_RADIUS, 10, 10, Ghost::CLYDE, Ghost::CHASE);

// light
extern Light light;

// text for centered
extern strokeCharacters HIGH_SCORE_TEXT;

void initialize()
{
	windowState = INGAME;
	//windowState = SAVE_SCORE;
	PLAY_MENU.centeredText();
	SCOREBOARD_MENU.centeredText();
	QUIT_MENU.centeredText();
	SAVE_YES_MENU.centeredText();
	SAVE_NO_MENU.centeredText();
	SAVE_BUTTON.centeredText();
	GOTO_MAIN.centeredText();
	HIGH_SCORE_TEXT.centeredText();
	read_score(ranker_name, ranker_score);

	// light setting
	light.setAmbient(0.3, 0.3, 0.3, 1.0);
	light.setDiffuse(0.8, 0.8, 0.7, 1.0);
	light.setSpecular(0.5, 0.5, 0.5, 1.0);

	// pacman setting
	Material pacman_mtl;
	pacman_mtl.setAmbient(1.0, 1.0, 0.4, 1.0);
	pacman_mtl.setDiffuse(1.0, 1.0, 0.0, 1.0);
	pacman_mtl.setSpecular(0.3, 0.3, 0.0, 1.0);
	pacman_mtl.setShininess(10.0);
	pacman_mtl.setEmission(1.0, 1.0, 0.2, 1.0);
	pacman.setMTL(pacman_mtl);

	// ghost setting
	Material blinky_mtl;
	blinky_mtl.setEmission(0.3f, 0.0f, 0.0f, 1.0f);
	blinky_mtl.setAmbient(0.6f, 0.1f, 0.1f, 1.0f);
	blinky_mtl.setDiffuse(0.8f, 0.0f, 0.0f, 1.0f);
	blinky_mtl.setSpecular(0.5f, 0.1f, 0.1f, 1.0f);
	blinky_mtl.setShininess(50.0f);
	blinky.setMTL(blinky_mtl);

	Material pinky_mtl;
	pinky_mtl.setEmission(0.2f, 0.1f, 0.2f, 1.0f);
	pinky_mtl.setAmbient(0.8f, 0.4f, 0.8f, 1.0f);
	pinky_mtl.setDiffuse(0.9f, 0.5f, 0.9f, 1.0f);
	pinky_mtl.setSpecular(0.6f, 0.3f, 0.6f, 1.0f);
	pinky_mtl.setShininess(40.0f);
	pinky.setMTL(pinky_mtl);

	Material inky_mtl;
	inky_mtl.setEmission(0.0f, 0.0f, 0.3f, 1.0f);
	inky_mtl.setAmbient(0.2f, 0.2f, 0.6f, 1.0f);
	inky_mtl.setDiffuse(0.4f, 0.4f, 0.9f, 1.0f);
	inky_mtl.setSpecular(0.5f, 0.5f, 0.7f, 1.0f);
	inky_mtl.setShininess(60.0f);
	inky.setMTL(inky_mtl);

	Material clyde_mtl;
	clyde_mtl.setEmission(0.3f, 0.2f, 0.0f, 1.0f);
	clyde_mtl.setAmbient(0.7f, 0.4f, 0.1f, 1.0f);
	clyde_mtl.setDiffuse(1.0f, 0.5f, 0.2f, 1.0f);
	clyde_mtl.setSpecular(0.8f, 0.5f, 0.3f, 1.0f);
	clyde_mtl.setShininess(30.0f);
	clyde.setMTL(clyde_mtl);

	// create stage1
	maps[0].createMap("stage1_layout.txt");
	maps[0].setBlockColor(BLOCK_COLOR_R, BLOCK_COLOR_G, BLOCK_COLOR_B);
	maps[0].setDotColor(DOT_COLOR_R, DOT_COLOR_G, DOT_COLOR_B);
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

