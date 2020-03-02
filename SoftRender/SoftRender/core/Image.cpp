#include "Image.h"
#include "../util/Util.h"

#pragma pack(1)
struct TGAHeader {
    char idLength;
    char colorMapType;
    char imageType;
    short colorMapOrigin;
    short colorMapLength;
    char colorMapDepth;
    short xOrigin;
    short yOrigin;
    short width;
    short height;
    char  bitsPerPixel;
    char  imageDescriptor;
};
#pragma pack()



bool Image::readTgaFile(const char *fileName) {
    LogUtil::LogInfo("[Image]Start load image file %s.", fileName);
    if (data) delete [] data;
    data = NULL;
    std::ifstream in;
    in.open(fileName, std::ios::binary);
    if (in.fail()) {
        LogUtil::LogError("[Image]File %s load fail.", fileName);
        return false;
    }
    TGAHeader tgaHeader;
    in.read((char *)&tgaHeader, sizeof(tgaHeader));
    if (!in.good()) {
        in.close();
        LogUtil::LogError("[Image]An error occured while reading the header.");
        return false;
    }
    width = tgaHeader.width;
    height = tgaHeader.height;
    bytesLen = tgaHeader.bitsPerPixel >> 3;
    if (width<=0 || height<=0 || (bytesLen!=GRAYSCALE && bytesLen!=RGB && bytesLen!=RGBA)) {
        in.close();
        LogUtil::LogError("[Image]Bad bytesLen (or width/height) value.");
        return false;
    }
    unsigned long length = bytesLen * width * height;
    data = new unsigned char[length];
    if (tgaHeader.imageType < 8) {
        in.read((char *)data, length);
    } else {
        loadRLEData(in);
    }
    in.close();
    LogUtil::LogInfo("[Image]Finish load image file.");
    return true;
}



bool Image::loadRLEData(std::ifstream &in) {
    unsigned long pixelCount = width * height;
    unsigned long currentPixel = 0;
    unsigned long currentByte  = 0;
    unsigned char colorBuffer[4];
    do {
        unsigned char chunkHeader = 0;
        chunkHeader = in.get();
        if (!in.good()) {
            std::cerr << "an error occured while reading the data\n";
            return false;
        }
        if (chunkHeader<128) {
            chunkHeader++;
            for (int i=0; i<chunkHeader; i++) {
                in.read((char *)colorBuffer, bytesLen);
                if (!in.good()) {
                    std::cerr << "an error occured while reading the header\n";
                    return false;
                }
                for (int t=0; t<bytesLen; t++)
                    data[currentByte++] = colorBuffer[t];
                currentPixel++;
                if (currentPixel>pixelCount) {
                    std::cerr << "Too many pixels read\n";
                    return false;
                }
            }
        } else {
            chunkHeader -= 127;
            in.read((char *)colorBuffer, bytesLen);
            if (!in.good()) {
                std::cerr << "an error occured while reading the header\n";
                return false;
            }
            for (int i=0; i<chunkHeader; i++) {
                for (int t=0; t<bytesLen; t++)
                    data[currentByte++] = colorBuffer[t];
                currentPixel++;
                if (currentPixel>pixelCount) {
                    std::cerr << "Too many pixels read\n";
                    return false;
                }
            }
        }
    } while (currentPixel < pixelCount);
}



Vector4 Image::getColor(float u, float v) {
    unsigned char* colorStart = data + (int(u * width) + int(v * height) * width) * bytesLen;
    if (bytesLen == GRAYSCALE) {
        float temp = colorStart[0] / 255.0f;
        return Vector4(temp, temp, temp, 1.0f);
    } else if (bytesLen == RGB) {
        return Vector4(colorStart[0] / 255.0f, colorStart[1] / 255.0f, colorStart[2] / 255.0f, 1.0f);
    } else if (bytesLen == RGBA) {
        return Vector4(colorStart[0] / 255.0f, colorStart[1] / 255.0f, colorStart[2] / 255.0f, colorStart[3] / 255.0f);
    }
    return Vector4();
}