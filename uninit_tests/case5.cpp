#include <iostream>

void test_case_5(int input) {
    int e;
    for (int j = 0; j < input + 1; ++j) {
        if (j == input) {
            e = j;
            break;
        }
    }
    // 'e' uninitialized if input is not in range [0, 9]
    std::cout << e << std::endl;
}
