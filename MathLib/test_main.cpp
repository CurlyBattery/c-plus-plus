#include "library.h"
#include <iostream>
#include <windows.h>

using namespace std;

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    cout << "2^3 = " << power(2, 3) << " (ожидается 8)" << endl;

    cout << "√16 = " << nroot(16, 2) << " (ожидается 4)" << endl;

    return 0;
}

