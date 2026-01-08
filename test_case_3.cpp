// Positive Case 3: Initialization by Reference
// 'x' is initialized inside the helper function.
// Static analysis needs inter-procedural analysis to catch this.
void init_val(int &v) {
    v = 42;
}

int test_case_3() {
    int x;
    init_val(x);
    return x; // Safe
}
