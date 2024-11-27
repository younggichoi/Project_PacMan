#include <GL/freeglut.h>
#include <random>
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

Ghost::STATE ghost_state = Ghost::STATE::CHASE;

const float CHASE_SCATTER_TIME = 15000.f;
const float FRIGHTENED_TIME = 15000.f;
const float FRIGHTENED_NORMAL_TIME = 5000.f;
float chase_scatter_sTime;

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
            // TODO: 초기위치로 setTargetPosition
            if (ghost.getName() == Ghost::BLINKY) {
                targetX = 1; targetY = 2;
            }
            else if (ghost.getName() == Ghost::PINKY) {
                targetX = 1; targetY = 27;
            }
            else if (ghost.getName() == Ghost::INKY) {
                targetX = 26; targetY = 27;
            }
            else if (ghost.getName() == Ghost::CLYDE) {
                targetX = 26; targetY = 2;
            }
        }

        updateDirectionOfGhost(ghost, targetX, targetY);
    }
    ghost.move();
}

bool checkClear(Map& map)
{
    for (int row = 0; row < NUM_ROW; row++)
    {
        for (int col = 0; col < NUM_COL; col++)
        {
            if (!map.getDot(col, row).getEaten())
                return false;
        }
    }
    return true;
}

void createItem(Map& map)   // 맵에서 item이 없다는 전제가 필요
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> whatitem(1, 3);
    int dot_count = 0;
    for (int row = 0; row < NUM_ROW; row++)
    {
        for (int col = 0; col < NUM_COL; col++)
        {
            if (!map.getDot(col, row).getEaten() && map.getDot(col, row).getSize() == Dot::DOTSIZE::SMALL)
                dot_count++;
        }
    }
    if (!dot_count)  return;
    // 맵에 small dot이 존재할 경우
    std::uniform_int_distribution<> whatdot(1, dot_count);
    Dot::DOTSIZE target_item;
    switch (whatitem(gen))
    {
    case 1:
        target_item = Dot::DOTSIZE::ITEM1;
        break;

    case 2:
        target_item = Dot::DOTSIZE::ITEM2;
        break;

    case 3:
        target_item = Dot::DOTSIZE::ITEM3;
        break;
    }
    int dot_test;
    for (int row = 0; row < NUM_ROW; row++)
    {
        for (int col = 0; col < NUM_COL; col++)
        {
            if (!map.getDot(col, row).getEaten() && map.getDot(col, row).getSize() == Dot::DOTSIZE::SMALL)
            {
                dot_test = whatdot(gen);
                if (dot_test == 1)
                {
                    map.getDot(col, row).setDotsize(target_item);
                    return;
                }
            }
        }
        if (row == NUM_ROW - 1)
            row = 0;
    }
}

void deleteItem(Map& map)
{
    for (int row = 0; row < NUM_ROW; row++)
    {
        for (int col = 0; col < NUM_COL; col++)
        {
            if (!map.getDot(col, row).getEaten() && map.getDot(col, row).getSize() > 5)
                map.getDot(col, row).setDotsize(Dot::DOTSIZE::SMALL);
        }
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
        updatePacMan();
        updateGhost(blinky);
        colHandler(pacman, blinky);
        updateGhost(pinky);
        colHandler(pacman, pinky);
        updateGhost(inky);
        colHandler(pacman, inky);
        updateGhost(clyde);
        colHandler(pacman, clyde);
        colHandler(pacman, maps[stage_num].getDot(pacman.getXIndex(), pacman.getYIndex()));
        if (pacman.getXIndex() + 1 != NUM_COL) {
            colHandler(pacman, maps[stage_num].getDot(pacman.getXIndex() + 1, pacman.getYIndex()));
        }
        else {
            colHandler(pacman, maps[stage_num].getDot(0, pacman.getYIndex()));
        }
        if (pacman.getYIndex() + 1 != NUM_ROW) {
            colHandler(pacman, maps[stage_num].getDot(pacman.getXIndex(), pacman.getYIndex() + 1));
        }
        else {
            colHandler(pacman, maps[stage_num].getDot(pacman.getXIndex(), 0));
        }
        if (pacman.getXIndex() - 1 != -1) {
            colHandler(pacman, maps[stage_num].getDot(pacman.getXIndex() - 1, pacman.getYIndex()));
        }
        else {
            colHandler(pacman, maps[stage_num].getDot(NUM_COL - 1, pacman.getYIndex()));
        }
        if (pacman.getYIndex() - 1 != -1) {
            colHandler(pacman, maps[stage_num].getDot(pacman.getXIndex(), pacman.getYIndex() - 1));
        }
        else{
            colHandler(pacman, maps[stage_num].getDot(pacman.getXIndex(), NUM_ROW - 1));
        }

        sTime = eTime;
        glutPostRedisplay();
    }
    
    if (eTime - chase_scatter_sTime > CHASE_SCATTER_TIME)
    {
        if (ghost_state == Ghost::STATE::CHASE)
        {
            ghost_state = Ghost::STATE::SCATTER;
            // 고스트들의 state를 SCATTER로 변경
            if (blinky.getState() == Ghost::STATE::CHASE)
                blinky.setState(Ghost::STATE::SCATTER);
            if (pinky.getState() == Ghost::STATE::CHASE)
                pinky.setState(Ghost::STATE::SCATTER);
            if (inky.getState() == Ghost::STATE::CHASE)
                inky.setState(Ghost::STATE::SCATTER);
            if (clyde.getState() == Ghost::STATE::CHASE)
                clyde.setState(Ghost::STATE::SCATTER);
        }
        else if (ghost_state == Ghost::STATE::SCATTER)
        {
            ghost_state = Ghost::STATE::CHASE;
            // 고스트들의 state를 CHASE로 변경
            if (blinky.getState() == Ghost::STATE::SCATTER)
                blinky.setState(Ghost::STATE::CHASE);
            if (pinky.getState() == Ghost::STATE::SCATTER)
                pinky.setState(Ghost::STATE::CHASE);
            if (inky.getState() == Ghost::STATE::SCATTER)
                inky.setState(Ghost::STATE::CHASE);
            if (clyde.getState() == Ghost::STATE::SCATTER)
                clyde.setState(Ghost::STATE::CHASE);
        }
        chase_scatter_sTime = eTime;
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
