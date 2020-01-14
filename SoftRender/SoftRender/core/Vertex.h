#ifndef VERTEX_H
#define VERTEX_H

#include "../math/Vector2.h"
#include "../math/Vector3.h"
#include "../math/Vector4.h"


struct Vertex
{
    Vector4 position;
    Vector4 color;
    Vector2 texcoord;
    Vector3 normal;
};




#endif