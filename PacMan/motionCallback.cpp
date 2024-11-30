#include "motionCallback.h"
#include "menubox.h"
#include "Vector3f.h"

Vector3f POINTED_COLOR{ 0.8, 1.0, 0.9 };

const int POINTED_lnWIDTH = 2.5f;
const int DEFAULT_lnWIDTH = 1.f;

void motionCallback_main(int x, int y) {
	x = changeCorX(x);
	y = changeCorY(y);

	if (PLAY_MENU.checkMousePtr(x, y)) {
		PLAY_MENU.setColor(POINTED_COLOR);
		PLAY_MENU.setlnWidth(POINTED_lnWIDTH);
		PLAY_MENU.setTextlnWidth(POINTED_lnWIDTH);
	}
	else {
		PLAY_MENU.setColor(MAINMENU_COLOR);
		PLAY_MENU.setlnWidth(DEFAULT_lnWIDTH);
		PLAY_MENU.setTextlnWidth(MENU_MAIN_lnWIDTH);
	}

	if (SCOREBOARD_MENU.checkMousePtr(x, y)) {
		SCOREBOARD_MENU.setColor(POINTED_COLOR);
		SCOREBOARD_MENU.setlnWidth(POINTED_lnWIDTH);
		SCOREBOARD_MENU.setTextlnWidth(POINTED_lnWIDTH);
	}
	else {
		SCOREBOARD_MENU.setColor(MAINMENU_COLOR);
		SCOREBOARD_MENU.setlnWidth(DEFAULT_lnWIDTH);
		SCOREBOARD_MENU.setTextlnWidth(MENU_MAIN_lnWIDTH);
	}

	if (QUIT_MENU.checkMousePtr(x, y)) {
		QUIT_MENU.setColor(POINTED_COLOR);
		QUIT_MENU.setlnWidth(POINTED_lnWIDTH);
		QUIT_MENU.setTextlnWidth(POINTED_lnWIDTH);
	}
	else {
		QUIT_MENU.setColor(MAINMENU_COLOR);
		QUIT_MENU.setlnWidth(DEFAULT_lnWIDTH);
		QUIT_MENU.setTextlnWidth(MENU_MAIN_lnWIDTH);
	}
}

void motionCallback_ingame(int x, int y) {

}

void motionCallback_end(int x, int y) {

}

void motionCallback_savescore(int x, int y) {
	x = changeCorX(x);
	y = changeCorY(y);

	if (SAVE_YES_MENU.checkMousePtr(x, y)) {
		SAVE_YES_MENU.setColor(POINTED_COLOR);
		SAVE_YES_MENU.setlnWidth(POINTED_lnWIDTH);
		SAVE_YES_MENU.setTextlnWidth(POINTED_lnWIDTH);
	}
	else {
		SAVE_YES_MENU.setColor(SAVEMENU_COLOR);
		SAVE_YES_MENU.setlnWidth(DEFAULT_lnWIDTH);
		SAVE_YES_MENU.setTextlnWidth(MENU_SAVESCORE_lnWIDTH);
	}

	if (SAVE_NO_MENU.checkMousePtr(x, y)) {
		SAVE_NO_MENU.setColor(POINTED_COLOR);
		SAVE_NO_MENU.setlnWidth(POINTED_lnWIDTH);
		SAVE_NO_MENU.setTextlnWidth(POINTED_lnWIDTH);
	}
	else {
		SAVE_NO_MENU.setColor(SAVEMENU_COLOR);
		SAVE_NO_MENU.setlnWidth(DEFAULT_lnWIDTH);
		SAVE_NO_MENU.setTextlnWidth(MENU_SAVESCORE_lnWIDTH);
	}

	if (SAVE_BUTTON.checkMousePtr(x, y)) {
		SAVE_BUTTON.setColor(POINTED_COLOR);
		SAVE_BUTTON.setlnWidth(POINTED_lnWIDTH);
		SAVE_BUTTON.setTextlnWidth(POINTED_lnWIDTH);
	}
	else {
		SAVE_BUTTON.setColor(SAVEMENU_COLOR);
		SAVE_BUTTON.setlnWidth(DEFAULT_lnWIDTH);
		SAVE_BUTTON.setTextlnWidth(SAVE_BUTTON_lnWIDTH);
	}
}

void motionCallback_scoreboard(int x, int y) {
	x = changeCorX(x);
	y = changeCorY(y);

	if (GOTO_MAIN.checkMousePtr(x, y)) {
		GOTO_MAIN.setColor(POINTED_COLOR);
		GOTO_MAIN.setlnWidth(POINTED_lnWIDTH);
		GOTO_MAIN.setTextlnWidth(POINTED_lnWIDTH);
	}
	else {
		GOTO_MAIN.setColor(GOTO_MAIN_COLOR);
		GOTO_MAIN.setlnWidth(DEFAULT_lnWIDTH);
		GOTO_MAIN.setTextlnWidth(MENU_SCOREBOARD_lnWIDTH);
	}
}