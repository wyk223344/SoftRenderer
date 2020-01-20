#include "Matrix4x4.h"
#include "Vector3.h"
#include "Quaternion.h"

Matrix4x4::Matrix4x4() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            elements[i][j] = i == j ? 1 : 0;
        }
    }
}


void Matrix4x4::updateMatrix(Vector3 position, Quaternion rotation, Vector3 scale) {

}


Matrix4x4 Matrix4x4::operator+(const Matrix4x4 &b) {
    Matrix4x4 matrix;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            matrix.elements[i][j] = elements[i][j] + b.elements[i][j];
        }
    }
    return matrix;
}


Matrix4x4 Matrix4x4::operator-(const Matrix4x4 &b) {
    Matrix4x4 matrix;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            matrix.elements[i][j] = elements[i][j] - b.elements[i][j];
        }
    }
    return matrix;
}


Matrix4x4 Matrix4x4::operator*(double b) {
    Matrix4x4 matrix;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            matrix.elements[i][j] = elements[i][j] * b;
        }
    }
    return matrix;
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4 &b) {
    Matrix4x4 matrix;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            matrix.elements[i][j] = 0;
            for (int k = 0; k < 4; k++) {
                matrix.elements[i][j] += elements[i][k] * b.elements[k][j];
            }
        }
    }
    return matrix;
}

float* Matrix4x4::operator[](int i) {
    return elements[i];
}


void Matrix4x4::operator+=(const Matrix4x4 &b) {
    (*this) = (*this)+b;
}

void Matrix4x4::operator-=(const Matrix4x4 &b) {
    (*this) = (*this)-b;
}

void Matrix4x4::operator*=(const Matrix4x4 &b) {
    (*this) = (*this)*b;
}

void Matrix4x4::operator*=(const float b) {
    (*this) = (*this)*b;
}


Matrix4x4 Matrix4x4::LookAt(Vector3 &eye, Vector3 &target, Vector3 &upDir) {
    Vector3 forward = eye - target;
    forward.normalize();

    Vector3 left = upDir.cross(forward);
    left.normalize();

    Vector3 up = forward.cross(left);

    Matrix4x4 matrix;
    matrix[0][0] = left.x;
    matrix[0][1] = left.y;
    matrix[0][1] = left.z;
    matrix[1][0] = up.x;
    matrix[1][1] = up.y;
    matrix[1][2] = up.z;
    matrix[2][0] = forward.x;
    matrix[2][1] = forward.y;
    matrix[2][2] = forward.z;
}