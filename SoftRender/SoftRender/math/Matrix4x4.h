#ifndef MATRIX4X4_H
#define MATRIX4X4_H

#include <iostream>
struct Vector3;
struct Vector4;
struct Quaternion;


struct Matrix4x4 {
   float elements[4][4];
   Matrix4x4(bool isInit = true);

   static Matrix4x4 CreateViewMatrixByLookAt(Vector3 &eye, Vector3 &target, Vector3 &upDir, Matrix4x4 outMatrix=Matrix4x4(false));
   static Matrix4x4 CreatePerspectiveProjectionMatrix(float fovy, float aspect, float near, float far, Matrix4x4 outMatrix=Matrix4x4(false));
   static Matrix4x4 CreatePerspectiveProjectionMatrix(float left, float right, float bottom, float top, float near, float far, Matrix4x4 outMatrix=Matrix4x4(false));
   static Matrix4x4 CreateOrthographicProjectionMatrix(float left, float right, float bottom, float top, float near, float far, Matrix4x4 outMatrix=Matrix4x4(false));
   

   void updateMatrix(Vector3 position, Quaternion rotation, Vector3 scale);

   void identity();

   Matrix4x4 operator+(const Matrix4x4 &b);
   Matrix4x4 operator-(const Matrix4x4 &b);
   Matrix4x4 operator*(double b);
   Matrix4x4 operator*(const Matrix4x4 &b);
   Vector4 operator*(const Vector4 &b);
   float* operator[](int i);

   void operator+=(const Matrix4x4 &b);
   void operator-=(const Matrix4x4 &b);
   void operator*=(const float b);
   void operator*=(const Matrix4x4 &b);

   void print();

};



#endif