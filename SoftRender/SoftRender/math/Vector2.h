#ifndef VECTOR2_H
#define VECTOR2_H

struct Vector2
{
    float x, y;

    Vector2(float _x=0.0f, float _y=0.0f): x(_x), y(_y) {};

    Vector2 operator+(const Vector2 &b);

	Vector2 operator-(const Vector2 &b);

	Vector2 operator*(double b);

	Vector2 operator*(const Vector2 &b);

    float& operator[](int i);
};

#endif