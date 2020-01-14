#include <stdlib.h>
#include <memory.h>
#include <iostream>
#include "FrameBuffer.h"


FrameBuffer FrameBuffer::Create(int width, int height, int channel) {
    FrameBuffer frameBuffer = FrameBuffer();
    frameBuffer.m_Width = width;
    frameBuffer.m_Height = height;
    frameBuffer.m_Channel = channel;

    int size = sizeof(unsigned char) * width * height * channel;
    frameBuffer.m_PixelBuffer = (unsigned char *)malloc(size);
    memset(frameBuffer.m_PixelBuffer, 0, size);

    std::cout << "FrameBuffer:Create" << size << std::endl;

    return frameBuffer;
};


unsigned char *FrameBuffer::getPixelBuffer() {
    return m_PixelBuffer;
};


void FrameBuffer::setPixelBuffer(unsigned char *pixelBuffer) {
    clearPixelBuffer();
    m_PixelBuffer = pixelBuffer;
};

void FrameBuffer::clearPixelBuffer() {
    free(m_PixelBuffer);
    m_PixelBuffer = NULL;
};


int FrameBuffer::getWidth() {
    return m_Width;
};


int FrameBuffer::getHeight() {
    return m_Height;
};


void FrameBuffer::clonePixelBufferTo(FrameBuffer destFrameBuffer) {
    int width = m_Width;
    int height = m_Height;

    unsigned char *curPixelBuffer = m_PixelBuffer;
    unsigned char *destPixelBuffer = destFrameBuffer.getPixelBuffer();

    for (int r = 0; r < height; r++) {
        for (int c = 0; c < width; c++) {
            int flippedR = height - 1 - r;
            int srcIndex = (r * width + c) * 4;
            int dstIndex = (flippedR * width + c) * 4;
            unsigned char *srcPixel = &curPixelBuffer[srcIndex];
            unsigned char *dstPixel = &destPixelBuffer[dstIndex];
            dstPixel[0] = srcPixel[2];  /* blue */
            dstPixel[1] = srcPixel[1];  /* green */
            dstPixel[2] = srcPixel[0];  /* red */
        }
    }
};


void FrameBuffer::drawPixel(unsigned int x, unsigned int y, Vector4 color) {
    if(x < 0 || x >= m_Width || y < 0 || y >= m_Height)
        return;
    // gamma correction.
    unsigned char red = static_cast<unsigned char>(255*pow(color.x,1.0/2.2));
    unsigned char green = static_cast<unsigned char>(255*pow(color.y,1.0/2.2));
    unsigned char blue = static_cast<unsigned char>(255*pow(color.z,1.0/2.2));
    unsigned char alpha = static_cast<unsigned char>(255*color.w);
    unsigned int index = y * m_Width * m_Channel + x * m_Channel;
    m_PixelBuffer[index + 0] = red;
    m_PixelBuffer[index + 1] = green;
    m_PixelBuffer[index + 2] = blue;
    m_PixelBuffer[index + 3] = alpha;
}