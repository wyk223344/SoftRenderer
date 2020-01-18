#ifndef VECTOR4_H
#define VECTOR4_H

struct Vector3;


struct Vector4 {
    float x, y, z, w;

    Vector4(float _x=0.0f, float _y=0.0f, float _z=0.0f, float _w=0.0f): x(_x), y(_y), z(_z), w(_w) {};
    Vector4(const Vector3 &vector3);

    Vector4 operator+(const Vector4 &b);

	Vector4 operator-(const Vector4 &b);

	Vector4 operator*(double b);

	Vector4 operator*(const Vector4 &b);

    float& operator[](int i);
};


#endif