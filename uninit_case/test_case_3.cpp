// Positive Case: Depth 30
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
                                        for (int i10 = 0; i10 < 5; ++i10) {
                                            while (val < 111) {
                                                val++;
                                                if (val > 12) {
                                                    for (int i13 = 0; i13 < 5; ++i13) {
                                                        while (val < 114) {
                                                            val++;
                                                            if (val > 15) {
                                                                for (int i16 = 0; i16 < 5; ++i16) {
                                                                    while (val < 117) {
                                                                        val++;
                                                                        if (val > 18) {
                                                                            for (int i19 = 0; i19 < 5; ++i19) {
                                                                                while (val < 120) {
                                                                                    val++;
                                                                                    if (val > 21) {
                                                                                        for (int i22 = 0; i22 < 5; ++i22) {
                                                                                            while (val < 123) {
                                                                                                val++;
                                                                                                if (val > 24) {
                                                                                                    for (int i25 = 0; i25 < 5; ++i25) {
                                                                                                        while (val < 126) {
                                                                                                            val++;
                                                                                                            if (val > 27) {
                                                                                                                for (int i28 = 0; i28 < 5; ++i28) {
                                                                                                                    while (val < 129) {
                                                                                                                        val++;
                                                                                                                        x = 1; // Assignment at depth 30
                                                                                                                    }
                                                                                                                }
                                                                                                            }
                                                                                                        }
                                                                                                    }
                                                                                                }
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
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
