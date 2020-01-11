#ifndef WINDOW_H
#define WINDOW_H

#include <Windows.h>

static const wchar_t *WINDOW_CLASS_NAME = L"Class";

class Window {
public:
    static Window Create(const char *title, int width, int height);

    bool shouldClose();

private:    
    static void RegisterWindowClass();

    HWND m_Handle;
    void createWindow(const char *title, int width, int height);
    void showWindow();
    void hideWindow();
    
};

#endif