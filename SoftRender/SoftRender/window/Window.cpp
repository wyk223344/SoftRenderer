#include "Window.h"
#include <assert.h>
// #include <Windows.h>


LRESULT CALLBACK ProcessMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
};



Window Window::Create(const char *title, int width, int height) {
    RegisterWindowClass();
    Window window = Window();
    window.createWindow(title, width, height);
    window.showWindow();
    return window;
};

void Window::RegisterWindowClass() {
    ATOM class_atom;
    WNDCLASS window_class;
    window_class.style = CS_HREDRAW | CS_VREDRAW;
    window_class.lpfnWndProc = ProcessMessage;
    window_class.cbClsExtra = 0;
    window_class.cbWndExtra = 0;
    window_class.hInstance = GetModuleHandle(NULL);
    window_class.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    window_class.hCursor = LoadCursor(NULL, IDC_ARROW);
    window_class.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    window_class.lpszMenuName = NULL;
    window_class.lpszClassName = WINDOW_CLASS_NAME;
    class_atom = RegisterClass(&window_class);
    assert(class_atom != 0);
    // UNUSED_VAR(class_atom);
};

void Window::createWindow(const char *title, int width, int height) {
    DWORD style = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
    RECT rect;
    HWND handle;
    rect.left = 0;
    rect.top = 0;
    rect.right = width;
    rect.bottom = height;
    AdjustWindowRect(&rect, style, 0);
    width = rect.right - rect.left;
    height = rect.bottom - rect.top;

    // 转换标题格式
    int num = MultiByteToWideChar(0, 0, title, -1, NULL, 0);
    wchar_t *newTitle = new wchar_t[num];
    MultiByteToWideChar(0, 0, title, -1, newTitle, num);

    handle = CreateWindow(WINDOW_CLASS_NAME, newTitle, style,
                          CW_USEDEFAULT, CW_USEDEFAULT, width, height,
                          NULL, NULL, GetModuleHandle(NULL), NULL);
    
    m_Handle = handle;
    assert(handle != NULL);
};

void Window::showWindow() {
    if (!m_Handle) {
        return;
    }
    ShowWindow(m_Handle, SW_SHOW);
    UpdateWindow(m_Handle);
};

void Window::hideWindow() {
    if (!m_Handle) {
        return;
    }
    ShowWindow(m_Handle, SW_HIDE);
};

bool Window::shouldClose() {
    return false;
};

