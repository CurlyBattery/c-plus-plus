#include <iostream>
#include <windows.h>
#include <iomanip>
#include <string>

using namespace std;

string DWORDToRGB(DWORD color) {
    int red = GetRValue(color);
    int green = GetGValue(color);
    int blue = GetBValue(color);
    char buffer[50];
    sprintf(buffer, "RGB(%d, %d, %d)", red, green, blue);
    return string(buffer);
}

string GetPlatformName(DWORD platformId) {
    switch(platformId) {
        case VER_PLATFORM_WIN32s: return "Win32s";
        case VER_PLATFORM_WIN32_WINDOWS: return "Windows 95/98/ME";
        case VER_PLATFORM_WIN32_NT: return "Windows NT";
        default: return "Unknown";
    }
}

int main() {
    char computerName[256];
    DWORD size = sizeof(computerName);
    GetComputerName(computerName, &size);
    cout << "Name computer " << computerName << endl;

    char userName[256];
    size = sizeof(userName);
    GetUserName(userName, &size);
    cout << "User name " << userName << endl;

    char windowsDir[256];
    GetWindowsDirectory(windowsDir, sizeof(windowsDir));
    cout << "Windows catalog " << windowsDir << endl;

    char systemDir[256];
    GetSystemDirectory(systemDir, sizeof(systemDir));
    cout << "System catalog " << systemDir << endl;

    char tempPath[256];
    GetTempPath(256, tempPath);
    cout << "Temp path " << tempPath << endl;

    OSVERSIONINFO osvi;
    ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    GetVersionEx(&osvi);

    cout << "Version OS " << osvi.dwMajorVersion << "." << osvi.dwMinorVersion << endl;
    cout << "Build " << osvi.dwBuildNumber << endl;
    cout << "Platform " << GetPlatformName(osvi.dwPlatformId) << endl;
    cout << "Service pack " << osvi.szCSDVersion << endl;

    cout << "Разрешение экрана: " << GetSystemMetrics(SM_CXSCREEN) << "x" << endl;
    cout << "Кнопок мыши: " << GetSystemMetrics(SM_MOUSEWHEELPRESENT) << endl;
    cout << "Колесо прокрутки: " << GetSystemMetrics(SM_CYCAPTION) << endl;

    BOOL beep;
    SystemParametersInfo(SPI_GETBEEP, 0, &beep, 0);
    cout << "Звуковые сигналы: " << (beep ? "Да" : "Нет") << endl;

    BOOL dragFullWindows;
    SystemParametersInfo(SPI_GETDRAGFULLWINDOWS, 0, &dragFullWindows, 0);
    cout << "Перетаскивание с содержимым: " << (dragFullWindows ? "Да" : "Нет") << endl;

    cout << "Цвет активного заголовка: " << DWORDToRGB(GetSysColor(COLOR_ACTIVECAPTION)) << endl;
    cout << "Цвет кнопки: " << DWORDToRGB(GetSysColor(COLOR_BTNFACE)) << endl;
    cout << "Цвет фона окна: " << DWORDToRGB(GetSysColor(COLOR_WINDOW)) << endl << endl;

    SYSTEMTIME localTime;
    GetLocalTime(&localTime);
    cout << "Местное время: " << setfill('0') << setw(2) << localTime.wHour << ":" << setw(2) << localTime.wMinute << ":" << setw(2) << localTime.wSecond << endl;
    cout << "Дата: " << setw(2) << localTime.wDay << "." << setw(2) << localTime.wMonth << "." << localTime.wYear << endl;

    POINT cursorPos;
    if (GetCursorPos(&cursorPos)) {
        cout << "Позиция курсора: X=" << cursorPos.x << ", Y=" << cursorPos.y << endl;
    }

    int kbType = GetKeyboardType(0);
    cout << "Тип клавиатуры: " << kbType << endl;


    return 0;
}