#include <iostream>
#include <windows.h>

using namespace std;

CRITICAL_SECTION cs;
int counter = 0;

DWORD WINAPI ThreadFunc(LPVOID) {
    for (int i = 0; i < 100000; i++) {
        EnterCriticalSection(&cs);
        counter++;
        LeaveCriticalSection(&cs);
    }
    return 0;
}

int main() {
    InitializeCriticalSection(&cs);

    HANDLE threads[4];
    for (int i = 0; i < 4; i++) {
        threads[i] = CreateThread(NULL, 0, ThreadFunc, NULL, 0, NULL);
    }

    WaitForMultipleObjects(4, threads, TRUE, INFINITE);

    cout << "Counter: " << counter << endl;

    DeleteCriticalSection(&cs);

    return 0;
}