#include <iostream>
#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);

    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);

    if(!GlobalMemoryStatusEx(&memInfo)) {
        std::cerr << "Error GlobalMemoryStatusEx\n";
        return 1;
    }

    std::cout << "Процент используемой памяти: " << memInfo.dwMemoryLoad << "%\n\n";

    std::cout << "Физическая память (всего): " << memInfo.ullTotalPhys / (1024 * 1024) << "MB\n\n";

    std::cout << "Физическая память (доступно): " << memInfo.ullAvailPhys / (1024 * 1024) << "MB\n\n";

    std::cout << "Файл подкачки (всего): " << memInfo.ullTotalPageFile / (1024 * 1024) << "MB\n\n";

    std::cout << "Файл подкачки (доступно): " << memInfo.ullAvailPageFile / (1024 * 1024) << "MB\n\n";

    std::cout << "Виртуальная память (всего): " << memInfo.ullTotalVirtual / (1024 * 1024) << "MB\n\n";

    std::cout << "Виртуальная память (доступно): " << memInfo.ullAvailVirtual / (1024 * 1024) << "MB\n\n";

    unsigned long long usedPhys  = memInfo.ullTotalPhys - memInfo.ullAvailPhys;

    std::cout << "Используемая физическая память процессорами: " << usedPhys / (1024 * 1024) << " MB\n\n";

    return 0;
}