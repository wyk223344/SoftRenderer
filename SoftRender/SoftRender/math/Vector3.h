#ifndef VECTOR3_H
#define VECTOR3_H
#include <math.h>

struct Vector3
{
    float x, y, z;

    Vector3(float _x=0.0f, float _y=0.0f, float _z=0.0f): x(_x), y(_y), z(_z) {};

    Vector3 operator+(const Vector3 &b) const;

	Vector3 operator-(const Vector3 &b) const;

	Vector3 operator*(double b) const;

	Vector3 operator*(const Vector3 &b) const;

	Vector3 mult(const Vector3 &b) const;

	Vector3& normalize();

	double dot(const Vector3 &b) const;

	Vector3 cross(const Vector3 &b) const;
};


#endif