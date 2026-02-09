#include <windows.h>
#include <iostream>

void GetModuleInfo(HMODULE hModule)
{
    char path[MAX_PATH];
    char name[MAX_PATH];

    GetModuleFileNameA(hModule, path, MAX_PATH);

    char* p = strrchr(path, '\\');
    strcpy_s(name, p ? p + 1 : path);

    std::cout << "Handle: " << hModule << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Full name: " << path << std::endl;
}

int main()
{
    GetModuleInfo(GetModuleHandle(NULL));

    GetModuleInfo(GetModuleHandleA("user32.dll"));

    return 0;
}
