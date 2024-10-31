//
//  Block.cpp
//  PacMan
//
//  Created by 이현우 on 10/31/24.
//
#include "Block.h"
//MacOS
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
//Windows
//#include <GL/freeglut.h>

void Block::setWidth(float w){
    width = w;
}
void Block::setHeight(float h){
    height = h;
}
float Block::getWidth() const{
    return width;
}
float Block::getHeight() const{
    return height;
}
