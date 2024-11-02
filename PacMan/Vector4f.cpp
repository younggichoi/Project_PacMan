//
//  Vector4f.cpp
//  PacMan
//
//  Created by 이현우 on 11/3/24.
//
#include "Vector4f.h"

Vector4f::Vector4f(){
    pos[0] = 0.0f; pos[1] = 0.0f; pos[2] = 0.0f; pos[3] = 0.0f;
}
Vector4f::Vector4f(float x, float y, float z, float w){
    pos[0] = x; pos[1] = y; pos[2] = z; pos[3] = w;
}
void Vector4f::setPos(float x, float y, float z, float w){
    pos[0] = x; pos[1] = y; pos[2] = z; pos[3] = w;
}

float& Vector4f::operator[](const int i){
    return pos[i];
}
float Vector4f::operator[](const int i) const{
    return pos[i];
}
