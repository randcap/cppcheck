#include <iostream>

void test_case_8(int input) {
    int h;
    auto helper = [](int& val, int flag) {
        if (flag) val = 1;
    };
    // 'h' only initialized if input > 0
    helper(h, input > 0); 
    std::cout << h << std::endl;
}
