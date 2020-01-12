#ifndef FRAME_BUFFER_H
#define FRAME_BUFFER_H

class FrameBuffer {
public:
    static FrameBuffer Create(int width, int height, int channel);
    unsigned char *getPixelBuffer();
    void clearPixelBuffer();
    int getWidth();
    int getHeight();
    void clonePixelBufferTo(FrameBuffer destFrameBuffer);
private:
    int m_Width;
    int m_Height;
    int m_Channel;
    unsigned char *m_PixelBuffer;
};




#endif