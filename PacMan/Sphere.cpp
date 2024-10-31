//
//  Sphere.cpp
//  PacMan
//
//  Created by 이현우 on 11/1/24.
//

#include "Sphere.h"

void Sphere::setRadius(float r){
    radius = r;
}
float Sphere::getRadius() const{
    return radius;
}
void Sphere::setSlice(int sl){
    slice = sl;
}
void Sphere::setStack(int st){
    stack = st;
}
void Sphere::setIndexPosition(int x, int y){
    idxPos[0] = x; idxPos[1] = y;
    //bInxPosUpdated = true;
    //언제 다시 false로 만들 건지 나중에 생각
}
bool Sphere::isIndexPositionUpdated() const{
    return bInxPosUpdated;
}
int Sphere::getXIndex() const{
    return idxPos[0];
}
int Sphere::getYIndex() const{
    return idxPos[1];
}
void Sphere::setCurrentDirection(DIRECTION d){
    currDirection = d;
}
void Sphere::setNextDirection(DIRECTION d){
    nextDirection = d;
}
DIRECTION Sphere::getCurrentDirection() const{
    return currDirection;
}
DIRECTION Sphere::getNextDirection() const{
    return nextDirection;
}
void Sphere::updateDirection(){
    currDirection = nextDirection;
}
void Sphere::move(){
    if(DIRECTION == )
}

