//
//  Block.h
//  Mission10
//
//  Created by 이현우 on 11/3/24.
//

#pragma once

#include "Shape3D.h"
#include "Constants.h"

#include <GL/freeglut.h>


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
        // /*
        if (!isPassable()){
            GLfloat sh = mtl.getShininess();
            glPushMatrix();
            glColor3f(0.0f, 0.0f, 1.0f);
            glTranslatef(center[0], center[1], center[2]);
            glShadeModel(GL_SMOOTH);
            glMaterialfv(GL_FRONT, GL_EMISSION, mtl.getEmission().pos);
            glMaterialfv(GL_FRONT, GL_AMBIENT, mtl.getAmbient().pos);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, mtl.getDiffuse().pos);
            glMaterialfv(GL_FRONT, GL_SPECULAR, mtl.getSpecular().pos);
            glMaterialfv(GL_FRONT, GL_SHININESS, &sh);
            glutSolidCube(BLOCK_SIZE);
            glPopMatrix();
        }
         // */
        //glPushMatrix();
        /*
        glColor3f(1.0f, 1.0f, 1.0f);
        glLineWidth(2.5f);
        glBegin(GL_LINE_LOOP);
            glVertex2f(getCenter()[0] -width/2, getCenter()[1] +width/2);
            glVertex2f(getCenter()[0] -width/2, getCenter()[1] -width/2);
            glVertex2f(getCenter()[0] + width/2, getCenter()[1] -width/2);
            glVertex2f(getCenter()[0] + width/2, getCenter()[1] +width/2);
        glEnd();
         */
        //glPopMatrix();
         
    };
    
private:
    float width, height;
    bool bPassable;
};
