//
//  Sphere.cpp
//  Mission10
//
//  Created by 이현우 on 11/3/24.
//

#include "Sphere.h"


Sphere::Sphere()
    : radius(0), slice(10), stack(10), currDirection(NONE) {};

Sphere::Sphere(float r, int sl, int st){
    radius = r; slice = sl; stack = st;
    center[0] = 0.0f; center[1] = 0.0f; center[2] = 0.0f;
    currDirection = NONE;
}

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
Sphere::DIRECTION Sphere::getCurrentDirection() const{
    return currDirection;
}
Sphere::DIRECTION Sphere::getNextDirection() const{
    return nextDirection;
}

void Sphere::updateDirection(){
        currDirection = nextDirection;
}

void Sphere::updateIndexPosition(){
    float xFromIdx = LEFT_BOUNDARY + idxPos[0] * BLOCK_SIZE;
    float yFromIdx = TOP_BOUNDARY  - idxPos[1] * BLOCK_SIZE;
    if (velocity[0] > 0.0f){
        if (center[0] - radius * 2.0f >= xFromIdx) {
            if (idxPos[0] < NUM_COL - 1)
                setIndexPosition(idxPos[0] + 1, idxPos[1]);
            else {
                setIndexPosition(0, idxPos[1]);
                this->setCenter(LEFT_BOUNDARY + idxPos[0] * BLOCK_SIZE, yFromIdx, 0.0f);
                cout << xFromIdx << endl;
            }
            bInxPosUpdated = true;
        }
        else {
            bInxPosUpdated = false;
        }
    }
    else if (velocity[0] < 0.0f){
        if (center[0] + radius * 2.0f <= xFromIdx) {
            if (idxPos[0] > 0)
                setIndexPosition(idxPos[0] - 1, idxPos[1]);
            else {
                setIndexPosition(NUM_COL - 1, idxPos[1]);
                this->setCenter(LEFT_BOUNDARY + idxPos[0] * BLOCK_SIZE, yFromIdx, 0.0f);
            }
            bInxPosUpdated = true;
        }
        else {
            bInxPosUpdated = false;
        }
    }
    else if (velocity[1] > 0.0f){
        if (center[1] - radius * 2.0f >= yFromIdx) {
            if (idxPos[1] > 0)
                setIndexPosition(idxPos[0], idxPos[1] - 1);
            else {
                setIndexPosition(idxPos[0], NUM_ROW - 1);
                this->setCenter(xFromIdx, TOP_BOUNDARY  - idxPos[1] * BLOCK_SIZE, 0.0f);
            }
            bInxPosUpdated = true;
        }
        else {
            bInxPosUpdated = false;
        }
    }
    else if (velocity[1] < 0.0f){
        if (center[1] + radius * 2.0f <= yFromIdx) {
            if (idxPos[1] < NUM_ROW - 1)
                setIndexPosition(idxPos[0], idxPos[1] + 1);
            else {
                setIndexPosition(idxPos[0], 0);
                this->setCenter(xFromIdx, TOP_BOUNDARY  - idxPos[1] * BLOCK_SIZE, 0.0f);
            }
            bInxPosUpdated = true;
        }
        else {
            bInxPosUpdated = false;
        }
    }
    else {
        bInxPosUpdated = false;
    }
}

void Sphere::move(){
    
    updateIndexPosition();
    
    if (currDirection == LEFT){
        this->setVelocity(-MOVE_SPEED, 0.0f, 0.0f);
    }
    else if (currDirection == RIGHT){
        this->setVelocity(MOVE_SPEED, 0.0f, 0.0f);
    }
    else if (currDirection == UP){
        this->setVelocity(0.0f, MOVE_SPEED, 0.0f);
    }
    else if (currDirection == DOWN){
        this->setVelocity(0.0f, -MOVE_SPEED, 0.0f);
    }
    else{
        this->setVelocity(0.0f, 0.0f, 0.0f);
    }
    
    center = center + velocity;
    
    //updateIndexPosition();
    //cout << "[" << this->getXIndex() << ", " << this->getYIndex() << "]"  << " (" << xFromIdx << ", " << yFromIdx << ")" << endl;
}

//******************************************************//
// PacMan
//******************************************************//

PacMan::PacMan(float r, int sl, int st, bool bCol) : Sphere(r, sl, st){
    bCollided = bCol;
    life = 3;
    idxPos[0] = 14;
    idxPos[1] = 14;
}
void PacMan::setCollided(bool bCol){
    bCollided = bCol;
}
void PacMan::setLife(int l) {
    life = l;
}
void PacMan::decreaseLife() {
    life -= 1;
}
int PacMan::getLife() {
    return life;
}
void PacMan::addScore(int sc) {
    score += sc;
}
int PacMan::getScore() {
    return score;
}

void PacMan::initialize()
{
    bCollided = false;
    score = 0;
    life = INIT_LIFE;
}


//******************************************************//
// Ghost
//******************************************************//

Ghost::Ghost(float r, int sl, int st, NAME n, STATE s) : Sphere(r, sl, st){
    name = n;
    state = s;
    isEaten = false;
    // TODO : 이름 별 초기위치 세팅
    if (name == Ghost::BLINKY) {
        center[0] = -260.0f; center[1] = 240.0f; center[2] = 0.0f; idxPos[0] = 1; idxPos[1] = 2;
    }
    else if (name == Ghost::PINKY) {
        center[0] = -260.0f; center[1] = -240.0f; center[2] = 0.0f; idxPos[0] = 1; idxPos[1] = 27;
    }
    else if (name == Ghost::INKY) {
        center[0] = 240.0f; center[1] = -240.0f; center[2] = 0.0f; idxPos[0] = 26; idxPos[1] = 27;
    }
    else if (name == Ghost::CLYDE) {
        center[0] = 240.0f; center[1] = 240.0f; center[2] = 0.0f; idxPos[0] = 26; idxPos[1] = 2;
    }
}
void Ghost::setName(NAME n) {
    name = n;
}
Ghost::NAME Ghost::getName() const {
    return name;
}
void Ghost::setState(STATE s){
    state = s;
}
Ghost::STATE Ghost::getState() const{
    return state;
}
void Ghost::setTargetPosition(int x, int y) {
    targetPos[0] = x; targetPos[1] = y;
}
bool Ghost::getEaten() {
    return isEaten;
}
void Ghost::setEaten(bool v) {
    isEaten = v;
}

//******************************************************//
// Dot
//******************************************************//

Dot::Dot()
    : dotSize(SMALL), isEaten(false) {
    radius = PACMAN_RADIUS / dotSize;
};

Dot::Dot(float r, int sl, int st, DOTSIZE ds) : Sphere(r, sl, st){
    dotSize = ds;
    isEaten = false;
}

void Dot::setEaten(bool iE){
    isEaten = iE;
}

void Dot::setDotsize(DOTSIZE ds)
{
    dotSize = ds;
    radius = PACMAN_RADIUS / dotSize;
}

bool Dot::isLarge() const{
    if (dotSize == LARGE) {
        return true;
    }
    else {
        return false;
    }
}

bool Dot::getEaten() const{
    return isEaten;
}