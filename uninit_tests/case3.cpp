#include <iostream>

void test_case_3(int input) {
    int c;
    switch (input) {
        case 1:
            c = 100;
            break;
        case 2:
            c = 200;
            break;
        default:
            c = input;
            break;
    }
    std::cout << c << std::endl;
}
