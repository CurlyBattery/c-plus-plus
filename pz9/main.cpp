#include <windows.h>
#include <iostream>
#include <iomanip>

using namespace std;

const char* GetStateString(DWORD state) {
    switch (state) {
        case MEM_COMMIT: return "MEM_COMMIT";
        case MEM_RESERVE: return "MEM_RESERVE";
        case MEM_FREE: return "MEM_FREE";
        default: return "UNKNOWN";
    }
}

const char* GetProtectString(DWORD protect) {
    switch (protect) {
        case PAGE_NOACCESS: return "PAGE_NOACCESS";
        case PAGE_READONLY: return "PAGE_READONLY";
        case PAGE_READWRITE: return "PAGE_READWRITE";
        case PAGE_WRITECOPY: return "PAGE_WRITECOPY";
        case PAGE_EXECUTE: return "PAGE_EXECUTE";
        case PAGE_EXECUTE_READ: return "PAGE_EXECUTE_READ";
        case PAGE_EXECUTE_READWRITE: return "PAGE_EXECUTE_READWRITE";
        case PAGE_EXECUTE_WRITECOPY: return "PAGE_EXECUTE_WRITECOPY";
        default: return "UNKNOWN";
    }
}

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    SYSTEM_INFO si;
    GetSystemInfo(&si);
    DWORD pageSize = si.dwPageSize;

    cout << "Page size: " << pageSize << endl;

    LPVOID pReserved = VirtualAlloc(NULL, pageSize, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

    if (pReserved == NULL) {
        cerr << "Ошибка VirtualAlloc" << endl;
        return 1;
    }

    cout << "Memory successfully acllocated at address: " << pReserved << endl;

    memset(pReserved, 0x7F, pageSize);
    cout << "Memory filled with value 0x7F\n\n";

    MEMORY_BASIC_INFORMATION mbi;
    SIZE_T result = VirtualQuery(
        pReserved,
        &mbi,
        sizeof(mbi)
    );

    if (result == 0) {
        cerr << "Ошибка VirtualQuery" << endl;
        VirtualFree(pReserved, 0, MEM_RELEASE);
        return 1;
    }

    cout << "Memory region information" << endl;

    cout << "Base address:    0x" << hex << uppercase << setw(16)
    << setfill('0') << (ULONG_PTR)mbi.BaseAddress << dec << endl;

    cout << "AllocationProtect: " << GetProtectString(mbi.AllocationProtect)
    << " (0x" << hex << mbi.AllocationProtect << dec << ")" << endl;

    cout << "Region Size:       " << mbi.RegionSize << "bytes" << endl;


    cout << "State:     " << GetStateString(mbi.State) << endl;

    cout << "Additional information" << endl;

    cout << "AllocationBase:    0x" << hex << uppercase << setw(16)
    << setfill('0') << (ULONG_PTR)mbi.AllocationBase << dec << endl;

    cout << "Protect:    " << GetProtectString(mbi.Protect) << endl;

    cout << "Type";
    switch (mbi.Type) {
        case MEM_IMAGE: cout << "MEM_IMAGE"; break;
        case MEM_MAPPED: cout << "MEM_MAPPED"; break;
        case MEM_PRIVATE: cout << "MEM_PRIVATE"; break;
        default: cout << "UNKNOWN"; break;
    }

    cout << "Проверка сожержимого памяти" << endl;
    BYTE* pByte = (BYTE*)pReserved;
    cout << "Первые 16 байт памяьт: ";
    for (int i = 0; i < 16; i++) {
        cout << hex << uppercase << setw(2) << setfill('0') << (int)pByte[i] << " ";
    }
    cout << dec << endl;

    if (!VirtualFree(pReserved, 0, MEM_RELEASE)) {
        cerr << "Ошибка VirtualFree" << endl;
        return 1;
    }

    cout << "\nПамять успещно освобождена" << endl;


    return 0;
}