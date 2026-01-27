#define STRICT
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) { // LRESULT = long int
    if (uMsg == WM_DESTROY) {  // WM_DESTROY = окно закрывается
        PostQuitMessage(0);  // выход из программы
        return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int main() {
    char className[] = "MyWindow";
    char windowTitle[] = "My Window";

    WNDCLASS wc = {}; // WNDCLASS = структура с настройками окна
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

    MSG msg = {}; //    MSG = структура с инфой о сообщении
    while (GetMessage(&msg, 0, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}