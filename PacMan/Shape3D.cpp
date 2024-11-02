//
//  Shape3D.cpp
//  PacMan
//
//  Created by 이현우 on 10/31/24.
//

#include "Shape3D.h"


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

//나중에 ghost, pacman 모양 꾸밀 때 활용할만한 내용은 주석처리 해뒀음
/*
 enum SHAPE {
SPHERE, CUBE, TEAPOT, CONE, TORUS, DODECAHEDRON, ICOSAHEDRON, OCTAHEDRON, TETRAHEDRON,
RHOMBIC_DODECAHEDRON, SIERPINSKI_SPONGE, CYLINDER, TEACUP, TEASPOON
};
*/

/*
void Shape3D::setShape(SHAPE shp){
    this->shape = shp;
}
 */
/*
void Shape3D::setPos(float x, float y, float z){
    this->pos[0] = x; this->pos[1] = y; this->pos[2] = z;
}
void Shape3D::setAngleOfSpin(float ang){
    this->angleOfSpin = ang;
}
void Shape3D::setAngleOfRevolution(float ang){
    this->angleOfRevolution = ang;
}
void Shape3D::setSize(float s){
    this->size = s;
}
void Shape3D::increaseAngleOfSpin(float ang){
    this->angleOfSpin += ang;
}
void Shape3D::increaseAngleOfvolution(float ang){
    this->angleOfRevolution += ang;
}
 */
