// Positive Case 2: Loop with Flag
// 'val' is initialized only if 'found' is true.
// We return 'val' only if 'found' is true.
int test_case_2(int n) {
    int val;
    bool found = false;
    for (int i = 0; i < n; ++i) {
        if (i == 10) {
            val = 100;
            found = true;
            break;
        }
    }
    
    if (found) {
        return val; // Safe
    }
    return 0;
}
