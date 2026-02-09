#include <windows.h>
#include <fstream>


int main() {
    HANDLE hMutex = CreateMutex(NULL, FALSE,  "MyGlobalMutex");

    WaitForSingleObject(hMutex, INFINITE);

    std::ofstream file("log.txt", std::ios::app);
    file << "Process " << GetCurrentProcessId() << " " << " wrote this line\n" << std::endl;
    file.close();

    ReleaseMutex(hMutex);
    CloseHandle(hMutex);

    return 0;
}