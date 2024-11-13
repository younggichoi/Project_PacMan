//
//  Vector3f.cpp
//  Mission10
//
//  Created by 이현우 on 11/3/24.
//

#include "Vector3f.h"

Vector3f::Vector3f(){
    pos[0] = 0; pos[1] = 0; pos[2] = 0;
}
Vector3f::Vector3f(float a, float b, float c){
    pos[0] = a; pos[1] = b; pos[2] = c;
}

float Vector3f::getX() const { return pos[0]; }
float Vector3f::getY() const { return pos[1]; }
float Vector3f::getZ() const { return pos[2]; }

Vector3f& Vector3f::operator=(const Vector3f& v){
    pos[0] = v.pos[0]; pos[1] = v.pos[1]; pos[2] = v.pos[2];
    return *this;
}
Vector3f Vector3f::operator+(const Vector3f& a){
    return Vector3f(this->pos[0] + a.pos[0], this->pos[1] + a.pos[1], this->pos[2] + a.pos[2]);
}
Vector3f Vector3f::operator*(float s) const{
    return Vector3f(pos[0] * s, pos[1] * s, pos[2] * s);
}
Vector3f operator*(float s, const Vector3f& v) {
    return Vector3f(v.getX() * s, v.getY() * s, v.getZ() * s);
}

float& Vector3f::operator[](const int i){
    return pos[i];
}
float Vector3f::operator[](const int i) const{
    return pos[i];
}
Vector3f Vector3f::operator-(const Vector3f& v) {
    return Vector3f(this->getX() - v.getX(), this->getY() - v.getY(), this->getZ() - v.getZ());
}

void Vector3f::setPos(float a, float b, float c) {
    pos[0] = a; pos[1] = b; pos[2] = c;
}
void Vector3f::setPos(const Vector3f& v){
    this->pos[0] = v.pos[0]; this->pos[1] = v.pos[1]; this->pos[2] = v.pos[2];
}

float Vector3f::getAbs() {
    return sqrt(pow(pos[0], 2) + pow(pos[1], 2) + pow(pos[2], 2));
}