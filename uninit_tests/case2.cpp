#include <iostream>

void test_case_2(int input) {
    int b;
    int i = 0;
    // If input <= 0, the loop is skipped entirely
    while (i < input) {
        b = i * 2;
        i++;
    }
    std::cout << b << std::endl;
}
