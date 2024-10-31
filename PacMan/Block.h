//
//  Block.h
//  PacMan
//
//  Created by 이현우 on 10/31/24.
//
#pragma once

#include "Shape3D.h"

class Block : public Shape3D {
public:
    Block();
    Block(float x, float y, float z, float w, float h) : width(w), height(h) {
        this->setCenter(x,y,z);
    };
    void setWidth(float w);
    void setHeight(float h);
    float getWidth() const;
    float getHeight() const;
    virtual void draw() const;
    
private:
    float width, height;
};
