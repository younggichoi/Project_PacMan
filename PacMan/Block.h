//
//  Block.h
//  PacMan
//
//  Created by 이현우 on 10/31/24.
//
#pragma once

#include "Shape3D.h"

//MacOS
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
//Windows
//#include <GL/freeglut.h>

#define BLOCK_SIZE 1

class Block : public Shape3D {
public:
    Block();
    Block(float x, float y, float z, float w, float h) : width(w), height(h) {
        setCenter(x,y,z);
    };
    void setWidth(float w);
    void setHeight(float h);
    void setPassable(bool v);
    
    float getWidth() const;
    float getHeight() const;
    bool isPassable() const;
    
    virtual void draw() const{
        if(isPassable()){
            glPushMatrix();
            glTranslatef(center[0], center[1], center[2]);
            glShadeModel(GL_SMOOTH);
            glMaterialfv(GL_FRONT, GL_EMISSION, mtl.emission);
            glMaterialfv(GL_FRONT, GL_AMBIENT, mtl.ambient);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, mtl.diffuse);
            glMaterialfv(GL_FRONT, GL_SPECULAR, mtl.specular);
            glMaterialfv(GL_FRONT, GL_SHININESS, mtl.shininess);
            glutSolidCube(BLOCK_SIZE);
            glPopMatrix();
        }
    };
    
private:
    float width, height;
    bool bPassable;
};
