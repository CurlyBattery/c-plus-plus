#include <windows.h>
#include <tlhelp32.h>
#include <iostream>

int main()
{
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    PROCESSENTRY32 pe;
    pe.dwSize = sizeof(pe);

    if (Process32First(snap, &pe))
    {
        do {
            std::wcout << L"PID: " << pe.th32ProcessID
                       << L" | Threads: " << pe.cntThreads
                       << L" | EXE: " << pe.szExeFile << std::endl;
        } while (Process32Next(snap, &pe));
    }

    CloseHandle(snap);
    return 0;
}
