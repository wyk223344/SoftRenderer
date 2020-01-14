#include "Vector3.h"


Vector3 Vector3::operator+(const Vector3 &b) const {
	return Vector3(x + b.x, y + b.y, z + b.z);
}

Vector3 Vector3::operator-(const Vector3 &b) const {
	return Vector3(x - b.x, y - b.y, z - b.z);
}

Vector3 Vector3::operator*(double b) const {
	return Vector3(x * b, y * b, z * b);
}

Vector3 Vector3::operator*(const Vector3 &b) const {
	return Vector3(x * b.x, y * b.y, z * b.z);
}

Vector3 Vector3::mult(const Vector3 &b) const {
	return Vector3(x * b.x, y * b.y, z * b.z);
}

Vector3& Vector3::normalize() {
	return *this = *this * (1 / sqrt(x * x + y * y + z * z));
}

double Vector3::dot(const Vector3 &b) const {
	return x * b.x + y * b.y + z * b.z;
}

Vector3 Vector3::cross(const Vector3 &b) const {
	return Vector3(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
}
