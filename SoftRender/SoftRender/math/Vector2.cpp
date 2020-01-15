#include "Vector2.h"


Vector2 Vector2::operator+(const Vector2 &b) {
    return Vector2(x + b.x, y + b.y);
}

Vector2 Vector2::operator-(const Vector2 &b) {
    return Vector2(x - b.x, y - b.y);
}

Vector2 Vector2::operator*(double b) {
    return Vector2(x * b, y * b);
}

Vector2 Vector2::operator*(const Vector2 &b) {
    return Vector2(x * b.x, y * b.y);
}