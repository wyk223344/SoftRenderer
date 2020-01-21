#include "Matrix4x4.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Quaternion.h"
#include <cmath>
#include <iostream>

Matrix4x4::Matrix4x4(bool isInit) {
    if (isInit) {
        identity();
    }  
}


void Matrix4x4::updateMatrix(Vector3 position, Quaternion rotation, Vector3 scale) {

}

void Matrix4x4::identity() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            elements[i][j] = i == j ? 1 : 0;
        }
    }
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

Vector4 Matrix4x4::operator*(const Vector4 &b) {
    Vector4 vector4;
    vector4.x = elements[0][0] * b.x + elements[0][1] * b.y + elements[0][2] * b.z + elements[0][3] * b.w;
    vector4.y = elements[1][0] * b.x + elements[1][1] * b.y + elements[1][2] * b.z + elements[1][3] * b.w;
    vector4.z = elements[2][0] * b.x + elements[2][1] * b.y + elements[2][2] * b.z + elements[2][3] * b.w;
    vector4.w = elements[3][0] * b.x + elements[3][1] * b.y + elements[3][2] * b.z + elements[3][3] * b.w;
    return vector4;
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

/*
    http://www.songho.ca/opengl/gl_camera.html
*/

Matrix4x4 Matrix4x4::CreateViewMatrixByLookAt(Vector3 &eye, Vector3 &target, Vector3 &upDir, Matrix4x4 outMatrix) {
    Vector3 forward = eye - target;
    forward.normalize();

    Vector3 left = upDir.cross(forward);
    left.normalize();

    Vector3 up = forward.cross(left);

    outMatrix.identity();
    outMatrix[0][0] = left.x;
    outMatrix[0][1] = left.y;
    outMatrix[0][2] = left.z;
    outMatrix[1][0] = up.x;
    outMatrix[1][1] = up.y;
    outMatrix[1][2] = up.z;
    outMatrix[2][0] = forward.x;
    outMatrix[2][1] = forward.y;
    outMatrix[2][2] = forward.z;

    outMatrix[0][3] = -left.x * eye.x - left.y * eye.y - left.z * eye.z;
    outMatrix[1][3] = -up.x * eye.x - up.y * eye.y - up.z * eye.z;
    outMatrix[2][3] = -forward.x * eye.x - forward.y * eye.y - forward.z * eye.z;


    return outMatrix;
}


Matrix4x4 Matrix4x4::CreatePerspectiveProjectionMatrix(float fovy, float aspect, float near, float far, Matrix4x4 outMatrix) {
    float halfHeight = near * (float)std::tan(fovy * 0.5f);
    float halfWidth = halfHeight * aspect;
    return CreatePerspectiveProjectionMatrix(-halfWidth, halfWidth, -halfHeight, halfHeight, near, far);
}

/*
    http://www.songho.ca/opengl/gl_projectionmatrix.html
*/

Matrix4x4 Matrix4x4::CreatePerspectiveProjectionMatrix(float left, float right, float bottom, float top, float near, float far, Matrix4x4 outMatrix) {
    float tempX = 1.0f / (right - left);
    float tempY = 1.0f / (top - bottom);
    float tempZ = 1.0f / (far - near);
    outMatrix.identity();
    outMatrix[0][0] = 2.0f * near * tempX;
    outMatrix[0][2] = (right + left) * tempX;
    outMatrix[1][1] = 2.0f * near * tempY;
    outMatrix[1][2] = (top + bottom) * tempY;
    outMatrix[2][2] = -(far + near) * tempZ;
    outMatrix[2][3] = -2.0f * far * near * tempZ;
    outMatrix[3][2] = -1.0f;
    outMatrix[3][3] = 0;
    return outMatrix;
}

/*
    http://www.songho.ca/opengl/gl_projectionmatrix.html
*/

Matrix4x4 Matrix4x4::CreateOrthographicProjectionMatrix(float left, float right, float bottom, float top, float near, float far, Matrix4x4 outMatrix) {
    float tempX = 1.0f / (right - left);
    float tempY = 1.0f / (top - bottom);
    float tempZ = 1.0f / (far - near);
    outMatrix.identity();
    outMatrix[0][0] = 2.0f * tempX;
    outMatrix[0][3] = -(right + left) * tempX;
    outMatrix[1][1] = 2.0f * tempY;
    outMatrix[1][3] = -(top + bottom) * tempY;
    outMatrix[2][2] = -2.0f * tempZ;
    outMatrix[2][3] = -(far + near) * tempZ;
    return outMatrix;
}





void Matrix4x4::print() {
    std::cout << "Matrix4x4-----------------------" << std::endl;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            std::cout << elements[i][j] << "   ";
        }
        std::cout << std::endl;
    }
}