#ifndef FRAME_BUFFER_H
#define FRAME_BUFFER_H

#include "../math/Vector4.h"

class FrameBuffer {
public:
    FrameBuffer(int width, int height, int channel);
    ~FrameBuffer();

    unsigned char *getPixelBuffer();
    int getWidth();
    int getHeight();
    void setPixelBuffer(unsigned char *pixelBuffer);
    void clearPixelBuffer();
    void clonePixelBufferTo(FrameBuffer *destFrameBuffer);
    void drawPixel(unsigned int x, unsigned int y, Vector4 color);
    void clean();
private:
    int m_Width;
    int m_Height;
    int m_Channel;
    int m_Size;
    unsigned char *m_PixelBuffer;
};




#endif