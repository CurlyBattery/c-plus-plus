#include <stdio.h>
#include <windows.h>

int main() {
    // получение имени компьютера
    char computerName[MAX_COMPUTERNAME_LENGTH  + 1];
    DWORD size = MAX_COMPUTERNAME_LENGTH + 1;

    if (GetComputerName(computerName, &size)) {
        printf("Computer name: %s\n", computerName);
    } else {
        printf("Error getting computer name\n");
    }

    // получение пути системных каталогов
    printf("Path system catalog: %s\n", getenv("TEMP"));

    // получение версии системы
    OSVERSIONINFO osvi;
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    GetVersionEx(&osvi);
    printf("Windows version: %d.%d (Build %d) \n", osvi.dwMajorVersion, osvi.dwMinorVersion, osvi.dwBuildNumber);

    return 0;
}