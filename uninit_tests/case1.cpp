#include <iostream>

void test_case_1(int input) {
    int a;
    if (input > 0) {
        a = 10;
    }
    // 'a' is uninitialized if input <= 0
    if (input > 5) {
        std::cout << a << std::endl; 
    }
}
