#include <windows.h>
#include <iostream>
#include <string>

using namespace std;

void PrintRegistryString(HKEY hKey, const char* valueName) {
    DWORD dataSize = 0;
    DWORD type = 0;

    if (RegQueryValueExA(hKey, valueName, NULL, &type, NULL, &dataSize) == ERROR_SUCCESS) {
        if (dataSize > 0) {
            char* buffer = new char[dataSize];
            if (RegQueryValueExA(hKey, valueName, NULL, &type, (LPBYTE)buffer, &dataSize) == ERROR_SUCCESS) {
                cout << buffer;
            }
            delete[] buffer;
        }
    }
}

void GetOSInfo() {
    HKEY hKey;
    cout << "OS Info" << endl;

    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
        cout << "Product: ";
        PrintRegistryString(hKey, "ProductName");
        cout << endl;

        cout << "Edition: ";
        PrintRegistryString(hKey, "EditionID");
        cout << endl;

        cout << "Build: ";
        PrintRegistryString(hKey, "CurrentBuild");
        cout << endl;

        cout << "System Folder: ";
        PrintRegistryString(hKey, "SystemRoot");
        cout << endl;

        RegCloseKey(hKey);
    }
}

void GetBiosInfo() {
    HKEY hKey;
    cout << "Bios Info" << endl;

    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\BIOS", 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
        cout << "Bios Vendor: ";
        PrintRegistryString(hKey, "BIOSVendor");
        cout << endl;

        cout << "Bios Version: ";
        PrintRegistryString(hKey, "BIOSVersion");
        cout << endl;

        cout << "Manufacturer: ";
        PrintRegistryString(hKey, "SystemManufacturer");
        cout << endl;

        RegCloseKey(hKey);
    }
}

void GetAutoStartApps() {
    HKEY hKey;
    cout << "AutoStart" << endl;

    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_READ, &hKey) == ERROR_SUCCESS) {

        DWORD index = 0;
        char valueName[256];
        DWORD valueNameSize;
        char valueData[1024];
        DWORD valueDataSize;
        DWORD type;

        while (true) {
            valueNameSize = sizeof(valueName);
            valueDataSize  = sizeof(valueData);

            LONG result = RegEnumValueA(hKey, index, valueName, &valueNameSize, NULL, &type, (LPBYTE)valueData, &valueDataSize);

            if (result == ERROR_NO_MORE_ITEMS) break;
            if (result == ERROR_SUCCESS) {
                cout << valueName << ": " << valueData << endl;
            }
            index++;
        }

        RegCloseKey(hKey);
    }
}

int main() {
    GetOSInfo();
    GetBiosInfo();
    GetAutoStartApps();

    return 0;
}