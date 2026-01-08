// Positive Case: Depth 10
int test_func(int val) {
    int x = 0; // Initialized at declaration
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
                                        x = 1; // Assignment at depth 10
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
