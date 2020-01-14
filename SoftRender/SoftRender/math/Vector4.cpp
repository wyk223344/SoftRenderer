#include "Vector4.h"


Vector4 Vector4::operator+(const Vector4 &b) {
    return Vector4(x + b.x, y + b.y, z + b.z, w + b.w);
};