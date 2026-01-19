#include <windows.h>
#include <iostream>
#include <string>

class Database {
private:
    CRITICAL_SECTION cs;

public:
    Database() {
        InitializeCriticalSection(&cs);
    }

    ~Database() {
        DeleteCriticalSection(&cs);
    }

    void SaveData(const std::string& text) {
        EnterCriticalSection(&cs);

        std::cout << "[START] " << text << std::endl;

        for (int i = 1; i <= 5; i++) {
            std::cout << "  " << text << " -> saving data (step " << i << "/5)" << std::endl;
            Sleep(500);
        }

        std::cout << "[END] " << text << std::endl << std::endl;

        LeaveCriticalSection(&cs);
    }
};

Database db;

DWORD WINAPI WorkerThread1(LPVOID) {
    std::cout << ">>> Thread 1 started" << std::endl;
    db.SaveData("Thread 1");
    std::cout << ">>> Thread 1 finished" << std::endl << std::endl;
    return 0;
}

DWORD WINAPI WorkerThread2(LPVOID) {
    std::cout << ">>> Thread 2 started" << std::endl;
    db.SaveData("Thread 2");
    std::cout << ">>> Thread 2 finished" << std::endl << std::endl;
    return 0;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::cout << "Critical Section Demo" << std::endl;

    HANDLE hThread1 = CreateThread(nullptr, 0, WorkerThread1, nullptr, 0, nullptr);
    HANDLE hThread2 = CreateThread(nullptr, 0, WorkerThread2, nullptr, 0, nullptr);

    WaitForSingleObject(hThread1, INFINITE);
    WaitForSingleObject(hThread2, INFINITE);

    CloseHandle(hThread1);
    CloseHandle(hThread2);

    std::cout << "All threads completed" << std::endl;

    system("pause");
    return 0;
}