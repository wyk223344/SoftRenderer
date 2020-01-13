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
    unsigned char *destPixelBuffer = destFrameBuffer.m_PixelBuffer;

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