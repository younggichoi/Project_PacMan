#include <GL/freeglut.h>
#include "display.h"
#include <string>
#include <cmath>
#include "strokeCharacters.h"
#include "menubox.h"

/* constants in main display */

// dimension of title text in main display
const float TITLE_SCALE = 80.0;
const float TITLE_lnWIDTH = 2.0;
const float TITLE_HEIGHT_POS = WINDOW_HEIGHT / 4.0;

// dimension of menubox in main display
const float	MENUBOX_MAIN_HEIGHT = WINDOW_HEIGHT / 9.0;
const float MENUBOX_MAIN_WIDTH = WINDOW_WIDTH / 2.0;
const float MENUBOX_MAIN_GAP = WINDOW_HEIGHT / 20.0;
const float MENUBOX_MAIN_RADIUS = 20.0;
const float MENU_MAIN_lnWIDTH = 1.0;
const float MENU_MAIN_SCALE = 40.0;
const unsigned int MENUBOX_MAIN_SEGMENT_NUM = 10;

// menubox initialization for main display
// define as global variable for interacting with mouse.cpp
strokeCharacters PLAY{ GLUT_STROKE_ROMAN, "PLAY", MENU_MAIN_SCALE, MENU_MAIN_lnWIDTH, 0, 0 };
strokeCharacters SCOREBOARD{ GLUT_STROKE_ROMAN, "SCOREBOARD", MENU_MAIN_SCALE, MENU_MAIN_lnWIDTH, 0, 0 };
strokeCharacters QUIT{ GLUT_STROKE_ROMAN, "QUIT", MENU_MAIN_SCALE, MENU_MAIN_lnWIDTH, 0, 0 };

menubox PLAY_MENU{ -MENUBOX_MAIN_WIDTH / 2, 0, MENUBOX_MAIN_RADIUS,
MENUBOX_MAIN_WIDTH, MENUBOX_MAIN_HEIGHT, MENUBOX_MAIN_SEGMENT_NUM, PLAY };
menubox SCOREBOARD_MENU{ -MENUBOX_MAIN_WIDTH / 2, -MENUBOX_MAIN_HEIGHT - MENUBOX_MAIN_GAP,
MENUBOX_MAIN_RADIUS, MENUBOX_MAIN_WIDTH, MENUBOX_MAIN_HEIGHT, MENUBOX_MAIN_SEGMENT_NUM, SCOREBOARD };
menubox QUIT_MENU{ -MENUBOX_MAIN_WIDTH / 2, -(MENUBOX_MAIN_HEIGHT + MENUBOX_MAIN_GAP) * 2 ,
MENUBOX_MAIN_RADIUS, MENUBOX_MAIN_WIDTH, MENUBOX_MAIN_HEIGHT, MENUBOX_MAIN_SEGMENT_NUM, QUIT };

/* constants in ingame state */

unsigned int score;

/* constants in end display */


/* constants in save_score display */

// dimension of text in save_score display
const float SCORE_SHOW_SCALE = 40;
const float SCORE_SHOW_lnWIDTH = 1.0;
const float SCORE_SHOW_HEIGHT_POS = WINDOW_HEIGHT * 0.3;

const float ASK_SAVING_SCALE = 35;
const float ASK_SAVING_lnWIDTH = 1.0;
const float ASK_SAVING_HEIGHT_POS = WINDOW_HEIGHT * 0.05;

// dimension of menubox in save_score display
const float MENUBOX_SAVESCORE_HEIGHT = WINDOW_HEIGHT * 0.15;
const float MENUBOX_SAVESCORE_WIDTH = WINDOW_WIDTH * 0.25;
const float MENUBOX_SAVESCORE_GAP = WINDOW_WIDTH * 0.15;
const float MENUBOX_SAVESCORE_HEIGHT_POS = WINDOW_HEIGHT * (-0.1);
const float MENUBOX_SAVESCORE_RADIUS = 20;
const unsigned int MENUBOX_SAVESCORE_SEGMENT_NUM = 10;
const float MENU_SAVESCORE_lnWIDTH = 1.0;
const float MENU_SAVESCORE_SCALE = 30.0;

// menubox initialization in save_score display
// define as global variable for interacting with mouse.cpp
strokeCharacters YES_SAVING{ GLUT_STROKE_ROMAN, "Yes", MENU_SAVESCORE_SCALE, MENU_SAVESCORE_lnWIDTH, 0, 0 };
strokeCharacters NO_SAVING{ GLUT_STROKE_ROMAN, "No", MENU_SAVESCORE_SCALE, MENU_SAVESCORE_lnWIDTH, 0, 0 };

menubox SAVE_YES_MENU{ -MENUBOX_SAVESCORE_WIDTH - MENUBOX_SAVESCORE_GAP / 2, MENUBOX_SAVESCORE_HEIGHT_POS, MENUBOX_SAVESCORE_RADIUS,
MENUBOX_SAVESCORE_WIDTH, MENUBOX_SAVESCORE_HEIGHT, MENUBOX_SAVESCORE_SEGMENT_NUM, YES_SAVING };
menubox SAVE_NO_MENU{ MENUBOX_SAVESCORE_GAP / 2, MENUBOX_SAVESCORE_HEIGHT_POS, MENUBOX_SAVESCORE_RADIUS,
MENUBOX_SAVESCORE_WIDTH, MENUBOX_SAVESCORE_HEIGHT, MENUBOX_SAVESCORE_SEGMENT_NUM, NO_SAVING };

// flag for saving state
bool savingState = false;

// name for saving score
std::string player_name{};

// dimension of window for entering player's name
const float SAVING_WINDOW_HEIGHT = WINDOW_HEIGHT * 0.6;
const float SAVING_WINDOW_WIDTH = WINDOW_WIDTH * 0.7;
const float SAVING_WINDOW_HEIGHT_POS = WINDOW_HEIGHT * 0.3;
const float SAVING_WINDOW_RADIUS = 30.0;
const unsigned int SAVING_WINDOW_SEGMENT_NUM = 15;

// distance between enter_name_text and upper boundary of saving window
const float ENTER_NAME_HEIGHT_POS = SAVING_WINDOW_HEIGHT * 0.1;

// dimension of enter_name_text
const float ENTER_NAME_SCALE = 35.0;
const float ENTER_NAME_lnWIDTH = 1.5;

// dimension of entered player's name
const float PLAYER_NAME_SCALE = 30.0;
const float PLAYER_NAME_lnWIDTH = 1.0;

// distance between enter line and entered player's name
const float PLAYER_NAME_GAP = 10.0;

// dimension of save button
const float SAVE_BUTTON_WIDTH = SAVING_WINDOW_WIDTH * 0.3;
const float SAVE_BUTTON_HEIGHT = SAVING_WINDOW_HEIGHT * 0.15;
const float SAVE_BUTTON_SCALE = 20.0;
const float SAVE_BUTTON_lnWIDTH = 1.0;
const float SAVE_BUTTON_RADIUS = 10.0;
const unsigned int SAVE_BUTTON_SEGMENT_NUM = 10;

// distance between save button and lower boundary of saving window
const float SAVE_BUTTON_GAP = SAVING_WINDOW_HEIGHT * 0.1;

// distance between enter line and lower boundary of saving window
const float ENTER_LINE_GAP = SAVING_WINDOW_HEIGHT * 0.4;

// dimension of enter position line
const float ENTER_LINE_WIDTH = 1.5;
const float ENTER_LINE_LENGTH = SAVING_WINDOW_WIDTH * 0.7;
const float ENTER_LINE_HEIGHT_POS = SAVING_WINDOW_HEIGHT_POS - SAVING_WINDOW_HEIGHT + ENTER_LINE_GAP;

// save button initialization in save window
// define as global variable for interacting with mouse.cpp
strokeCharacters SAVE_TEXT{ GLUT_STROKE_ROMAN, "SAVE", SAVE_BUTTON_SCALE, SAVE_BUTTON_lnWIDTH };

menubox SAVE_BUTTON{ -SAVE_BUTTON_WIDTH / 2, SAVING_WINDOW_HEIGHT_POS - SAVING_WINDOW_HEIGHT + SAVE_BUTTON_GAP + SAVE_BUTTON_HEIGHT,
SAVE_BUTTON_RADIUS, SAVE_BUTTON_WIDTH, SAVE_BUTTON_HEIGHT, SAVE_BUTTON_SEGMENT_NUM, SAVE_TEXT };

/* constants for scoreboard display */

// dimension of scoreboard title text
const float SCOREBOARD_TITLE_SCALE = 60.0;
const float SCOREBOARD_TITLE_lnWIDTH = 2.5;
const float SCOREBOARD_TITLE_HEIGHT_POS = WINDOW_HEIGHT * 0.35;

const float ATTRIBUTE_NAME_SCALE = 30.0;
const float ATTRIBUTE_NAME_lnWIDTH = 1.0;

// distance between attribute name and scoreboard title text
const float ATTRIBUTE_NAME_HEIGHT_POS = WINDOW_HEIGHT * 0.08;

const float RANK_WIDTH_POS = WINDOW_WIDTH * (-0.3);
const float NAME_WIDTH_POS = 0;
const float SCORE_WIDTH_POS = WINDOW_WIDTH * 0.3;

// maximum number of printed score in score board
const int MAX_RANK_NUM = 5;

const float DATA_SCALE = 25.0;
const float DATA_lnWIDTH = 1.0;
const float DATA_GAP = WINDOW_HEIGHT * 0.05;

// distance between 1st data and attribute name
const float DATA_HEIGHT_POS = WINDOW_HEIGHT * 0.05;

const float MENUBOX_SCOREBOARD_HEIGHT = WINDOW_HEIGHT * 0.1;
const float MENUBOX_SCOREBOARD_WIDTH = WINDOW_WIDTH * 0.3;
const float MENUBOX_SCOREBOARD_HEIGHT_POS = WINDOW_HEIGHT * (-0.3);
const float MENUBOX_SCOREBOARD_RADIUS = 20.0;
const unsigned int MENUBOX_SCOREBOARD_SEGMENT_NUM = 20;

const float MENU_SCOREBOARD_SCALE = 30.0;
const float MENU_SCOREBOARD_lnWIDTH = 1.2;

strokeCharacters GOTO_MAIN_TEXT{ GLUT_STROKE_ROMAN, "Main", MENU_SCOREBOARD_SCALE, MENU_SCOREBOARD_lnWIDTH };
menubox GOTO_MAIN{ -MENUBOX_SCOREBOARD_WIDTH / 2.0f, MENUBOX_SCOREBOARD_HEIGHT_POS, MENUBOX_SCOREBOARD_RADIUS,
MENUBOX_SCOREBOARD_WIDTH, MENUBOX_SCOREBOARD_HEIGHT, MENUBOX_SCOREBOARD_SEGMENT_NUM, GOTO_MAIN_TEXT };


void display_main()
{
	strokeCharacters TITLE_CHAR{ GLUT_STROKE_ROMAN, "Pac Man", TITLE_SCALE, TITLE_lnWIDTH, 0, TITLE_HEIGHT_POS};
	TITLE_CHAR.centeredText();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-WINDOW_WIDTH / 2.0, WINDOW_WIDTH / 2.0, -WINDOW_HEIGHT / 2.0, WINDOW_HEIGHT / 2.0, -100.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(0.0f, 1.0f, 0.0f);
	
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
	std::string SCORE_SHOW_TEXT = "Your score is " + std::to_string(score);
	strokeCharacters SCORE_SHOW(GLUT_STROKE_ROMAN, SCORE_SHOW_TEXT, SCORE_SHOW_SCALE, SCORE_SHOW_lnWIDTH, 0, SCORE_SHOW_HEIGHT_POS);
	SCORE_SHOW.centeredText();

	std::string ASK_SAVING_TEXT = "Do you want to save?";
	strokeCharacters ASK_SAVING(GLUT_STROKE_ROMAN, ASK_SAVING_TEXT, ASK_SAVING_SCALE, ASK_SAVING_lnWIDTH, 0, ASK_SAVING_HEIGHT_POS);
	ASK_SAVING.centeredText();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-WINDOW_WIDTH / 2.0, WINDOW_WIDTH / 2.0, -WINDOW_HEIGHT / 2.0, WINDOW_HEIGHT / 2.0, -100.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if (savingState)
		glColor3f(0.0f, 0.5f, 0.0f);
	else
		glColor3f(0.0f, 1.0f, 0.0f);

	SCORE_SHOW.displayStrokeCharacters();
	ASK_SAVING.displayStrokeCharacters();
	SAVE_YES_MENU.drawMenubox();
	SAVE_NO_MENU.drawMenubox();

	glColor3f(0.0f, 1.0f, 0.0f);

	if (savingState)
	{
		menubox SAVING_WINDOW{ -SAVING_WINDOW_WIDTH / 2, SAVING_WINDOW_HEIGHT_POS, SAVING_WINDOW_RADIUS,
			SAVING_WINDOW_WIDTH, SAVING_WINDOW_HEIGHT, SAVING_WINDOW_SEGMENT_NUM };
		strokeCharacters ENTER_NAME{ GLUT_STROKE_ROMAN, "Enter your name.",
			ENTER_NAME_SCALE, ENTER_NAME_lnWIDTH, 0, SAVING_WINDOW_HEIGHT_POS - ENTER_NAME_HEIGHT_POS };
		strokeCharacters PLAYER_NAME{ GLUT_STROKE_ROMAN, player_name, PLAYER_NAME_SCALE, PLAYER_NAME_lnWIDTH,
			0, ENTER_LINE_HEIGHT_POS + PLAYER_NAME_GAP + PLAYER_NAME_SCALE / strokeCharacters::FONT_BASEHEIGHT };
		ENTER_NAME.centeredText();
		PLAYER_NAME.centeredText();

		SAVING_WINDOW.drawMenubox(true);
		ENTER_NAME.displayStrokeCharacters();
		PLAYER_NAME.displayStrokeCharacters();
		glLineWidth(ENTER_LINE_WIDTH);
		glBegin(GL_LINES);
		glVertex2f(-ENTER_LINE_LENGTH / 2, ENTER_LINE_HEIGHT_POS);
		glVertex2f(ENTER_LINE_LENGTH / 2, ENTER_LINE_HEIGHT_POS);
		glEnd();
		SAVE_BUTTON.drawMenubox();
	}
	glutSwapBuffers();
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

	strokeCharacters SCOREBOARD_TITLE{ GLUT_STROKE_ROMAN, "Score Board", SCOREBOARD_TITLE_SCALE, SCOREBOARD_TITLE_lnWIDTH, 0, SCOREBOARD_TITLE_HEIGHT_POS };
	SCOREBOARD_TITLE.centeredText();
	strokeCharacters RANK_TEXT{ GLUT_STROKE_ROMAN, "Rank", ATTRIBUTE_NAME_SCALE, ATTRIBUTE_NAME_lnWIDTH };
	RANK_TEXT.setPos(RANK_WIDTH_POS - RANK_TEXT.getTextWidth() * ATTRIBUTE_NAME_SCALE / strokeCharacters::FONT_BASEHEIGHT / 2.0,
		SCOREBOARD_TITLE_HEIGHT_POS - ATTRIBUTE_NAME_HEIGHT_POS - ATTRIBUTE_NAME_SCALE);
	strokeCharacters NAME_TEXT{ GLUT_STROKE_ROMAN, "Name", ATTRIBUTE_NAME_SCALE, ATTRIBUTE_NAME_lnWIDTH };
	NAME_TEXT.setPos(NAME_WIDTH_POS - NAME_TEXT.getTextWidth() * ATTRIBUTE_NAME_SCALE / strokeCharacters::FONT_BASEHEIGHT / 2.0,
		SCOREBOARD_TITLE_HEIGHT_POS - ATTRIBUTE_NAME_HEIGHT_POS - ATTRIBUTE_NAME_SCALE);
	strokeCharacters SCORE_TEXT{ GLUT_STROKE_ROMAN, "Score", ATTRIBUTE_NAME_SCALE, ATTRIBUTE_NAME_lnWIDTH };
	SCORE_TEXT.setPos(SCORE_WIDTH_POS - SCORE_TEXT.getTextWidth() * ATTRIBUTE_NAME_SCALE / strokeCharacters::FONT_BASEHEIGHT / 2.0,
		SCOREBOARD_TITLE_HEIGHT_POS - ATTRIBUTE_NAME_HEIGHT_POS - ATTRIBUTE_NAME_SCALE);

	strokeCharacters RANK_DATA;
	strokeCharacters NAME_DATA;
	strokeCharacters SCORE_DATA;

	auto itr_name = ranker_name.begin();
	auto itr_score = ranker_score.begin();

	for (int i = 0; i < ranker_name.size(); i++)
	{
		RANK_DATA = strokeCharacters{ GLUT_STROKE_ROMAN, std::to_string(i + 1), DATA_SCALE, DATA_lnWIDTH };
		RANK_DATA.setPos(RANK_WIDTH_POS - RANK_DATA.getTextWidth() * DATA_SCALE / strokeCharacters::FONT_BASEHEIGHT / 2.0,
			SCOREBOARD_TITLE_HEIGHT_POS - ATTRIBUTE_NAME_HEIGHT_POS - ATTRIBUTE_NAME_SCALE - DATA_HEIGHT_POS - DATA_SCALE - (DATA_GAP + DATA_SCALE) * i);
		RANK_DATA.displayStrokeCharacters();

		NAME_DATA = strokeCharacters{ GLUT_STROKE_ROMAN, *itr_name, DATA_SCALE, DATA_lnWIDTH};
		NAME_DATA.setPos(NAME_WIDTH_POS - NAME_DATA.getTextWidth() * DATA_SCALE / strokeCharacters::FONT_BASEHEIGHT / 2.0,
			SCOREBOARD_TITLE_HEIGHT_POS - ATTRIBUTE_NAME_HEIGHT_POS - ATTRIBUTE_NAME_SCALE - DATA_HEIGHT_POS - DATA_SCALE - (DATA_GAP + DATA_SCALE) * i);
		NAME_DATA.displayStrokeCharacters();
		itr_name++;

		SCORE_DATA = strokeCharacters{ GLUT_STROKE_ROMAN, std::to_string(*itr_score), DATA_SCALE, DATA_lnWIDTH};
		SCORE_DATA.setPos(SCORE_WIDTH_POS - SCORE_DATA.getTextWidth() * DATA_SCALE / strokeCharacters::FONT_BASEHEIGHT / 2.0,
			SCOREBOARD_TITLE_HEIGHT_POS - ATTRIBUTE_NAME_HEIGHT_POS - ATTRIBUTE_NAME_SCALE - DATA_HEIGHT_POS - DATA_SCALE - (DATA_GAP + DATA_SCALE) * i);
		SCORE_DATA.displayStrokeCharacters();
		itr_score++;
	}

	SCOREBOARD_TITLE.displayStrokeCharacters();
	RANK_TEXT.displayStrokeCharacters();
	NAME_TEXT.displayStrokeCharacters();
	SCORE_TEXT.displayStrokeCharacters();
	GOTO_MAIN.drawMenubox();
	glutSwapBuffers();
}