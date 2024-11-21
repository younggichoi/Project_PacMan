#include <GL/freeglut.h>
#include "idle.h"
#include "Sphere.h"
#include "Map.h"
#include "CollisionHandler.h"

extern PacMan pacman;

extern std::array<Map, STAGE_NUM> maps;

const int FPS = 60;
int sTime = 0;
int eTime = 0;

CollisionHandler colHandler;

void updateDirection() {
    /* Implement */
    switch (pacman.getNextDirection()) {
    case Sphere::LEFT:
        if (maps[0].getBlock(pacman.getXIndex() - 1, pacman.getYIndex()).isPassable()) {
            pacman.updateDirection();
        }
        break;
    case Sphere::RIGHT:
        if (maps[0].getBlock(pacman.getXIndex() + 1, pacman.getYIndex()).isPassable()) {
            pacman.updateDirection();
        }
        break;
    case Sphere::UP:
        if (maps[0].getBlock(pacman.getXIndex(), pacman.getYIndex() - 1).isPassable()) {
            pacman.updateDirection();
        }
        break;
    case Sphere::DOWN:
        if (maps[0].getBlock(pacman.getXIndex(), pacman.getYIndex() + 1).isPassable()) {
            pacman.updateDirection();
        }
        break;
    default:
        //pacman.updateDirection();
        break;
    }

}

void idle_main()
{
	// TO DO
	glutPostRedisplay();
}

void idle_ingame()
{
	// TO DO
    float spf = 1000.0f / FPS;
    eTime = glutGet(GLUT_ELAPSED_TIME);

    if (eTime - sTime > spf) {
        bool bNoDir = pacman.getCurrentDirection() == Sphere::DIRECTION::NONE;
        bool bIdxPosUpdated = pacman.isIndexPositionUpdated();
        if (bNoDir || bIdxPosUpdated) {
            updateDirection();
            colHandler(pacman, maps[0]);
            cout << "PM: (" << pacman.getXIndex() << ", " << pacman.getYIndex() << ")" << endl;
        }

        pacman.move();

        sTime = eTime;
        glutPostRedisplay();
    }
}

void idle_end()
{
	// TO DO
}

void idle_savescore()
{
	// TO DO
}

void idle_scoreboard()
{
	// TO DO
}