//
//  Shape3D.cpp
//  Mission10
//
//  Created by 이현우 on 11/3/24.
//

#include "Shape3D.h"

#include <GL/freeglut.h>

Shape3D::Shape3D(){
    setCenter(0.0f, 0.0f, 0.0f);
    setVelocity(0.0f, 0.0f, 0.0f);
    mtl.setEmission(0.0f, 0.0f, 0.0f, 0.0f);
    mtl.setAmbient(0.0f, 0.0f, 0.0f, 0.0f);
    mtl.setDiffuse(0.0f, 0.0f, 0.0f, 0.0f);
    mtl.setSpecular(0.0f, 0.0f, 0.0f, 0.0f);
    mtl.setShininess(0.0f);
};
Shape3D::Shape3D(float x, float y, float z){
    setCenter(x,y,z);
}
void Shape3D::setCenter(float x, float y, float z){
    center.setPos(x, y, z);
}
void Shape3D::setCenter(const Vector3f& c){
    center.setPos(c);
}
Vector3f Shape3D::getCenter() const{
    return center;
}
void Shape3D::setVelocity(float x, float y, float z){
    velocity.setPos(x, y, z);
}
void Shape3D::setVelocity(const Vector3f& v){
    velocity.setPos(v);
}
Vector3f Shape3D::getVelocity() const{
    return velocity;
}
void Shape3D::setMTL(const Material& m){
    this->mtl = m;
}
const Material& Shape3D::getMTL() const{
    return mtl;
}
void Shape3D::move() {
    center = center + velocity;
}
