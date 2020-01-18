#ifndef QUATERNION_H
#define QUATERNION_H



struct Quaternion {
    float x, y, z, w;
    Quaternion(float _x=0.0f, float _y=0.0f, float _z=0.0f, float _w=1.0f): x(_x), y(_y), z(_z), w(_w) {};
};


#endif