#define STRICT
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

HBRUSH hBrush = NULL;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            if (hBrush) DeleteObject(hBrush);
            return 0;
        case WM_ACTIVATE:
            if (hBrush) DeleteObject(hBrush);
            hBrush = CreateSolidBrush(RGB(255, 200, 100));
            InvalidateRect(hwnd, NULL, TRUE);
            return 0;
        case WM_MOVE:
            if (hBrush) DeleteObject(hBrush);
            hBrush = CreateSolidBrush(RGB(100, 200, 255));
            InvalidateRect(hwnd, NULL, TRUE);
            return 0;
        case WM_RBUTTONDBLCLK:
            if (hBrush) DeleteObject(hBrush);
            hBrush = CreateSolidBrush(RGB(255, 100, 200));
            InvalidateRect(hwnd, NULL, TRUE);
            return 0;
        case WM_ERASEBKGND:
            if (hBrush) {
                RECT rc;
                GetClientRect(hwnd, &rc);
                FillRect((HDC)wParam, &rc, hBrush);
                return 1;
            }
            break;
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
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClass(&wc);

    HWND hwnd = CreateWindow(
        className,
        windowTitle,
        WS_OVERLAPPEDWINDOW,
        100, 100,
        500, 300,
        0, 0,
        GetModuleHandle(0),
        0);

    ShowWindow(hwnd, SW_SHOW);

    MSG msg = {};
    while (GetMessage(&msg, 0, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}