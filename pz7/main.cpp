#include <iostream>
#include <windows.h>

DWORD WINAPI Worker1(LPVOID) {
    while (true) {
        Sleep(1000);
    }
}

DWORD WINAPI Worker2(LPVOID) {
    while (true) {
        Sleep(1000);
    }
}

DWORD WINAPI Worker3(LPVOID) {
    while (true) {
        Sleep(1000);
    }
}

int main() {
    HANDLE t1 = CreateThread(nullptr, 0, Worker1, nullptr, 0, nullptr);
    HANDLE t2 = CreateThread(nullptr, 0, Worker2, nullptr, 0, nullptr);
    HANDLE t3 = CreateThread(nullptr, 0, Worker3, nullptr, 0, nullptr);

    std::cout << "Process running. Attach VMMap\n";

    HANDLE hHeap = HeapCreate(
    0,
    50 * 1024 * 1024, // 50 MB
    0
);

    void* mem = HeapAlloc(
        hHeap,
        0,
        30 * 1024 * 1024 // 30 MB
    );
    std::cin.get();

    return 0;
}