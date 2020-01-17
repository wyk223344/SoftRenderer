#ifndef VECTOR3_H
#define VECTOR3_H
#include <math.h>

struct Vector4;

struct Vector3
{
    float x, y, z;

    Vector3(float _x=0.0f, float _y=0.0f, float _z=0.0f): x(_x), y(_y), z(_z) {};
	Vector3(const Vector4 &vector4);

    Vector3 operator+(const Vector3 &b);

	Vector3 operator-(const Vector3 &b);

	Vector3 operator*(double b);

	Vector3 operator*(const Vector3 &b);

	float& operator[](int i);

	Vector3 mult(const Vector3 &b);

	Vector3& normalize();

	double dot(const Vector3 &b);

	Vector3 cross(const Vector3 &b);
};


#endif