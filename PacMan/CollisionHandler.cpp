//
//  CollisionHandler.cpp
//  Mission11
//
//  Created by 이현우 on 11/3/24.
//

#include "CollisionHandler.h"
extern Ghost blinky, pinky, inky, clyde;

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
            pacman.addScore(100);
        }
        else {
            if (ghost.getState() != Ghost::EATEN) {
                pacman.decreaseLife();
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
            }
            if (pinky.getState() != Ghost::EATEN) {
                pinky.setState(Ghost::FRIGHTENED);
            }
            if (inky.getState() != Ghost::EATEN) {
                inky.setState(Ghost::FRIGHTENED);
            }
            if (clyde.getState() != Ghost::EATEN) {
                clyde.setState(Ghost::FRIGHTENED);
            }
            // ghost들 전역변수로 선언하고 constants.h에 넣은 후에 아래 주석표시 풀기
            /*
            if (ghost.getState() != Ghost::EATEN) {
                ghost.setState(Ghost::FRIGHTENED);
            }
            */
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