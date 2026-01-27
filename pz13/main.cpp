#define STRICT
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (uMsg == WM_DESTROY) {
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int main() {
    char className[] = "MyWindow";
    char windowTitle[] = "My Window";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(0);
    wc.lpszClassName = className;

    RegisterClass(&wc);

    HWND hwnd = CreateWindow(
        className,
        windowTitle,
        WS_OVERLAPPEDWINDOW,
        100, 100,
        500, 300,
        0, 0,
        GetModuleHandle(0),
        0
        );

    ShowWindow(hwnd, SW_SHOW);

    MSG msg = {};
    while (GetMessage(&msg, 0, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}