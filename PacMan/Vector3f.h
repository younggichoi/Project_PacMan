//
//  Vector3f.h
//  Mission10
//
//  Created by 이현우 on 11/3/24.
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
    Vector3f operator-(const Vector3f& v);
    float& operator[](const int i);
    float operator[](const int i) const;
    
    void setPos(float a, float b, float c);
    void setPos(const Vector3f& v);
    

    float pos[3];
};
