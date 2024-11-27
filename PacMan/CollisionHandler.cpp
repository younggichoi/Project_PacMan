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
extern Material frightened_mtl;

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
            pacman.addScore(100);
        }
        else {
            if (ghost.getState() != Ghost::EATEN) {
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
                // 리스폰 시 시작 위치가 어긋나는 버그 -> currdir를 NONE으로 설정
                blinky.setCurrentDirection(Sphere::NONE);
                pinky.setCurrentDirection(Sphere::NONE);
                inky.setCurrentDirection(Sphere::NONE);
                clyde.setCurrentDirection(Sphere::NONE);
                pacman.setCurrentDirection(Sphere::NONE);
            }
            // pacman, ghost들 모두 각각 처음 위치로.
            // TODO

        }
    }
}
void CollisionHandler::operator()(PacMan& pacman, Dot& dot) {
    //TODO
    // dot 지우기
    CollisionDetector cd;
    if (cd(pacman, dot)) {
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
        }
        // 점수올리기
        pacman.addScore(10);
    }
}
void CollisionHandler::operator()(Ghost& ghost, Map& map) {
    CollisionDetector cd;
    if (cd(ghost, map)) {
        ghost.setCurrentDirection(Sphere::NONE);
        ghost.setNextDirection(Sphere::NONE);
    }
}
