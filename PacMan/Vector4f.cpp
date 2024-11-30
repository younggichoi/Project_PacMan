//
//  Vector4f.cpp
//  Mission10
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

bool Vector4f::operator==(const Vector4f& v) const {
    if (pos[0] != v.pos[0]) return false;
    if (pos[1] != v.pos[1]) return false;
    if (pos[2] != v.pos[2]) return false;
    if (pos[3] != v.pos[3]) return false;
    return true;
}

bool Vector4f::operator!=(const Vector4f& v) const {
    return !(*this == v);
}