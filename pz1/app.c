#include <stdio.h>

extern int x;
void func1(void);

int y = 20;

void func2() {
    printf("func2: y=%d\n", y);
}

int z = 30;

void func3() {
    func1();
    printf("print3: x=%d \t y=%d z=%d\n", x, y, z);
}