#include <windows.h>
#include <iostream>

int main()
{
    DWORD pid = GetCurrentProcessId();
    HANDLE pseudo = GetCurrentProcess();

    HANDLE real1 = NULL;
    DuplicateHandle(
        pseudo,
        pseudo,
        pseudo,
        &real1,
        0,
        FALSE,
        DUPLICATE_SAME_ACCESS
    );

    HANDLE real2 = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

    std::cout << "Process ID: " << pid << std::endl;
    std::cout << "Pseudo handle: " << pseudo << std::endl;
    std::cout << "DuplicateHandle: " << real1 << std::endl;
    std::cout << "OpenProcess: " << real2 << std::endl;

    CloseHandle(real2);
    CloseHandle(real1);

    return 0;
}
