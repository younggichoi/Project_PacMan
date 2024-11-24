//
//  Block.cpp
//  Mission10
//
//  Created by 이현우 on 11/3/24.
//

#include "Block.h"

Block::Block(){
    setWidth(0.0f);
    setHeight(0.0f);
    setPassable(false);
};

void Block::setWidth(float w){
    width = w;
}
void Block::setHeight(float h){
    height = h;
}

void Block::setPassable(bool v){
    bPassable = v;
}

void Block::setColor(float r, float g, float b) {
    color = Vector3f(r, g, b);
}

void Block::setColor(Vector3f& v) {
    color = v;
}


float Block::getWidth() const{
    return width;
}
float Block::getHeight() const{
    return height;
}

bool Block::isPassable() const{
    return bPassable;
}

