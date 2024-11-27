#include <GL/freeglut.h>
#include "idle.h"
#include "Sphere.h"
#include "Map.h"
#include "CollisionHandler.h"

extern PacMan pacman;

extern Ghost blinky, pinky, inky, clyde;

extern std::array<Map, STAGE_NUM> maps;

const int FPS = 60;
int sTime = 0;
int eTime = 0;

CollisionHandler colHandler;

void updateDirectionOfPacMan() {
    int xIdx = pacman.getXIndex();
    int yIdx = pacman.getYIndex();
    int lx, ly, rx, ry, tx, ty, bx, by;
    
    if (xIdx - 1 != -1) {
        lx = xIdx - 1;
        ly = yIdx;
    }
    else {
        lx = NUM_COL - 1;
        ly = yIdx;
    }
    if (xIdx + 1 != NUM_COL) {
        rx = xIdx + 1;
        ry = yIdx;
    }
    else {
        rx = 0;
        ry = yIdx;
    }
    if (yIdx - 1 != -1) {
        tx = xIdx;
        ty = yIdx - 1;    // top
    }
    else {
        tx = xIdx;
        ty = NUM_ROW - 1;
    }
    if (yIdx + 1 != NUM_ROW) {
        bx = xIdx;
        by = yIdx + 1;
    }
    else {
        bx = xIdx;
        by = 0;
    }
    const Block& lBlock = maps[0].getBlock(lx, ly);    // left
    const Block& rBlock = maps[0].getBlock(rx, ry);    // right
    const Block& tBlock = maps[0].getBlock(tx, ty);    // top
    const Block& bBlock = maps[0].getBlock(bx, by);    // bottom

    // update direction
    Sphere::DIRECTION nextDir = pacman.getNextDirection();
    switch (nextDir)
    {
    case Sphere::NONE:
        break;
    case Sphere::LEFT:
        if (lBlock.isPassable())
            pacman.updateDirection();
        break;
    case Sphere::UP:
        if (tBlock.isPassable())
            pacman.updateDirection();
        break;
    case Sphere::RIGHT:
        if (rBlock.isPassable())
            pacman.updateDirection();
        break;
    case Sphere::DOWN:
        if (bBlock.isPassable())
            pacman.updateDirection();
        break;
    default:
        break;
    }
}

void updateDirectionOfGhost(Ghost& ghost, int targetX, int targetY) {
    /* Implement */
    // block indices
    int idx[2] = { ghost.getXIndex(), ghost.getYIndex() };

    int lIdx[2] = { idx[0] - 1 , idx[1] };  // left
    int tIdx[2] = { idx[0], idx[1] - 1 };   // top
    int rIdx[2] = { idx[0] + 1, idx[1] };   // right
    int bIdx[2] = { idx[0], idx[1] + 1 };   // bottom
    
    if (lIdx[0] == -1) {
        lIdx[0] = NUM_COL - 1;
    }
    if (tIdx[1] == -1) {
        tIdx[1] = NUM_ROW - 1;
    }
    if (rIdx[0] == NUM_COL) {
        rIdx[0] = 0;
    }
    if (bIdx[1] == NUM_ROW) {
        bIdx[1] = 0;
    }

    const Block& lBlock = maps[0].getBlock(lIdx[0], lIdx[1]);// left
    const Block& tBlock = maps[0].getBlock(tIdx[0], tIdx[1]);// top
    const Block& rBlock = maps[0].getBlock(rIdx[0], rIdx[1]);// right
    const Block& bBlock = maps[0].getBlock(bIdx[0], bIdx[1]);// bottom

    Sphere::DIRECTION currDir = ghost.getCurrentDirection();
    Sphere::DIRECTION newDir = Sphere::DIRECTION::NONE;
    int minIdxDist = INT_MAX;
    // left
    if (lBlock.isPassable() && currDir != Sphere::DIRECTION::RIGHT) {
        // calculate distance
        int dist = (targetX - lIdx[0]) * (targetX - lIdx[0]) + (targetY - lIdx[1]) * (targetY - lIdx[1]);
        if (dist < minIdxDist) {
            minIdxDist = dist;
            newDir = Sphere::DIRECTION::LEFT;
        }
    }
    // top
    if (tBlock.isPassable() && currDir != Sphere::DIRECTION::DOWN) {
        // calculate distance
        int dist = (targetX - tIdx[0]) * (targetX - tIdx[0]) + (targetY - tIdx[1]) * (targetY - tIdx[1]);
        if (dist < minIdxDist) {
            minIdxDist = dist;
            newDir = Sphere::DIRECTION::UP;
        }
    }
    // right
    if (rBlock.isPassable() && currDir != Sphere::DIRECTION::LEFT) {
        // calculate distance
        int dist = (targetX - rIdx[0]) * (targetX - rIdx[0]) + (targetY - rIdx[1]) * (targetY - rIdx[1]);
        if (dist < minIdxDist) {
            minIdxDist = dist;
            newDir = Sphere::DIRECTION::RIGHT;
        }
    }
    // bottom
    if (bBlock.isPassable() && currDir != Sphere::DIRECTION::UP) {
        // calculate distance
        int dist = (targetX - bIdx[0]) * (targetX - bIdx[0]) + (targetY - bIdx[1]) * (targetY - bIdx[1]);
        if (dist < minIdxDist) {
            minIdxDist = dist;
            newDir = Sphere::DIRECTION::DOWN;
        }
    }

    ghost.setNextDirection(newDir);
    ghost.updateDirection();
}

void updatePacMan() {
    // update PacMan
    bool bNoDir = pacman.getCurrentDirection() == Sphere::DIRECTION::NONE;
    bool bIdxPosUpdated = pacman.isIndexPositionUpdated();
    if (bNoDir || bIdxPosUpdated) {
        updateDirectionOfPacMan();
        colHandler(pacman, maps[0]);
    }
    pacman.move();
}

void updateGhost(Ghost& ghost) {
    /* Implement */
    // update Ghost
    bool bNoDir = ghost.getCurrentDirection() == Sphere::DIRECTION::NONE;
    bool bIdxPosUpdated = ghost.isIndexPositionUpdated();
    if (bNoDir || bIdxPosUpdated) {
        int targetX = 0;
        int targetY = 0;

        // set target
        if (ghost.getState() == Ghost::CHASE) {
            if (ghost.getName() == Ghost::BLINKY) {
                targetX = pacman.getXIndex();
                targetY = pacman.getYIndex();
            }
            else if (ghost.getName() == Ghost::PINKY) {
                if (pacman.getCurrentDirection() == Sphere::DIRECTION::LEFT) {
                    if (pacman.getXIndex() - 4 >= 0) {
                        targetX = pacman.getXIndex()-4;
                        targetY = pacman.getYIndex();
                    }
                    else {
                        targetX = 0;
                        targetY = pacman.getYIndex();
                    }
                }
                else if (pacman.getCurrentDirection() == Sphere::DIRECTION::RIGHT) {
                    if (pacman.getXIndex() + 4 < NUM_COL) {
                        targetX = pacman.getXIndex() + 4;
                        targetY = pacman.getYIndex();
                    }
                    else {
                        targetX = NUM_COL - 1;
                        targetY = pacman.getYIndex();
                    }
                }
                else if (pacman.getCurrentDirection() == Sphere::DIRECTION::UP) {
                    if (pacman.getYIndex() - 4 >= 0) {
                        targetX = pacman.getXIndex();
                        targetY = pacman.getYIndex() - 4;
                    }
                    else {
                        targetX = pacman.getXIndex();
                        targetY = 0;
                    }
                }
                else if (pacman.getCurrentDirection() == Sphere::DIRECTION::DOWN) {
                    if (pacman.getYIndex() + 4 < NUM_ROW) {
                        targetX = pacman.getXIndex();
                        targetY = pacman.getYIndex() + 4;
                    }
                    else {
                        targetX = pacman.getXIndex();
                        targetY = NUM_ROW - 1;
                    }
                }
                else if (pacman.getCurrentDirection() == Sphere::DIRECTION::NONE) {
                    targetX = pacman.getXIndex();
                    targetY = pacman.getYIndex();
                }
            }
            else if (ghost.getName() == Ghost::INKY) {
                int bx = blinky.getXIndex();
                int by = blinky.getYIndex();
                int cx = 0;
                int cy = 0;
                if (pacman.getCurrentDirection() == Sphere::DIRECTION::UP) {
                    if (pacman.getYIndex() - 2 >= 0) {
                        cx = pacman.getXIndex();
                        cy = pacman.getYIndex() - 2;
                    }
                    else {
                        cx = pacman.getXIndex();
                        cy = 0;
                    }
                }
                else if (pacman.getCurrentDirection() == Sphere::DIRECTION::DOWN) {
                    if (pacman.getYIndex() + 2 < NUM_ROW) {
                        cx = pacman.getXIndex();
                        cy = pacman.getYIndex() + 2;
                    }
                    else {
                        cx = pacman.getXIndex();
                        cy = NUM_ROW - 1;
                    }
                }
                else if (pacman.getCurrentDirection() == Sphere::DIRECTION::LEFT) {
                    if (pacman.getXIndex() - 2 >= 0) {
                        cx = pacman.getXIndex() - 2;
                        cy = pacman.getYIndex();
                    }
                    else {
                        cx = 0;
                        cy = pacman.getYIndex();
                    }
                }
                else if (pacman.getCurrentDirection() == Sphere::DIRECTION::RIGHT) {
                    if (pacman.getYIndex() + 2 < NUM_COL) {
                        cx = pacman.getXIndex() + 2;
                        cy = pacman.getYIndex();
                    }
                    else {
                        cx = NUM_COL - 1;
                        cy = pacman.getYIndex();
                    }
                }
                else if (pacman.getCurrentDirection() == Sphere::DIRECTION::NONE) {
                    cx = pacman.getXIndex();
                    cy = pacman.getYIndex();
                }

                targetX = (bx - cx) * (-1) + cx;
                if (targetX < 0) {
                    targetX = 0;
                }
                else if (targetX >= NUM_COL) {
                    targetX = NUM_COL - 1;
                }
                targetY = (by - cy) * (-1) + cy;
                if (targetY < 0) {
                    targetY = 0;
                }
                else if (targetY >= NUM_ROW) {
                    targetY = NUM_ROW - 1;
                }
            }
            else if (ghost.getName() == Ghost::CLYDE) {
                int dist = (ghost.getXIndex() - pacman.getXIndex()) * (ghost.getXIndex() - pacman.getXIndex()) + (ghost.getYIndex() - pacman.getYIndex()) * (ghost.getYIndex() - pacman.getYIndex());
                if (dist >= 64) {
                    targetX = pacman.getXIndex();
                    targetY = pacman.getYIndex();
                }
                else {
                    targetX = 0;
                    targetY = NUM_ROW - 1;
                }
            }
        }
        else if (ghost.getState() == Ghost::SCATTER) {
            if (ghost.getName() == Ghost::BLINKY) {
                targetX = NUM_COL - 1;
                targetY = 0;
            }
            else if (ghost.getName() == Ghost::PINKY) {
                targetX = 0;
                targetY = 0;
            }
            else if (ghost.getName() == Ghost::INKY) {
                targetX = NUM_COL - 1;
                targetY = NUM_ROW - 1;
            }
            else if (ghost.getName() == Ghost::CLYDE) {
                targetX = 0;
                targetY = NUM_ROW - 1;
            }
        }
        else if (ghost.getState() == Ghost::FRIGHTENED) {
            int gx = ghost.getXIndex();
            int gy = ghost.getYIndex();
            int px = pacman.getXIndex();
            int py = pacman.getYIndex();

            targetX = ghost.getXIndex();
            targetY = ghost.getYIndex();
            if (gx > px) {
                targetX += 1;
                if (targetX == NUM_COL) {
                    targetX -= 1;
                }
            }
            else if (gx < px) {
                targetX -= 1;
                if (targetX == -1) {
                    targetX += 1;
                }
            }
            if (gy > py) {
                targetY += 1;
                if (targetY == NUM_ROW) {
                    targetY -= 1;
                }
            }
            else if (gy < py) {
                targetY -= 1;
                if (targetY == -1) {
                    targetY += 1;
                }
            }
        }
        else if (ghost.getState() == Ghost::EATEN) {
            // TODO: 초기위치 확정나면 바꾸기
            if (ghost.getName() == Ghost::BLINKY) {
                ghost.setCenter(0.0f, 0.0f, 0.0f);
            }
            else if (ghost.getName() == Ghost::PINKY) {
                ghost.setCenter(0.0f, 0.0f, 0.0f);
            }
            else if (ghost.getName() == Ghost::INKY) {
                ghost.setCenter(0.0f, 0.0f, 0.0f);
            }
            else if (ghost.getName() == Ghost::CLYDE) {
                ghost.setCenter(0.0f, 0.0f, 0.0f);
            }
        }

        updateDirectionOfGhost(ghost, targetX, targetY);
    }
    ghost.move();
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
        updatePacMan();
        updateGhost(blinky);
        colHandler(pacman, blinky);
        updateGhost(pinky);
        colHandler(pacman, pinky);
        updateGhost(inky);
        colHandler(pacman, inky);
        updateGhost(clyde);
        colHandler(pacman, clyde);
        // Dot colHandler 호출

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