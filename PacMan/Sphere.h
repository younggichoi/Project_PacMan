//
//  Sphere.h
//  PacMan
//
//  Created by 이현우 on 10/31/24.
//
#pragma once

#include "Shape3D.h"
#include "Constants.h"

class Sphere : public Shape3D {
public:
    enum DIRECTION { NONE, LEFT, UP, RIGHT, DOWN };
    
    Sphere(float r, int sl, int st);
    
    void setRadius(float r);
    float getRadius() const;
    void setSlice(int sl);
    void setStack(int st);
    
    void setIndexPosition(int x, int y);
    bool isIndexPositionUpdated() const;
    int getXIndex() const;
    int getYIndex() const;
    
    void setCurrentDirection(DIRECTION d);
    void setNextDirection(DIRECTION d);
    DIRECTION getCurrentDirection() const;
    DIRECTION getNextDirection() const;
    void updateDirection();
    
    void move();
    virtual void draw() const{
        
    };
    
private:
    float radius;
    int slice, stack;
    int idxPos[2];
    bool bInxPosUpdated;
    DIRECTION currDirection, nextDirection;
};
