#include <iostream>
#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);
    DWORD pid = GetCurrentProcessId();

    HANDLE pseudoHandle = GetCurrentProcess();

    HANDLE duplicateHandle  = nullptr;
    BOOL dupResult = DuplicateHandle(
        pseudoHandle,
        pseudoHandle,
        pseudoHandle,
        &duplicateHandle,
        0,
        FALSE,
        DUPLICATE_SAME_ACCESS
        );

    if (!dupResult) {
        std::cerr << "Duplicate handle failed" << std::endl;
        return 1;
    }

    HANDLE openProcessHandle = OpenProcess(
        PROCESS_ALL_ACCESS,
        FALSE,
        pid
    );

    if (!openProcessHandle) {
        std::cerr << "OpenProcess failed" << std::endl;
        CloseHandle(openProcessHandle);
        return 1;
    }

    std::cout << "ID процесса: " << pid << std::endl;
    std::cout << "Псевдоскриптор: " << pseudoHandle << std::endl;
    std::cout << "DuplicateHandle: " << duplicateHandle << std::endl;
    std::cout << "OpenProcess: " << openProcessHandle << std::endl;

    CloseHandle(openProcessHandle);
    CloseHandle(duplicateHandle);

    std::cout << "Дескрипторы закрыты\n" << std::endl;

    return 0;
}