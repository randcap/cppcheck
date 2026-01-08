#include <iostream>

void test_case_4(int input) {
    int d;
    if (input > 10) {
        if (input < 20) {
            d = 5;
        }
        else {
            d = 10;
        }
    } else {
        d = 1;
    }
    std::cout << d << std::endl;
}
