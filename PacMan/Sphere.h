//
//  Sphere.h
//  Mission10
//
//  Created by 이현우 on 11/3/24.
//

#pragma once

#include "Shape3D.h"
#include "constant.h"
#include <iostream>
#include <string>

extern const float PACMAN_RADIUS;

using namespace std;


class Sphere : public Shape3D {
public:
    enum DIRECTION { NONE, LEFT, UP, RIGHT, DOWN };
    
    Sphere();
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

    // MOVE_SPEED->SLOW_SPEED
    void slowDown();
    // SLOW_SPEED->MOVE_SPEED
    void speedUp();
    
    void move();
    virtual void draw() const{
        GLfloat sh = mtl.getShininess();
        glPushMatrix();
        glTranslatef(center[0], center[1], center[2]);
        glColor3f(color[0], color[1], color[2]);
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
    float speed = MOVE_SPEED;
};

/* Pacman class */
class PacMan : public Sphere
{
public:
    static const int INIT_LIFE = 3;

    PacMan(float r, int sl, int st, bool bCol);

    void setCollided(bool bCol);

    void setLife(int l);
    void increaseLife();
    void decreaseLife();
    int getLife();

    void addScore(int sc);
    int getScore();
    
    void initialize();

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
    bool bCollided = false;
    int score = 0;
    int life = INIT_LIFE;
};

/* Ghost class */
class Ghost : public Sphere
{
public:
    enum NAME {BLINKY, PINKY, INKY, CLYDE};
    enum STATE { CHASE, SCATTER, FRIGHTENED, EATEN };

    Ghost(float r, int sl, int st, NAME n, STATE s);

    void setName(NAME n);
    NAME getName() const;

    void setState(STATE s);
    STATE getState() const;

    void setTargetPosition(int x, int y);

    bool getEaten();
    void setEaten(bool v);

    std::string stateToString() const;

private:
    NAME name;
    STATE state;
    int targetPos[2];
    bool isEaten;
};


/* Dots */

class Dot : public Sphere{
public:
    enum DOTSIZE { SMALL = 5, LARGE = 2, ITEM1 = 6, ITEM2, ITEM3 };
    //main에서 dot의 radius 설정해서 선언할 때 radius = (pacman radius) / dotSize 식으로 사용
    //CollisionDetector, CollisionHandler에 pacman과 dot 충돌 관련 내용 추가해야.
    
    Dot();
    Dot(float r, int sl, int st, DOTSIZE ds);
    
    void setEaten(bool iE);
    void setDotsize(DOTSIZE ds);

    bool isLarge() const;
    DOTSIZE getSize() const;
    bool getEaten() const;
    
    virtual void draw() const{
        // isEaten == false (= not eaten yet) 이면 show
        if (!isEaten) {
            glPushMatrix();
            glTranslatef(center[0], center[1], center[2]);
            glColor3f(color[0], color[1], color[2]);
            glutSolidSphere(radius, slice, stack);
            glPopMatrix();
        }
    }
    
private:
    DOTSIZE dotSize;
    bool isEaten;
};
