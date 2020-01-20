#ifndef MATRIX4X4_H
#define MATRIX4X4_H


struct Vector3;
struct Quaternion;


struct Matrix4x4 {
   static Matrix4x4 LookAt(Vector3 &eye, Vector3 &target, Vector3 &upDir);

   float elements[4][4];

   Matrix4x4();

   void updateMatrix(Vector3 position, Quaternion rotation, Vector3 scale);

   Matrix4x4 operator+(const Matrix4x4 &b);
   Matrix4x4 operator-(const Matrix4x4 &b);
   Matrix4x4 operator*(double b);
   Matrix4x4 operator*(const Matrix4x4 &b);
   float* operator[](int i);

   void operator+=(const Matrix4x4 &b);
   void operator-=(const Matrix4x4 &b);
   void operator*=(const float b);
   void operator*=(const Matrix4x4 &b);

};



#endif