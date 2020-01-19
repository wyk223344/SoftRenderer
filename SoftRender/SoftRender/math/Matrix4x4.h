#ifndef MATRIX4X4_H
#define MATRIX4X4_H


struct Vector3;
struct Quaternion;


struct Matrix4x4 {
   float elements[4][4];

   Matrix4x4();

   void updateMatrix(Vector3 position, Quaternion rotation, Vector3 scale);

   Matrix4x4 operator+(const Matrix4x4 &b);
   Matrix4x4 operator-(const Matrix4x4 &b);
   Matrix4x4 operator*(double b);
   Matrix4x4 operator*(const Matrix4x4 &b);
   float* operator[](int i);
};



#endif