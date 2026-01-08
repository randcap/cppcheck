// Negative Case: Depth 10
int test_func(int val) {
    int x; // Not initialized at declaration
    for (int i1 = 0; i1 < 5; ++i1) {
        while (val < 102) {
            val++;
            if (val > 3) {
                for (int i4 = 0; i4 < 5; ++i4) {
                    while (val < 105) {
                        val++;
                        if (val > 6) {
                            for (int i7 = 0; i7 < 5; ++i7) {
                                while (val < 108) {
                                    val++;
                                    if (val > 9) {
                                        if (val == 999) x = 1; // Conditional assignment at depth 10
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return x;
}
