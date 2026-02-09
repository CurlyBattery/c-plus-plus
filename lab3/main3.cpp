#include <windows.h>
#include <iostream>

using namespace std;

HANDLE hEvent;

DWORD WINAPI WorkerThread(LPVOID) {
    Sleep(3000);
    SetEvent(hEvent);
    return 0;
}

int main() {
    hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

    CreateThread(NULL, 0, WorkerThread, NULL, 0, NULL);

    cout << "Waiting for event...\n";
    WaitForSingleObject(hEvent, INFINITE);
    cout << "Event received\n";

    CloseHandle(hEvent);
    return 0;
}