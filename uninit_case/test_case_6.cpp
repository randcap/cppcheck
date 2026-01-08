// Negative Case: Depth 2
int test_func(int val) {
    int x; // Not initialized at declaration
    for (int i1 = 0; i1 < 5; ++i1) {
        if (val == 999) x = 1; // Conditional assignment at depth 2
    }
    return x;
}
