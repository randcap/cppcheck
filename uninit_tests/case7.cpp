#include <iostream>

void test_case_7(int input) {
    int g;
    int arr[5] = {0, 1, 0, 1, 0};
    // Initialization depends on the value inside the array
    if (arr[input % 5] == 0) {
        g = 1;
    }
    std::cout << g << std::endl;
}
