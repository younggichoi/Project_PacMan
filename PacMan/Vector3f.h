//
//  Vector3f.h
//  PacMan
//
//  Created by 이현우 on 10/31/24.
//
#pragma once

class Vector3f {
public:
    Vector3f() : x(0), y(0), z(0) {};
    Vector3f(float a, float b, float c) : x(a), y(b), z(c) {};
    Vector3f operator+(const Vector3f& a){
        return Vector3f(x + a.x, y + a.y, z + a.z);
    }
    void setVector(float a, float b, float c);
    void setVector(const Vector3f& v);
    
    float x, y, z;
};
