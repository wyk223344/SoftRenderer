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


// Matrix4x4 Matrix4x4::operator+(const Matrix4x4 &b) {

// }


// Matrix4x4 Matrix4x4::operator-(const Matrix4x4 &b) {

// }


// Matrix4x4 Matrix4x4::operator*(double b) {

// }

// Matrix4x4 Matrix4x4::operator*(const Matrix4x4 &b) {

// }

float* Matrix4x4::operator[](int i) {
    return elements[i];
}