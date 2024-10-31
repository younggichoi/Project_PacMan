#include <GL/freeglut.h>

#define WINDOW_POS_X 120
#define WINDOW_POS_Y 55

#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 300

enum WINDOW_STATE {
	START,
	INGAME,
	END,
	SCORE_BOARD
};

WINDOW_STATE windowState;

void initialize()
{
	windowState = START;
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (windowState == START)
	{
		// TO DO
	}
	else if (windowState == INGAME)
	{
		// TO DO
	}
	else if (windowState == END)
	{
		// TO DO
	}
	else if (windowState == SCORE_BOARD)
	{
		// TO DO
	}
	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{

}

void mouse(int button, int state, int x, int y)
{
	// buttons : GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, GLUT_RIGHT_BUTTON
	// states : GLUT_DOWN, GLUT_UP
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		// Change state
	}
}

void idle()
{

}

int main(int argc, char** argv)
{
	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(WINDOW_POS_X, WINDOW_POS_Y);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("PacMan");
	initialize();

	// register callbacks
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutIdleFunc(idle);

	// enter GLUT event processing cycle
	glutMainLoop();
}