#ifndef VECTOR4_H
#define VECTOR4_H

#include "Vector3.h"

struct Vector4
{
    float x, y, z, w;

    Vector4(float _x=0.0f, float _y=0.0f, float _z=0.0f, float _w=0.0f): x(_x), y(_y), z(_z), w(_w) {};
    Vector4(const Vector3 &vector3): x(vector3.x), y(vector3.y), z(vector3.z), w(1.0f) {};

    Vector4 operator+(const Vector4 &b);

	Vector4 operator-(const Vector4 &b);

	Vector4 operator*(double b);

	Vector4 operator*(const Vector4 &b);
};


#endif