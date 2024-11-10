//
//  Sphere.h
//  Mission10
//
//  Created by 이현우 on 11/3/24.
//

#pragma once

#include "Shape3D.h"
#include "Constants.h"
#include <iostream>

using namespace std;


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
    void updateIndexPosition();
    
    void move();
    virtual void draw() const{
        GLfloat sh = mtl.getShininess();
        glPushMatrix();
        glTranslatef(center[0], center[1], center[2]);
        glShadeModel(GL_SMOOTH);
        glMaterialfv(GL_FRONT, GL_EMISSION, mtl.getEmission().pos);
        glMaterialfv(GL_FRONT, GL_AMBIENT, mtl.getAmbient().pos);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mtl.getDiffuse().pos);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mtl.getSpecular().pos);
        glMaterialfv(GL_FRONT, GL_SHININESS, &sh);
        glutSolidSphere(radius, slice, stack);
        glPopMatrix();
    }
    
protected:
    float radius;
    int slice, stack;
    int idxPos[2];
    bool bInxPosUpdated;
    DIRECTION currDirection, nextDirection;
};

/* Pacman class */
class PacMan : public Sphere
{
public:
    PacMan(float r, int sl, int st, bool bCol);

    void setCollided(bool bCol);

    virtual void draw() const{
        GLfloat sh = mtl.getShininess();
        glPushMatrix();
        glTranslatef(center[0], center[1], center[2]);
        glShadeModel(GL_SMOOTH);
        glMaterialfv(GL_FRONT, GL_EMISSION, mtl.getEmission().pos);
        glMaterialfv(GL_FRONT, GL_AMBIENT, mtl.getAmbient().pos);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mtl.getDiffuse().pos);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mtl.getSpecular().pos);
        glMaterialfv(GL_FRONT, GL_SHININESS, &sh);
        glutSolidSphere(radius, slice, stack);
        glPopMatrix();
    }

private:
    bool bCollided;
};

/* Ghost class */
class Ghost : public Sphere
{
public:
    enum STATE { CHASE, SCATTER };

    Ghost(float r, int sl, int st, STATE s);

    void setState(STATE s);
    STATE getState() const;

private:
    STATE state;
};
