//
//  CollisionHandler.cpp
//  Mission11
//
//  Created by 이현우 on 11/3/24.
//

#include "CollisionHandler.h"

// from main.cpp
extern Ghost blinky, pinky, inky, clyde;

// from idle.cpp
extern float frightened_sTime;
extern  bool FRIGHTENED;
extern Material pacman_mtl;
extern Material frightened_mtl;
extern Material frightened_blink_mtl;
extern bool pBLINK;
extern bool BLINK;

Material eaten_mtl;

void CollisionHandler::operator()(PacMan& pacman, Map& map){
    CollisionDetector cd;
    if (cd(pacman, map)){
        pacman.setCurrentDirection(Sphere::NONE);
        pacman.setNextDirection(Sphere::NONE);
    }
}
void CollisionHandler::operator()(PacMan& pacman, Ghost& ghost){

    // 만난 ghost가 frightened 상태라면 ghost->eaten, ghostroom으로, 점수 올리기
    // else: life 줄이고 pacman, ghost들 처음 위치로.
    CollisionDetector cd;
    if (cd(pacman, ghost)) {
        if (ghost.getState() == Ghost::FRIGHTENED) {
            ghost.setState(Ghost::EATEN);
            ghost.setMTL(eaten_mtl);
            ghost.speedUp();
            ghost.speedDouble();
            pacman.addScore(100);
            STOPFLAG = true;
            eatGhost = true;
            eatGhost_sTime = glutGet(GLUT_ELAPSED_TIME);
        }
        else {
            if (ghost.getState() != Ghost::EATEN) {
                STOPFLAG = true;
                if (!pBLINK && pacman.getLife() != 1) {
                    respone = true;
                    respone_sTime = glutGet(GLUT_ELAPSED_TIME);
                }
                else if (!pBLINK) {
                    stageFail = true;
                    stageFail_sTime = glutGet(GLUT_ELAPSED_TIME);
                }
                else {
                    ghost.setState(Ghost::EATEN);
                    ghost.setMTL(eaten_mtl);
                    ghost.speedUp();
                    ghost.speedDouble();
                    pacman.addScore(100);
                    eatGhost = true;
                    eatGhost_sTime = glutGet(GLUT_ELAPSED_TIME);
                }
            }
            

        }
    }
}
void CollisionHandler::operator()(PacMan& pacman, Dot& dot) {
    //TODO
    // dot 지우기
    CollisionDetector cd;
    if (cd(pacman, dot)) {
        // Item은 아니고 그냥 large/small dot인 경우
        if (dot.getSize() < 6) {
            dot.setEaten(true);
            if (dot.isLarge()) {
                // 큰 dot 먹은 경우 ghost들 상태 frightened로 바꾸기 (eaten이 아니라면.)
                if (blinky.getState() != Ghost::EATEN) {
                    blinky.setState(Ghost::FRIGHTENED);
                    blinky.setMTL(frightened_mtl);
                    blinky.slowDown();
                }
                if (pinky.getState() != Ghost::EATEN) {
                    pinky.setState(Ghost::FRIGHTENED);
                    pinky.setMTL(frightened_mtl);
                    pinky.slowDown();
                }
                if (inky.getState() != Ghost::EATEN) {
                    inky.setState(Ghost::FRIGHTENED);
                    inky.setMTL(frightened_mtl);
                    inky.slowDown();
                }
                if (clyde.getState() != Ghost::EATEN) {
                    clyde.setState(Ghost::FRIGHTENED);
                    clyde.setMTL(frightened_mtl);
                    clyde.slowDown();
                }
                frightened_sTime = glutGet(GLUT_ELAPSED_TIME);
                FRIGHTENED = true;
                BLINK = false;
                STOPFLAG = true;
                getItem = true;
                getItem_sTime = glutGet(GLUT_ELAPSED_TIME);
            }
            // 점수올리기
            pacman.addScore(10);
        }
        else {
            dot.setEaten(true);
            STOPFLAG = true;
            getItem = true;
            getItem_sTime = glutGet(GLUT_ELAPSED_TIME);
            if (dot.getSize() == Dot::DOTSIZE::ITEM1) {
                // pacman 블링킹, 스피드업, ghost와 collide시 ghost gets eaten
                pBLINK = true;
            }
            else if(dot.getSize() == Dot::DOTSIZE::ITEM2){
                // 점수 추가 + 이펙트
                pacman.addScore(100);
            }
            else if (dot.getSize() == Dot::DOTSIZE::ITEM3) {
                // 라이프 추가 + 이펙트
                pacman.increaseLife();
            }
        }
    }
}
void CollisionHandler::operator()(Ghost& ghost, Map& map) {
    CollisionDetector cd;
    if (cd(ghost, map)) {
        ghost.setCurrentDirection(Sphere::NONE);
        ghost.setNextDirection(Sphere::NONE);
    }
}
