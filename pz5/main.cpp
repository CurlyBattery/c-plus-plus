#include <iostream>
#include <windows.h>

HANDLE hThread1, hThread2;

CRITICAL_SECTION cs;

volatile double currentValue = 0.0;
volatile bool terminateAll = false;

const double PAUSE_THRESHOLD  = 100.0;
const double CRITICAL_VALUE = 1000.0;

DWORD WINAPI Thread2_Generator(LPVOID) {
    double value  = 1.0;
    double ratio =  1.5;
    int step = 0;

    std::cout << "Thread2 started: generating geometric progression" << std::endl;

    while (true) {
        EnterCriticalSection(&cs);
        currentValue = value;
        LeaveCriticalSection(&cs);

        step++;
        std::cout << "[Thread2] step " << step << ": value = " << value << std::endl;

        if (value >= CRITICAL_VALUE) {
            std::cout << "[Thread2] CRITICAL_VALUE reached" << std::endl;
            break;
        }

        value *= ratio;
        Sleep(800);
    }

    std::cout << "[Thread2] finished" << std::endl;
    return 0;
}

DWORD WINAPI Thread1_Generator(LPVOID) {
    std::cout << "Thread1 started: monitoring Thread2" << std::endl;

    bool paused = false;

    while (!terminateAll) {
        double value;

        EnterCriticalSection(&cs);
        value = currentValue;
        LeaveCriticalSection(&cs);

        std::cout << "[Thread1] read value " << value << std::endl;

        if (value >= PAUSE_THRESHOLD && !paused && value < CRITICAL_VALUE) {
            std::cout << "[Thread1] pushing Thread2" << std::endl;
            SuspendThread(hThread2);
            paused = true;

            Sleep(3000);

            std::cout << "[Thread1] resuming Thread2" << std::endl;
            ResumeThread(hThread2);
        }

        if (value >= CRITICAL_VALUE) {
            std::cout << "[Thread1] EMERGENCY TERMINATION" << std::endl;
            TerminateThread(hThread2, 0);
            terminateAll = true;
            break;
        }

        Sleep(1000);
    }

    std::cout << "[Thread1] finished" << std::endl;
    return 0;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    InitializeCriticalSection(&cs);

    hThread2 = CreateThread(
        nullptr,
        0,
        Thread2_Generator,
        nullptr,
        0,
        nullptr
        );
    hThread1 = CreateThread(
        nullptr,
        0,
        Thread1_Generator,
        nullptr,
        0,
        nullptr
        );

    WaitForSingleObject(hThread1, INFINITE);
    WaitForSingleObject(hThread2, INFINITE);

    DeleteCriticalSection(&cs);

    CloseHandle(hThread1);
    CloseHandle(hThread2);

    std::cout << "Program finished" << std::endl;
    return 0;
}