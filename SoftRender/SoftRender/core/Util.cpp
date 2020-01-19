#include "Util.h"
#include "../math/Vector2.h"
#include "../math/Vector3.h"
#include "../math/Vector4.h"
#include "FrameBuffer.h"
#include "Image.h"
#include <cmath>
#include <algorithm>
#include <iostream>


Vector3 Util::CalcuBarycentric(Vector2 *pts, Vector2 point) {
    Vector3 temp[2];
     for (int i = 0; i < 2; i++) {
        temp[i][0] = pts[1][i] - pts[0][i];
        temp[i][1] = pts[2][i] - pts[0][i];
        temp[i][2] = pts[0][i] - point[i];
    }
    Vector3 u = temp[0].cross(temp[1]);
    if (std::abs(u.z) > 1e-2) {
        return Vector3(1.0f - (u.x + u.y) / u.z, u.x / u.z, u.y / u.z);
    }
    return Vector3(-1.0f, 1.0f, 1.0f);
}


void Util::DrawLine(int x0, int y0, int x1, int y1, FrameBuffer frameBuffer, Vector4 color) {
    bool steep = false;
    if (std::abs(x0 - x1) < std::abs(y0 - y1)) {
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }
    if (x0 > x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }
    int dx = x1 - x0;
    int dy = y1 - y0;
    int derror2 = std::abs(dy)*2;
    int error2 = 0;
    int y = y0;
    for (int x = x0; x <= x1; x++) {
        if (steep) {
            frameBuffer.drawPixel(y, x, color);
        } else {
            frameBuffer.drawPixel(x, y, color);
        }
        error2 += derror2;
        if (error2 > dx) {
            y += (y1 > y0 ? 1 : -1);
            error2 -= dx * 2;
        }
    }
}

const float MAX_FLOAT = (std::numeric_limits<float>::max)();

void Util::DrawTriangle(Vector3 *pts, float *zBuffer, FrameBuffer frameBuffer, Vector2 *uvs, Image image, float intensity) {
    Vector2 vBoxMin(MAX_FLOAT, MAX_FLOAT);
    Vector2 vBoxMax(-MAX_FLOAT, -MAX_FLOAT);
    Vector2 vClamp(frameBuffer.getWidth() - 1, frameBuffer.getHeight() - 1);
    Vector2 pts2[3];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            vBoxMin[j] = std::max(0.0f,         std::min(vBoxMin[j], pts[i][j]));
            vBoxMax[j] = std::min(vClamp[j],    std::max(vBoxMax[j], pts[i][j]));
        }
        pts2[i] = Vector2(pts[i][0], pts[i][1]);
    }

    Vector3 vTemp;
    Vector2 uv;
    for (vTemp.x = vBoxMin.x; vTemp.x <= vBoxMax.x; vTemp.x++) {
        for (vTemp.y = vBoxMin.y; vTemp.y <= vBoxMax.y; vTemp.y++) {
            Vector3 bcScreen = CalcuBarycentric(pts2, Vector2(vTemp.x, vTemp.y));
            if (bcScreen.x < 0 || bcScreen.y < 0 || bcScreen.z < 0) continue;
            vTemp.z = 0;
            uv.x = 0;
            uv.y = 0;
            for (int i = 0; i < 3; i++) {
                vTemp.z += pts[i][2] * bcScreen[i];
                uv.x += uvs[i][0] * bcScreen[i];
                uv.y += uvs[i][1] * bcScreen[i];
            }
            int index = int(vTemp.x + vTemp.y * frameBuffer.getWidth());
            if (zBuffer[index] < vTemp.z) {
                Vector4 color = image.getColor(uv.x, uv.y);
                color.x *= intensity;
                color.y *= intensity;
                color.z *= intensity;
                // std::cout << "u:" << uv.x << ";v:" << uv.y << ";color" << color.x << std::endl;
                zBuffer[index] = vTemp.z;
                frameBuffer.drawPixel(vTemp.x, vTemp.y, color);
            }
        }
    }
}