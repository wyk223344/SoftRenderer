#include "Vector3.h"
#include "Vector4.h"

Vector3::Vector3(const Vector4 &vector4) {
	x = vector4.x;
	y = vector4.y;
	z = vector4.z;
}

Vector3 Vector3::operator+(const Vector3 &b) {
	return Vector3(x + b.x, y + b.y, z + b.z);
}

Vector3 Vector3::operator-(const Vector3 &b) {
	return Vector3(x - b.x, y - b.y, z - b.z);
}

Vector3 Vector3::operator*(double b) {
	return Vector3(x * b, y * b, z * b);
}

Vector3 Vector3::operator*(const Vector3 &b) {
	return Vector3(x * b.x, y * b.y, z * b.z);
}

float& Vector3::operator[](int i) {
	switch (i) {
		case 0: return x;
		case 1: return y;
		case 2: return z;
		default: break;
	}
}

Vector3 Vector3::mult(const Vector3 &b) {
	return Vector3(x * b.x, y * b.y, z * b.z);
}

Vector3& Vector3::normalize() {
	return *this = *this * (1 / sqrt(x * x + y * y + z * z));
}

double Vector3::dot(const Vector3 &b) {
	return x * b.x + y * b.y + z * b.z;
}

Vector3 Vector3::cross(const Vector3 &b) {
	return Vector3(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
}
