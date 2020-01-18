#ifndef UTIL_H
#define UTIL_H

struct Vector2;
struct Vector3;
struct Vector4;
struct Image;
class FrameBuffer;


class Util {
public:
    static Vector3 CalcuBarycentric(Vector2 *pts, Vector2 point);
    static void DrawLine(int x0, int y0, int x1, int y1, FrameBuffer frameBuffer, Vector4 color);
    static void DrawTriangle(Vector3 *pts, float *zBuffer, FrameBuffer frameBuffer, Vector2 *uvs, Image image, float intensity);
};


#endif