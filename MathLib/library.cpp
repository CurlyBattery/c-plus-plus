#include "library.h"
#include <cmath>

double power(double base, int n) {
    double result = 1.0;
    for (int i = 0; i < n; i++) {
        result *= base;
    }

    return result;
}

double nroot(double value, int n) {
    if (n == 0) return 0.0;
    return pow(value, 1.0 / n);
}