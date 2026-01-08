// Positive Case 1: Correlated Constraints
// 'ret' is initialized if a > 10. We return 'ret' only if b > 10.
// Since a == b, this is safe. Cppcheck might fail to track a == b.
int test_case_1(int x) {
    int ret;
    int a = x;
    int b = x;
    
    if (a > 10) {
        ret = 1;
    }
    
    if (b > 10) {
        return ret; // Safe
    }
    return 0;
}
