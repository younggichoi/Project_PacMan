//
//  Block.h
//  Mission10
//
//  Created by 이현우 on 11/3/24.
//

#pragma once

#include "Shape3D.h"
#include "constant.h"
#include "Vector3f.h"

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
    void setColor(float r, float g, float b);
    void setColor(Vector3f& v);
    
    float getWidth() const;
    float getHeight() const;
    bool isPassable() const;
    
    virtual void draw() const{
        if (!isPassable()){
            glColor3f(color[0], color[1], color[2]);
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glBegin(GL_POLYGON);
            glVertex2f(getCenter()[0] - width / 2, getCenter()[1] + height / 2);
            glVertex2f(getCenter()[0] - width / 2, getCenter()[1] - height / 2);
            glVertex2f(getCenter()[0] + width / 2, getCenter()[1] - height / 2);
            glVertex2f(getCenter()[0] + width / 2, getCenter()[1] + height / 2);
            glEnd();
        }
    };
    
private:
    float width, height;
    bool bPassable;
    Vector3f color;
};
