#include "Vector4.h"
#include "Vector3.h"

Vector4::Vector4(const Vector3 &vector3) {
    x = vector3.x;
    y = vector3.y;
    z = vector3.z;
    w = 1.0f;
}

Vector4 Vector4::operator+(const Vector4 &b) {
    return Vector4(x + b.x, y + b.y, z + b.z, w + b.w);
}


Vector4 Vector4::operator-(const Vector4 &b) {
    return Vector4(x - b.x, y - b.y, z - b.z, w - b.w);
}

Vector4 Vector4::operator*(double b) {
    return Vector4(x * b, y * b, z * b, w * b);
}

Vector4 Vector4::operator*(const Vector4 &b) {
    return Vector4(x * b.x, y * b.y, z * b.z, w * b.w);
}

float& Vector4::operator[](int i) {
    switch (i) {
		case 0: return x;
		case 1: return y;
		case 2: return z;
        case 3: return w;
		default: break;
	}
}