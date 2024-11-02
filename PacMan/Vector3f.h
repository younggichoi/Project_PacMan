//
//  Vector3f.h
//  PacMan
//
//  Created by 이현우 on 10/31/24.
//
#pragma once
#include "Constants.h"

class Vector3f {
public:
    Vector3f();
    Vector3f(float a, float b, float c);
    
    float getX() const;
    float getY() const;
    float getZ() const;
    
    Vector3f& operator=(const Vector3f& v);
    Vector3f operator+(const Vector3f& a);
    Vector3f operator*(float s) const;
    float& operator[](const int i);
    float operator[](const int i) const;
    //TODO: 아마 다른 operator들도 구현해두는게 좋을듯
    
    void setPos(float a, float b, float c);
    void setPos(const Vector3f& v);
    

    float pos[3];
};
