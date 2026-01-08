// Positive Case: Depth 2
int test_func(int val) {
    int x = 0; // Initialized at declaration
    for (int i1 = 0; i1 < 5; ++i1) {
        x = 1; // Assignment at depth 2
    }
    return x;
}
