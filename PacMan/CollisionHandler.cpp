//
//  CollisionHandler.cpp
//  Mission11
//
//  Created by 이현우 on 11/3/24.
//

#include "CollisionHandler.h"

void CollisionHandler::operator()(PacMan& pacman, const Map& map){
    CollisionDetector cd;
    if (cd(pacman, map)){
        pacman.setCurrentDirection(Sphere::NONE);
        pacman.setNextDirection(Sphere::NONE);
    }
}
void CollisionHandler::operator()(PacMan& pacman, Ghost& ghost){
    // 만난 ghost가 frightened 상태라면 ghost->eaten, ghostroom으로 
    // else: life 줄이고 pacman, ghost들 처음 위치로.
    if (ghost.getState() == Ghost::FRIGHTENED) {
        ghost.setState(Ghost::EATEN);
    }
    else {
        pacman.decreaseLife();
        // pacman, ghost들 각각 처음 위치로.
        // TODO
        
    }
}
void CollisionHandler::operator()(PacMan& pacman, Dot& dot) {
    //TODO
    // dot 지우기
    dot.setEaten(true);
    if (dot.isLarge()) {
        // 큰 dot 먹은 경우 ghost들 상태 frightened로 바꾸기 (eaten이 아니라면.)
        // ghost들 전역변수로 선언하고 constants.h에 넣은 후에 아래 주석표시 풀기
        /*
        if (ghost.getState() != Ghost::EATEN) {
            ghost.setState(Ghost::FRIGHTENED);
        }
        */
    }
    // 점수올리기
    pacman.addScore(50);
}