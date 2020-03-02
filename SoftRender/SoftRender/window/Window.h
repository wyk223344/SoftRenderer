#ifndef WINDOW_H
#define WINDOW_H

#include <Windows.h>
#include "../core/FrameBuffer.h"

#ifdef UNICODE
static const wchar_t *WINDOW_CLASS_NAME = L"Class";
static const wchar_t *WINDOW_ENTRY_NAME = L"Entry";
#else
static const char *WINDOW_CLASS_NAME = "Class";
static const char *WINDOW_ENTRY_NAME = "Entry";
#endif

struct OperateRecord {
    float x, y;
    boolean isLeftBtnDown = false;
    boolean close = false;
};

class Window {
public:
    static void RegisterWindowClass();

    Window(const char *title, int width, int height);
    ~Window();
    bool shouldClose();
    void drawBuffer(FrameBuffer *frameBuffer);
    void updateOperateRecord();
    OperateRecord *getOperateRecord() {return m_OperateRecord;};
private:    
    HWND m_Handle;
    HDC m_MemoryDC;
    FrameBuffer *m_FrameBuffer;
    OperateRecord *m_OperateRecord;
    
    void createWindow(const char *title, int width, int height);
    void createFrameBuffer(int width, int height);
    void showWindow();
    void hideWindow();
};

#endif