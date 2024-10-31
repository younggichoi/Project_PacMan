//
//  Block.cpp
//  PacMan
//
//  Created by 이현우 on 10/31/24.
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

float Block::getWidth() const{
    return width;
}
float Block::getHeight() const{
    return height;
}
bool Block::isPassable() const{
    return bPassable;
}
