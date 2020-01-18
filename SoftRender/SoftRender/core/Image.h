#ifndef IMAGE_H
#define IMAGE_H
#include <iostream>
#include <fstream>
#include "../math/Vector4.h"

struct Image {
    unsigned char *data;
    int width;
    int height;
    int bytesLen;

    enum Format {
        GRAYSCALE=1, RGB=3, RGBA=4
    };

    bool readTgaFile(const char *fileName);

    Vector4 getColor(float u, float v);

private:
    bool loadRLEData(std::ifstream &in);
};



#endif