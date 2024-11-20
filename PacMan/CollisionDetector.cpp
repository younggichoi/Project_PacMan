//
//  CollisionDetector.cpp
//  Mission11
//
//  Created by 이현우 on 11/3/24.
//

#include "CollisionDetector.h"


bool CollisionDetector::operator()(const PacMan& pacman, const Map& map){
    //if (map.getBlock(sphere.getXIndex()-1, sphere.getYIndex()).isPassable())
    
    switch (pacman.getCurrentDirection()){
        case Sphere::LEFT:
            if (!map.getBlock(pacman.getXIndex()-1, pacman.getYIndex()).isPassable()){
                return true;
            }
            else return false;
            break;
        case Sphere::RIGHT:
            if (!map.getBlock(pacman.getXIndex()+1, pacman.getYIndex()).isPassable()){
                return true;
            }
            else return false;
            break;
        case Sphere::UP:
            if (!map.getBlock(pacman.getXIndex(), pacman.getYIndex()-1).isPassable()){
                return true;
            }
            else return false;
            break;
        case Sphere::DOWN:
            if (!map.getBlock(pacman.getXIndex(), pacman.getYIndex()+1).isPassable()){
                return true;
            }
            else return false;
            break;
        default:
            return false;
            break;
    }
}

bool CollisionDetector::operator()(const PacMan& pacman, const Ghost& ghost){
    if (  ( pacman.getRadius() + ghost.getRadius() ) >= sqrt(pow(pacman.getCenter()[0] - ghost.getCenter()[0],2) + pow(pacman.getCenter()[1] - ghost.getCenter()[1], 2))) {
        if (ghost.getState() == Ghost::EATEN) {
            return false;
        }
        else {
            return true;
        }
    }
    else return false;
}

bool CollisionDetector::operator()(const PacMan& pacman, const Dot& dot) {
    if ( (pacman.getRadius() + dot.getRadius()) < (pacman.getCenter() - dot.getCenter()).getAbs()) {
        // if 반지름 합 < 둘 사이 거리
        // not yet
        return false;
    }
    else {
        return true;
    }
}
bool CollisionDetector::operator()(const Ghost& ghost, const Map& map) {
    switch (ghost.getCurrentDirection()) {
    case Sphere::LEFT:
        if (!map.getBlock(ghost.getXIndex() - 1, ghost.getYIndex()).isPassable()) {
            return true;
        }
        else return false;
        break;
    case Sphere::RIGHT:
        if (!map.getBlock(ghost.getXIndex() + 1, ghost.getYIndex()).isPassable()) {
            return true;
        }
        else return false;
        break;
    case Sphere::UP:
        if (!map.getBlock(ghost.getXIndex(), ghost.getYIndex() - 1).isPassable()) {
            return true;
        }
        else return false;
        break;
    case Sphere::DOWN:
        if (!map.getBlock(ghost.getXIndex(), ghost.getYIndex() + 1).isPassable()) {
            return true;
        }
        else return false;
        break;
    default:
        return false;
        break;
    }
}