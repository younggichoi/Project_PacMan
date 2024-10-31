//
//  Vector3f.cpp
//  PacMan
//
//  Created by 이현우 on 10/31/24.
//
#include "Vector3f.h"

void Vector3f::setVector(float a, float b, float c) {
    x = a; y = b; z = c;
}
void Vector3f::setVector(const Vector3f& v){
    this->x = v.x; this->y = v.y; this->z = v.z;
}
