//
//  Shape3D.cpp
//  PacMan
//
//  Created by 이현우 on 10/31/24.
//

#include "Shape3D.h"

//MacOS
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
//Windows
//#include <GL/freeglut.h>

void Shape3D::setMTL(const Material& m){
    this->mtl = m;
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
