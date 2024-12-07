#include <GL/freeglut.h>
#include <random>
#include <iostream>
#include "idle.h"
#include "Sphere.h"
#include "Map.h"
#include "CollisionHandler.h"

extern PacMan pacman;

extern Ghost blinky, pinky, inky, clyde;

extern std::array<Map, STAGE_NUM> maps;

const int FPS = 135;
int sTime = 0;
int eTime = 0;

CollisionHandler colHandler;

Ghost::STATE ghost_state = Ghost::STATE::CHASE;

// chase, scatter 지속시간
const float CHASE_SCATTER_TIME = 15000.f;
// frightened state 지속시간
const float FRIGHTENED_TIME = 20000.f;
// frightened state의 후반 ghost 점등 시간
const float FRIGHTENED_NORMAL_TIME = 5000.f;
// ghost 점등 주기
const float BLINK_TIME = 100.f;
float chase_scatter_sTime;
float frightened_sTime;
float blink_sTime;
float pblink_sTime;
// ghost가 점등하는 동안만 true로 설정
bool BLINK = false;
// pacman blink 지속시간
const float PACMAN_BLINK_TIME = 10000.f;
// pacman blink
bool pBLINK = false;
// large dot을 먹으면 true, FRIGHTENED_TIME이 지나면 false
bool FRIGHTENED = false;
// 일시적으로 행동 정지
bool STOPFLAG = false;
// 스테이지 클리어시 사용하는 sTime, time constants
bool currStageClear = false;
bool allStageClear = false;
float stageClear_sTime;
const float stageClear_Time1 = 1500.f;
const float stageClear_Time2 = 1500.f;
const float stageClear_Time3 = 1500.f;
// 스테이지 실패시 사용하는 sTime, time constants
bool stageFail = false;
float stageFail_sTime;
const float stageFail_Time1 = 1500.f;
const float stageFail_Time2 = 1500.f;
const float stageFail_Time3 = 1500.f;
// ready text 출력
bool stageReady = false;
float stageReady_sTime;
const float stageReady_Time = 1500.f;
// respone variables
bool respone = false;
float respone_sTime;
const float respone_Time1 = 1500.f;
const float respone_Time2 = 1500.f;
// item varaibles
bool getItem = false;
float getItem_sTime;
const float getItem_Time = 500.f;
// eatGhost varaibles
bool eatGhost = false;
float eatGhost_sTime;
const float eatGhost_Time = 500.f;
// frightened material
Material frightened_mtl;

// blink material
Material frightened_blink_mtl;

// ghost material
extern Material blinky_mtl, pinky_mtl, inky_mtl, clyde_mtl;

// pacman material
extern Material pacman_mtl;

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
    const Block& lBlock = maps[stage_num].getBlock(lx, ly);    // left
    const Block& rBlock = maps[stage_num].getBlock(rx, ry);    // right
    const Block& tBlock = maps[stage_num].getBlock(tx, ty);    // top
    const Block& bBlock = maps[stage_num].getBlock(bx, by);    // bottom

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

    const Block& lBlock = maps[stage_num].getBlock(lIdx[0], lIdx[1]);// left
    const Block& tBlock = maps[stage_num].getBlock(tIdx[0], tIdx[1]);// top
    const Block& rBlock = maps[stage_num].getBlock(rIdx[0], rIdx[1]);// right
    const Block& bBlock = maps[stage_num].getBlock(bIdx[0], bIdx[1]);// bottom

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
        colHandler(pacman, maps[stage_num]);
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

    // eaten state에서 초기 위치 도달시 normal state로 전환
    if (ghost.getState() == Ghost::EATEN) {
        if (ghost.getName() == Ghost::BLINKY && ghost.getXIndex() == 1 && ghost.getYIndex() == 2) {
            ghost.setState(ghost_state);
            ghost.setMTL(blinky_mtl);
            ghost.speedUp();
        }
        if (ghost.getName() == Ghost::PINKY && ghost.getXIndex() == 1 && ghost.getYIndex() == 27) {
            ghost.setState(ghost_state);
            ghost.setMTL(pinky_mtl);
            ghost.speedUp();
        }
        if (ghost.getName() == Ghost::INKY && ghost.getXIndex() == 26 && ghost.getYIndex() == 27) {
            ghost.setState(ghost_state);
            ghost.setMTL(inky_mtl);
            ghost.speedUp();
        }
        if (ghost.getName() == Ghost::CLYDE && ghost.getXIndex() == 26 && ghost.getYIndex() == 2) {
            ghost.setState(ghost_state);
            ghost.setMTL(clyde_mtl);
            ghost.speedUp();
        }
    }
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

void ingameInit() {
    maps[0].createMap("stage1_layout.txt");
    maps[1].createMap("stage2_layout.txt");
    maps[2].createMap("stage3_layout.txt");
    stageReady = false;
    currStageClear = false;
    allStageClear = false;
    respone = false;
    drawSurroundings = true;
    drawPacman = true;
    drawGhost = true;
    FRIGHTENED = false;
    BLINK = false;
    pBLINK = false;
    eatGhost = false;

    pacman.setCenter(0.0f, 0.0f, 0.0f);
    pacman.setIndexPosition(14, 14);
    blinky.setCenter(-260.0f, 240.0f, 0.0f);
    blinky.setIndexPosition(1, 2);
    pinky.setCenter(-260.0f, -240.0f, 0.0f);
    pinky.setIndexPosition(1, 27);
    inky.setCenter(240.0f, -240.0f, 0.0f);
    inky.setIndexPosition(26, 27);
    clyde.setCenter(240.0f, 240.0f, 0.0f);
    clyde.setIndexPosition(26, 2);
    // 리스폰 시 시작 위치가 어긋나는 버그 -> currdir, nextdir를 NONE으로 설정
    blinky.setCurrentDirection(Sphere::NONE);
    pinky.setCurrentDirection(Sphere::NONE);
    inky.setCurrentDirection(Sphere::NONE);
    clyde.setCurrentDirection(Sphere::NONE);
    pacman.setCurrentDirection(Sphere::NONE);
    blinky.setNextDirection(Sphere::NONE);
    pinky.setNextDirection(Sphere::NONE);
    inky.setNextDirection(Sphere::NONE);
    clyde.setNextDirection(Sphere::NONE);
    pacman.setNextDirection(Sphere::NONE);
    // 리스폰시 state를 모두 normal로
    blinky.setState(ghost_state);
    pinky.setState(ghost_state);
    inky.setState(ghost_state);
    clyde.setState(ghost_state);
    blinky.setMTL(blinky_mtl);
    pinky.setMTL(pinky_mtl);
    inky.setMTL(inky_mtl);
    clyde.setMTL(clyde_mtl);
    blinky.speedUp();
    pinky.speedUp();
    inky.speedUp();
    clyde.speedUp();
    pacman.speedUp();
    pacman.setMTL(pacman_mtl);
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

    if (!currStageClear && !allStageClear && checkClear(maps[stage_num])) {  // dot이 다 사라졌는지 확인
        if (stage_num < 2) {
            currStageClear = true;
        }
        else {
            allStageClear = true;
        }
        STOPFLAG = true;
        stageClear_sTime = eTime;
    }

    // 현재 스테이지 클리어시 동작
    if (currStageClear && eTime - stageClear_sTime > stageClear_Time1)
        drawGhost = false;

    if (currStageClear && eTime - stageClear_sTime > stageClear_Time1 + stageClear_Time2)
    {
        drawPacman = false;
        drawSurroundings = false;
    }

    if (currStageClear && eTime - stageClear_sTime > stageClear_Time1 + stageClear_Time2 + stageClear_Time3) {
        stage_num++;
        currStageClear = false;
        drawGhost = true;
        drawPacman = true;
        drawSurroundings = true;
        // STOPFLAG를 풀지 않고 stageReady상태로 진입
        stageReady = true;
        stageReady_sTime = eTime;

        // pacman, ghost들 모두 각각 처음 위치로.
        pacman.setCenter(0.0f, 0.0f, 0.0f);
        pacman.setIndexPosition(14, 14);
        blinky.setCenter(-260.0f, 240.0f, 0.0f);
        blinky.setIndexPosition(1, 2);
        pinky.setCenter(-260.0f, -240.0f, 0.0f);
        pinky.setIndexPosition(1, 27);
        inky.setCenter(240.0f, -240.0f, 0.0f);
        inky.setIndexPosition(26, 27);
        clyde.setCenter(240.0f, 240.0f, 0.0f);
        clyde.setIndexPosition(26, 2);
        // 리스폰 시 시작 위치가 어긋나는 버그 -> currdir, nextdir를 NONE으로 설정
        blinky.setCurrentDirection(Sphere::NONE);
        pinky.setCurrentDirection(Sphere::NONE);
        inky.setCurrentDirection(Sphere::NONE);
        clyde.setCurrentDirection(Sphere::NONE);
        pacman.setCurrentDirection(Sphere::NONE);
        blinky.setNextDirection(Sphere::NONE);
        pinky.setNextDirection(Sphere::NONE);
        inky.setNextDirection(Sphere::NONE);
        clyde.setNextDirection(Sphere::NONE);
        pacman.setNextDirection(Sphere::NONE);
        // 리스폰시 state를 모두 normal로
        blinky.setState(ghost_state);
        pinky.setState(ghost_state);
        inky.setState(ghost_state);
        clyde.setState(ghost_state);
        blinky.setMTL(blinky_mtl);
        pinky.setMTL(pinky_mtl);
        inky.setMTL(inky_mtl);
        clyde.setMTL(clyde_mtl);
        blinky.speedUp();
        pinky.speedUp();
        inky.speedUp();
        clyde.speedUp();
        pacman.speedUp();
        pacman.setMTL(pacman_mtl);
        FRIGHTENED = false;
        BLINK = false;
        pBLINK = false;
        eatGhost = false;

        deleteItem(maps[stage_num]);
        createItem(maps[stage_num]);
    }

    // 모든 스테이지 클리어시 동작
    if (allStageClear && eTime - stageClear_sTime > stageClear_Time1)
        drawGhost = false;

    if (allStageClear && eTime - stageClear_sTime > stageClear_Time1 + stageClear_Time2)
    {
        drawPacman = false;
        drawSurroundings = false;
    }

    if (allStageClear && eTime - stageClear_sTime > stageClear_Time1 + stageClear_Time2 + stageClear_Time3) {
        stage_num = 0;
        allStageClear = false;
        STOPFLAG = false;
        drawGhost = true;
        drawPacman = true;
        drawSurroundings = true;
        windowState = SAVE_SCORE;
        ingameInit();
    }

    // 스테이지 실패시 동작
    if (stageFail && eTime - stageFail_sTime > stageFail_Time1)
        drawPacman = false;

    if (stageFail && eTime - stageFail_sTime > stageFail_Time1 + stageFail_Time2) {
        drawGhost = false;
        drawSurroundings = false;
    }

    if (stageFail && eTime - stageFail_sTime > stageFail_Time1 + stageFail_Time2 + stageFail_Time3) {
        stage_num = 0;
        STOPFLAG = false;
        stageFail = false;
        drawPacman = true;
        drawGhost = true;
        drawSurroundings = true;
        windowState = SAVE_SCORE;
        ingameInit();
    }

    // respone시 동작
    if (respone && eTime - respone_sTime > respone_Time1) {
        drawPacman = false;
        drawGhost = false;
    }

    if (respone && eTime - respone_sTime > respone_Time1 + respone_Time2) {
        pacman.decreaseLife();
        // pacman, ghost들 모두 각각 처음 위치로.
        pacman.setCenter(0.0f, 0.0f, 0.0f);
        pacman.setIndexPosition(14, 14);
        blinky.setCenter(-260.0f, 240.0f, 0.0f);
        blinky.setIndexPosition(1, 2);
        pinky.setCenter(-260.0f, -240.0f, 0.0f);
        pinky.setIndexPosition(1, 27);
        inky.setCenter(240.0f, -240.0f, 0.0f);
        inky.setIndexPosition(26, 27);
        clyde.setCenter(240.0f, 240.0f, 0.0f);
        clyde.setIndexPosition(26, 2);
        // 리스폰 시 시작 위치가 어긋나는 버그 -> currdir, nextdir를 NONE으로 설정
        blinky.setCurrentDirection(Sphere::NONE);
        pinky.setCurrentDirection(Sphere::NONE);
        inky.setCurrentDirection(Sphere::NONE);
        clyde.setCurrentDirection(Sphere::NONE);
        pacman.setCurrentDirection(Sphere::NONE);
        blinky.setNextDirection(Sphere::NONE);
        pinky.setNextDirection(Sphere::NONE);
        inky.setNextDirection(Sphere::NONE);
        clyde.setNextDirection(Sphere::NONE);
        pacman.setNextDirection(Sphere::NONE);
        // 리스폰시 state를 모두 normal로
        blinky.setState(ghost_state);
        pinky.setState(ghost_state);
        inky.setState(ghost_state);
        clyde.setState(ghost_state);
        blinky.setMTL(blinky_mtl);
        pinky.setMTL(pinky_mtl);
        inky.setMTL(inky_mtl);
        clyde.setMTL(clyde_mtl);
        blinky.speedUp();
        pinky.speedUp();
        inky.speedUp();
        clyde.speedUp();
        pacman.speedUp();
        pacman.setMTL(pacman_mtl);

        deleteItem(maps[stage_num]);
        createItem(maps[stage_num]);

        FRIGHTENED = false;
        BLINK = false;
        pBLINK = false;
        eatGhost = false;

        respone = false;
        drawPacman = true;
        drawGhost = true;
        // STOPFLAG를 풀지 않고 ready로 진입
        stageReady = true;
        stageReady_sTime = glutGet(GLUT_ELAPSED_TIME);
    }
    // 스테이지 시작 시 ready 출력
    if (stageReady && eTime - stageReady_sTime > stageReady_Time) {
        stageReady = false;
        STOPFLAG = false;
    }

    // item 획득시 동작
    if (getItem && eTime - getItem_sTime > getItem_Time) {
        if (!currStageClear && !allStageClear && !stageFail && !stageReady && !respone && !eatGhost)
            STOPFLAG = false;
        getItem = false;
    }

    // ghost eat 동작
    if (eatGhost && eTime - eatGhost_sTime > eatGhost_Time) {
        if (!currStageClear && !allStageClear && !stageFail && !stageReady && !respone && !getItem)
            STOPFLAG = false;
        eatGhost = false;
    }

    // ghost ai
    if (!STOPFLAG && eTime - sTime > spf) {
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
        // for debugging
        std::cout << "Blinky: " << blinky.stateToString() << " Pinky: " << pinky.stateToString()
            << " Inky: " << inky.stateToString() << " Clyde: " << clyde.stateToString() << std::endl;
    }
    
    if (!STOPFLAG && eTime - chase_scatter_sTime > CHASE_SCATTER_TIME)
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

    if (!STOPFLAG && FRIGHTENED && eTime - frightened_sTime > FRIGHTENED_TIME - FRIGHTENED_NORMAL_TIME && !BLINK) {
        // ghost 점멸 상태 진입
        BLINK = true;
        blink_sTime = glutGet(GLUT_ELAPSED_TIME);
    }

    if (!STOPFLAG && BLINK && eTime - blink_sTime > BLINK_TIME) {
        // ghost 점멸
        if (blinky.getState() == Ghost::FRIGHTENED) {
            if (blinky.getMTL() == frightened_mtl)
                blinky.setMTL(frightened_blink_mtl);
            else
                blinky.setMTL(frightened_mtl);
        }
        if (pinky.getState() == Ghost::FRIGHTENED) {
            if (pinky.getMTL() == frightened_mtl)
                pinky.setMTL(frightened_blink_mtl);
            else
                pinky.setMTL(frightened_mtl);
        }
        if (inky.getState() == Ghost::FRIGHTENED) {
            if (inky.getMTL() == frightened_mtl)
                inky.setMTL(frightened_blink_mtl);
            else
                inky.setMTL(frightened_mtl);
        }
        if (clyde.getState() == Ghost::FRIGHTENED) {
            if (clyde.getMTL() == frightened_mtl)
                clyde.setMTL(frightened_blink_mtl);
            else
                clyde.setMTL(frightened_mtl);
        }
        blink_sTime = eTime;
    }

    if (!STOPFLAG && FRIGHTENED && eTime - frightened_sTime > FRIGHTENED_TIME) {
        // frightened state 종료
        FRIGHTENED = false;
        BLINK = false;
        if (blinky.getState() == Ghost::FRIGHTENED) {
            blinky.setState(ghost_state);
            blinky.setMTL(blinky_mtl);
            blinky.speedUp();
        }
        if (pinky.getState() == Ghost::FRIGHTENED) {
            pinky.setState(ghost_state);
            pinky.setMTL(pinky_mtl);
            pinky.speedUp();
        }
        if (inky.getState() == Ghost::FRIGHTENED) {
            inky.setState(ghost_state);
            inky.setMTL(inky_mtl);
            inky.speedUp();
        }
        if (clyde.getState() == Ghost::FRIGHTENED) {
            clyde.setState(ghost_state);
            clyde.setMTL(clyde_mtl);
            clyde.speedUp();
        }  
    }

    glutPostRedisplay();

    if (!STOPFLAG && pBLINK) {
        // pBLINK가 true이면 처음으로 pblink_sTime 설정
        if (pblink_sTime == 0) {
            pblink_sTime = glutGet(GLUT_ELAPSED_TIME); // 시작 시간 기록
        }

        // 현재 시간 가져오기
        float currentTime = glutGet(GLUT_ELAPSED_TIME);

        // 깜박이는 상태 유지: 일정 시간 간격으로 material 교체
        if (int(currentTime - pblink_sTime) % int(BLINK_TIME) < (BLINK_TIME / 2)) {
            pacman.setMTL(frightened_blink_mtl); // 깜박임 material 적용
            pacman.speedDouble();
        }
        else {
            pacman.setMTL(pacman_mtl); // 원래 material 적용
            pacman.speedUp();
        }

        // 총 BLINK_TIME이 지나면 pBLINK 종료
        if (currentTime - pblink_sTime > PACMAN_BLINK_TIME) {
            pBLINK = false;
            pblink_sTime = 0; // 초기화
            pacman.setMTL(pacman_mtl); // material 복구
            pacman.speedUp();
        }
        chase_scatter_sTime = eTime;
    }
}

void idle_end()
{
	// TO DO
    glutPostRedisplay();
}

void idle_savescore()
{
	// TO DO
    glutPostRedisplay();
}

void idle_scoreboard()
{
	// TO DO
    glutPostRedisplay();
}
