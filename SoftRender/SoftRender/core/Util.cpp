#include "Util.h"
#include "../math/Vector2.h"
#include "../math/Vector3.h"
#include "../math/Vector4.h"
#include "FrameBuffer.h"
#include <cmath>
#include <algorithm>

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

const float MAX_FLOAT = std::numeric_limits<float>::max();

void Util::DrawTriangle(Vector3 *pts, float *zBuffer, FrameBuffer frameBuffer, Vector4 color) {
    Vector2 vBoxMin(MAX_FLOAT, MAX_FLOAT);
    Vector2 vBoxMax(-MAX_FLOAT, -MAX_FLOAT);
    Vector2 vClamp(frameBuffer.getWidth() - 1, frameBuffer.getHeight() - 1);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            vBoxMin[j] = std::max(0.0f,         std::min(vBoxMin[j], pts[i][j]));
            vBoxMax[j] = std::min(vClamp[j],    std::max(vBoxMax[j], pts[i][j]));
        }
    }
    Vector3 vTemp;
    for (vTemp.x = vBoxMin.x; vTemp.x <= vBoxMax.x; vTemp.x++) {
        for (vTemp.y = vBoxMin.y; vTemp.y <= vBoxMax.y; vTemp.y++) {
            
        }
    }
    // if (t0.y > t1.y) {
    //     std::swap(t0, t1);
    // }
    // if (t0.y > t2.y) {
    //     std::swap(t0, t2);
    // }
    // if (t1.y > t2.y) {
    //     std::swap(t1, t2);
    // }
    // int totalHeight = t2.y - t0.y;
    // for (int i = 0; i < totalHeight; i++) {
    //     bool isSecondHalf = i > (t1.y - t0.y) || t1.y == t0.y;
    //     int segmentHeight = isSecondHalf ? t2.y - t1.y : t1.y - t0.y;
    //     float alpha = (float) i / totalHeight;
    //     float beta = (float) (i - (isSecondHalf ? t1.y - t0.y : 0)) / segmentHeight;
    //     Vector2 pointA = t0 + (t2 - t0) * alpha;
    //     Vector2 pointB = isSecondHalf ? t1 + (t2 - t1) * beta : t0 + (t1 - t0) * beta;
    //     if (pointA.x > pointB.x) {
    //         std::swap(pointA, pointB);
    //     }
    //     for (int j = pointA.x; j <= pointB.x; j++) {
    //         frameBuffer.drawPixel(j, t0.y + i, color);
    //     }
    // }
}