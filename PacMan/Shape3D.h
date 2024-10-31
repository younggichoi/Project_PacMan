//
//  Shape3D.h
//  PacMan
//
//  Created by 이현우 on 10/31/24.
//

/*
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
<variables: protected>
Vector3f center;
Vector3f velocity;
Material mtl;

*/
#pragma once
#include "Vector3f.h"
#include "Material.h"
/*
enum SHAPE {
    SPHERE, CUBE, TEAPOT, CONE, TORUS, DODECAHEDRON, ICOSAHEDRON, OCTAHEDRON, TETRAHEDRON,
    RHOMBIC_DODECAHEDRON, SIERPINSKI_SPONGE, CYLINDER, TEACUP, TEASPOON
};
 */
class Vector3f {
public:
    Vector3f() : x(0), y(0), z(0) {};
    Vector3f(float a, float b, float c) : x(a), y(b), z(c) {};
    Vector3f operator+(const Vector3f& a){
        return Vector3f(x + a.x, y + a.y, z + a.z);
    }
    void setVector(float a, float b, float c);
    void setVector(const Vector3f& v);
    
protected:
    float x, y, z;
};

class Shape3D{
public:
    //void setShape(SHAPE shp);
    /*
    void setPos(float x, float y, float z);
    void setAngleOfSpin(float ang);
    void setAngleOfRevolution(float ang);
    void setSize(float s);
    void increaseAngleOfSpin(float ang);
    void increaseAngleOfvolution(float ang);
    void draw() const;
     */
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
