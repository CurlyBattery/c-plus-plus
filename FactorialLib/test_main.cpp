#include "library.h"
#include <iostream>
#include <windows.h>

using namespace std;

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    cout << "Факториал 5: " << factorial(5) << " (ожидается 120)" << endl;

    return 0;
}
