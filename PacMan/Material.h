//
//  Material.h
//  PacMan
//
//  Created by 이현우 on 10/31/24.
//

#pragma once
#include "Constants.h"
#include "Vector3f.h"
#include "Vector4f.h"

class Material{
public:
    Material();
    void setEmission(float r, float g, float b, float a);
    void setAmbient(float r, float g, float b, float a);
    void setDiffuse(float r, float g, float b, float a);
    void setSpecular(float r, float g, float b, float a);
    void setShininess(float sh);
    
    Vector4f getEmission() const;
    Vector4f getAmbient() const;
    Vector4f getDiffuse() const;
    Vector4f getSpecular() const;
    float getShininess() const;
    
private:
    Vector4f emission;
    Vector4f ambient;
    Vector4f diffuse;
    Vector4f specular;
    float shininess;
};
