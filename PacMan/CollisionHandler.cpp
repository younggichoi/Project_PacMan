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
    //TODO
}
void CollisionHandler::operator()(PacMan& pacman, Dot& dot) {
    //TODO
    if (dot.isLarge()) {
        // 큰 dot 먹은 경우 ghost들 상태 바꾸기

    }
    else {
        // 작은 dot 먹은 경우 점수올리기?

    }
}