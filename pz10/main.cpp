#include <iostream>
#include <windows.h>
#include <iomanip>

void PrintLastError(const char* msg) {
    DWORD error = GetLastError();
    LPSTR buffer = nullptr;

    FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
        NULL,
        error,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPSTR)&buffer,
        0,
        NULL
    );

    std::cerr << msg << std::endl;
    std::cerr << "Код ошибки: " << error << std::endl;
    if (buffer) {
        std::cerr << "Описание: " << buffer << std::endl;
        LocalFree(buffer);
    }
}



int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    SYSTEM_INFO si;
    GetSystemInfo(&si);
    SIZE_T pageSize = si.dwPageSize;

    std::cout << "Размер страницы: " << pageSize << " байт\n\n";

    LPVOID mem = VirtualAlloc(
        nullptr,
        pageSize,
        MEM_RESERVE | MEM_COMMIT,
        PAGE_READWRITE
    );

    if (!mem) {
        PrintLastError("Ошибка VirtualAlloc");
        return 1;
    }

    std::cout << "Память выделена по адресу: " << mem << std::endl;

    memset(mem, 0x11, pageSize);
    std::cout << "Память заполнена значением 0x11\n";

    std::cout << "IsBadReadPtr (до VirtualProtect): "
              << IsBadReadPtr(mem, pageSize) << std::endl;

    DWORD oldProtect;
    if (!VirtualProtect(mem, pageSize, PAGE_NOACCESS, &oldProtect)) {
        PrintLastError("Ошибка VirtualProtect (PAGE_NOACCESS)");
        VirtualFree(mem, 0, MEM_RELEASE);
        return 1;
    }

    std::cout << "Защита изменена на PAGE_NOACCESS\n";

    std::cout << "IsBadReadPtr (после PAGE_NOACCESS): "
              << IsBadReadPtr(mem, pageSize) << std::endl;

    if (!VirtualProtect(mem, pageSize, oldProtect, &oldProtect)) {
        PrintLastError("Ошибка VirtualProtect (возврат защиты)");
        VirtualFree(mem, 0, MEM_RELEASE);
        return 1;
    }

    std::cout << "Защита восстановлена\n";

    std::cout << "IsBadReadPtr (после восстановления): "
              << IsBadReadPtr(mem, pageSize) << std::endl;

    if (!VirtualFree(mem, 0, MEM_RELEASE)) {
        PrintLastError("Ошибка VirtualFree");
        return 1;
    }

    std::cout << "\nПамять успешно освобождена\n";
    return 0;
}