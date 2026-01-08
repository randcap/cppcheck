#include <iostream>

void test_case_6(int input) {
    int f;
    if (input == 42) goto skip_init;
    f = 10;
skip_init:
    // 'f' uninitialized if input == 42
    std::cout << f << std::endl;
}
