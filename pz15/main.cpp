#define STRICT
#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <windows.h>
#include "MathLib/library.h"

#define ID_EDIT_BASE 101
#define ID_EDIT_N 102
#define ID_EDIT_RESULT 103
#define ID_BTN_POWER 104
#define ID_BTN_NROOT 105
#define ID_BTN_CLEAR 106

HWND hEditBase, hEditN, hEditResult;
HWND hBtnPower, hBtnNRoot, hBtnClear;
HWND hLabelBase, hLabelN, hLabelResult;
HBRUSH hBrush = NULL;

void CalculatePower(HWND hwnd) {
    char bufferBase[256], bufferN[256];
    GetWindowText(hEditBase, bufferBase, 256);
    GetWindowText(hEditN, bufferN, 256);

    try {
        double base = std::stod(bufferBase);
        int n = std::stoi(bufferN);

        double result = power(base, n);

        std::ostringstream oss;
        oss << std::fixed << std::setprecision(6) << result;
        SetWindowText(hEditResult, oss.str().c_str());
    } catch (...) {
        MessageBox(hwnd, "Ошибка: проверьте введенные данные!", "Ошибка", MB_OK | MB_ICONERROR);
    }
}

void CalculateNRoot(HWND hwnd) {
    char bufferBase[256], bufferN[256];
    GetWindowText(hEditBase, bufferBase, 256);
    GetWindowText(hEditN, bufferN, 256);

    try {
        double value = std::stod(bufferBase);
        int n = std::stoi(bufferN);

        if (n == 0) {
            MessageBox(hwnd, "Ошибка: степень корня не может быть 0!", "Ошибка", MB_OK | MB_ICONERROR);
            return;
        }

        double result = nroot(value, n);

        std::ostringstream oss;
        oss << std::fixed << std::setprecision(6) << result;
        SetWindowText(hEditResult, oss.str().c_str());
    }
    catch (...) {
        MessageBox(hwnd, "Ошибка: проверьте введенные данные!", "Ошибка", MB_OK | MB_ICONERROR);
    }
}

void ClearFields() {
    SetWindowText(hEditBase, "");
    SetWindowText(hEditN, "");
    SetWindowText(hEditBase, "");

    SetWindowText(hEditResult, "");
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CREATE: {
            hLabelBase = CreateWindow(
                "STATIC", "base:",
                WS_VISIBLE | WS_CHILD | SS_LEFT,
                20, 20, 150, 20,
                hwnd, NULL, NULL, NULL);

            hLabelN = CreateWindow(
                "STATIC", "n:",
                WS_VISIBLE | WS_CHILD | SS_LEFT,
                20, 60, 150, 20,
                hwnd, NULL, NULL, NULL);

            hLabelResult = CreateWindow(
                "STATIC", "Result:",
                WS_VISIBLE | WS_CHILD | SS_LEFT,
                20, 100, 150, 20,
                hwnd, NULL, NULL, NULL);

            hEditBase = CreateWindow(
                "EDIT", "",
                WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LEFT,
                180, 18, 280, 25,
                hwnd, (HMENU)ID_EDIT_BASE, NULL, NULL);

            hEditN = CreateWindow(
                "EDIT", "",
                WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LEFT,
                180, 58, 280, 25,
                hwnd, (HMENU)ID_EDIT_N, NULL, NULL);

            hEditResult = CreateWindow(
                "EDIT", "",
                WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LEFT | ES_READONLY,
                180, 98, 280, 25,
                hwnd, (HMENU)ID_EDIT_RESULT, NULL, NULL);

            hBtnPower = CreateWindow(
                "BUTTON", "base^n",
                WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                20, 140, 220, 35,
                hwnd, (HMENU)ID_BTN_POWER, NULL, NULL);

            hBtnNRoot = CreateWindow(
                "BUTTON", "nRoot",
                WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                260, 140, 200, 35,
                hwnd, (HMENU)ID_BTN_NROOT, NULL, NULL);

            hBtnClear = CreateWindow(
                "BUTTON", "Clear",
                WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                20, 185, 440, 35,
                hwnd, (HMENU)ID_BTN_CLEAR, NULL, NULL);


            return 0;
        }

        case WM_COMMAND: {
            switch (LOWORD(wParam)) {
                case ID_BTN_POWER:
                    CalculatePower(hwnd);
                    break;
                case ID_BTN_NROOT:
                    CalculateNRoot(hwnd);
                    break;
                case ID_BTN_CLEAR:
                    ClearFields();
                    break;
            }
            return 0;
        }

        case WM_DESTROY:
            PostQuitMessage(0);
            if (hBrush) DeleteObject(hBrush);
            return 0;

        case WM_ACTIVATE:
            if (hBrush) DeleteObject(hBrush);
            hBrush = CreateSolidBrush(RGB(255, 255, 255));
            InvalidateRect(hwnd, NULL, TRUE);
            return 0;

        case WM_MOVE:
            if (hBrush) DeleteObject(hBrush);
            hBrush = CreateSolidBrush(RGB(255, 255, 255));
            InvalidateRect(hwnd, NULL, TRUE);
            return 0;

        case WM_RBUTTONDBLCLK:
            if (hBrush) DeleteObject(hBrush);
            hBrush = CreateSolidBrush(RGB(255, 255, 255));
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
    char windowTitle[] = "Calculator - 14-15";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(0);
    wc.lpszClassName = className;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

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