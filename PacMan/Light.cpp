//
//  Light.cpp
//  Mission10
//
//  Created by 이현우 on 11/3/24.
//

#include "Light.h"

Light::Light(float x, float y, float z, int L_ID){
    pos[0] = x; pos[1] = y; pos[2] = z; lightID = L_ID;
}

void Light::setAmbient(float r, float g, float b, float a){
    ambient[0] = r; ambient[1] = g; ambient[2] = b; ambient[3] = a;
}
void Light::setDiffuse(float r, float g, float b, float a){
    diffuse[0] = r; diffuse[1] = g; diffuse[2] = b; diffuse[3] = a;
}

void Light::setSpecular(float r, float g, float b, float a){
    specular[0] = r; specular[1] = g; specular[2] = b; specular[3] = a;
}

Vector4f Light::getAmbient() const{
    return ambient;
}
Vector4f Light::getDiffuse() const{
    return diffuse;
}
Vector4f Light::getSpecular() const{
    return specular;
}
int Light::getID() const{
    return lightID;
}

void Light::draw() const{
    //glEnable(lightID);
    glLightfv(lightID, GL_AMBIENT, ambient.pos);
    glLightfv(lightID, GL_DIFFUSE, diffuse.pos);
    glLightfv(lightID, GL_SPECULAR, specular.pos);
    glLightfv(lightID, GL_POSITION, pos.pos);
    //glDisable(lightID);
}
