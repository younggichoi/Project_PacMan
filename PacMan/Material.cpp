//
//  Material.cpp
//  Mission10
//
//  Created by 이현우 on 11/3/24.
//

#include "Material.h"

Material::Material(){
    setEmission(0.0f, 0.0f, 0.0f, 0.0f);
    setAmbient(0.0f, 0.0f, 0.0f, 0.0f);
    setDiffuse(0.0f, 0.0f, 0.0f, 0.0f);
    setSpecular(0.0f, 0.0f, 0.0f, 0.0f);
    setShininess(0.0f);
}

void Material::setEmission(float r, float g, float b, float a){
    this->emission[0] = r; this->emission[1] = g; this->emission[2] = b; this->emission[3] = a;
}

void Material::setAmbient(float r, float g, float b, float a){
    this->ambient[0] = r; this->ambient[1] = g; this->ambient[2] = b; this->ambient[3] = a;
}
void Material::setDiffuse(float r, float g, float b, float a){
    this->diffuse[0] = r; this->diffuse[1] = g; this->diffuse[2] = b; this->diffuse[3] = a;
}
void Material::setSpecular(float r, float g, float b, float a){
    this->specular[0] = r; this->specular[1] = g; this->specular[2] = b; this->specular[3] = a;
}
void Material::setShininess(float sh){
    this->shininess = sh;
}

Vector4f Material::getEmission() const{
    return emission;
}
Vector4f Material::getAmbient() const{
    return ambient;
}
Vector4f Material::getDiffuse() const{
    return diffuse;
}
Vector4f Material::getSpecular() const{
    return specular;
}
float Material::getShininess() const{
    return shininess;
}

bool Material::operator==(const Material& m) const {
    if (emission != m.getEmission()) return false;
    if (ambient != m.getAmbient()) return false;
    if (diffuse != m.getDiffuse()) return false;
    if (specular != m.getSpecular()) return false;
    if (shininess != m.getShininess()) return false;
    return true;
}