//
//  Shape3D.h
//  Mission10
//
//  Created by 이현우 on 11/3/24.
//

#pragma once
#include "Vector3f.h"
#include "Material.h"
#include "Constants.h"
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>


class Shape3D{
public:
    Shape3D();
    Shape3D(float x, float y, float z);
    
    void setCenter(float x, float y, float z);
    void setCenter(const Vector3f& c);
    Vector3f getCenter() const;
    
    void setVelocity(float x, float y, float z);
    void setVelocity(const Vector3f& v);
    Vector3f getVelocity() const;
    
    void setMTL(const Material& m);
    const Material& getMTL() const;
    
    void move();
    
    virtual void draw() const = 0;
    
protected:
    Vector3f center;
    Vector3f velocity;
    Material mtl;

};
