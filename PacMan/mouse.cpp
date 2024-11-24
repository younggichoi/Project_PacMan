#include <GL/freeglut.h>
#include <fstream>
#include <string>
#include <iostream>
#include <list>
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

void save_score(std::string& name, unsigned int scr)
{
	std::ofstream saveFile("score_table.txt", std::ios::app );
	saveFile << name << ' ' << scr << '\n';
	saveFile.close();
}

void read_score(std::list<std::string>& str, std::list<int>& scr)
{
	str.clear();
	scr.clear();
	std::ifstream readFile("score_table.txt");
	if (!readFile.is_open())
		return;
	std::string name;
	int score;
	while (readFile >> name)
	{
		readFile >> score;
		auto itr2 = str.begin();
		for (auto itr = scr.begin(); itr != scr.end(); itr++, itr2++)
		{
			if (score > *itr)
			{
				scr.insert(itr, score);
				str.insert(itr2, name);
				if (scr.size() > MAX_RANK_NUM)
				{
					scr.pop_back();
					str.pop_back();
				}
				break;
			}
		}
		if (itr2 == str.end() && str.size() < MAX_RANK_NUM)
		{
			scr.push_back(score);
			str.push_back(name);
		}
	}
	readFile.close();
	high_score = *scr.begin(); // high_score update
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
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		x = changeCorX(x);
		y = changeCorY(y);
		if (savingState)
		{
			if (SAVE_BUTTON.checkMousePtr(x, y))
			{
				// player name을 빈칸으로 할 경우 저장이 안되게 해야함
				save_score(player_name, pacman.getScore());
				player_name = "";
				pacman.initialize();
				savingState = false;
				windowState = SCORE_BOARD;
				read_score(ranker_name, ranker_score);
			}
		}
		else
		{
			if (SAVE_YES_MENU.checkMousePtr(x, y))
				savingState = true;
			if (SAVE_NO_MENU.checkMousePtr(x, y))
			{
				windowState = MAIN;
				pacman.initialize();
			}
		}
	}
}

void mouse_scoreboard(int button, int state, int x, int y)
{
	// TO DO
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		x = changeCorX(x);
		y = changeCorY(y);
		if (GOTO_MAIN.checkMousePtr(x, y))
			windowState = MAIN;
	}
}