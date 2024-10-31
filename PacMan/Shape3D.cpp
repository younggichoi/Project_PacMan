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
void Shape3D::setMTL(const Material& m){
    this->mtl = m;
}
void Shape3D::increaseAngleOfSpin(float ang){
    this->angleOfSpin += ang;
}
void Shape3D::increaseAngleOfvolution(float ang){
    this->angleOfRevolution += ang;
}
void Shape3D::draw() const{
    /*
    if(this->shape == DODECAHEDRON){
        glTranslatef(this->pos[0], this->pos[1], this->pos[2]);
        glPushMatrix();
        glRotatef(this->angleOfSpin, 1.0f, 1.0f, 1.0f);
        glShadeModel(GL_SMOOTH);
        glMaterialfv(GL_FRONT, GL_EMISSION, this->mtl.emission);
        glMaterialfv(GL_FRONT, GL_AMBIENT, this->mtl.ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, this->mtl.diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, this->mtl.specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, this->mtl.shininess);
        glutSolidDodecahedron();
        glPopMatrix();
    }
    if(this->shape == CUBE){
        glTranslatef(this->pos[0], this->pos[1], this->pos[2]);
        glPushMatrix();
        glRotatef(this->angleOfSpin, 0.0f, 1.0f, 0.0f);
        glShadeModel(GL_SMOOTH);
        glMaterialfv(GL_FRONT, GL_EMISSION, this->mtl.emission);
        glMaterialfv(GL_FRONT, GL_AMBIENT, this->mtl.ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, this->mtl.diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, this->mtl.specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, this->mtl.shininess);
        glutSolidCube(this->size);
        glPopMatrix();
    }
    if(this->shape == TEAPOT){
        glTranslatef(this->pos[0], this->pos[1], this->pos[2]);
        glPushMatrix();
        glRotatef(this->angleOfSpin, 0.0f, 1.0f, 0.0f);
        glShadeModel(GL_SMOOTH);
        glMaterialfv(GL_FRONT, GL_EMISSION, this->mtl.emission);
        glMaterialfv(GL_FRONT, GL_AMBIENT, this->mtl.ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, this->mtl.diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, this->mtl.specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, this->mtl.shininess);
        glutSolidTeapot(this->size);
        glPopMatrix();
    }
    if(this->shape == TETRAHEDRON){
        glTranslatef(this->pos[0], this->pos[1], this->pos[2]);
        glPushMatrix();
        glRotatef(this->angleOfSpin, 0.0f, 1.0f, 0.0f);
        glShadeModel(GL_SMOOTH);
        glMaterialfv(GL_FRONT, GL_EMISSION, this->mtl.emission);
        glMaterialfv(GL_FRONT, GL_AMBIENT, this->mtl.ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, this->mtl.diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, this->mtl.specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, this->mtl.shininess);
        glutSolidTetrahedron();
        glPopMatrix();
    }
     */
    glTranslatef(this->pos[0], this->pos[1], this->pos[2]);
    glPushMatrix();
    glRotatef(this->angleOfSpin, 0.0f, 1.0f, 0.0f);
    glShadeModel(GL_SMOOTH);
    glMaterialfv(GL_FRONT, GL_EMISSION, this->mtl.emission);
    glMaterialfv(GL_FRONT, GL_AMBIENT, this->mtl.ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, this->mtl.diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, this->mtl.specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, this->mtl.shininess);
    glutSolidSphere(<#GLdouble radius#>, <#GLint slices#>, <#GLint stacks#>)
    glPopMatrix();
}


//SHAPE shape;
float pos[3];
float angleOfSpin;
float angleOfRevolution;
float size;
Material mtl;
