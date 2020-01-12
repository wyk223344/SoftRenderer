#ifndef WINDOW_H
#define WINDOW_H

#include <Windows.h>
#include "../core/FrameBuffer.h"

static const wchar_t *WINDOW_CLASS_NAME = L"Class";

class Window {
public:
    static Window Create(const char *title, int width, int height);

    bool shouldClose();
    void drawBuffer(FrameBuffer frameBuffer);

private:    
    static void RegisterWindowClass();

    FrameBuffer m_FrameBuffer;
    HWND m_Handle;
    HDC m_MemoryDC;
    void createWindow(const char *title, int width, int height);
    void createFrameBuffer(int width, int height);
    void showWindow();
    void hideWindow();
    
};

#endif