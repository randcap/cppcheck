#include <iostream>

void test_case_10(int input) {
    int m;
    if (false) {
        m = 5; // This line is dead code
    }
    // 'm' is definitely uninitialized here
    std::cout << m << std::endl;
}
