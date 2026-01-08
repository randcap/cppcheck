// Positive Case 5: Goto Spaghetti
// 'x' is initialized in both paths (n > 0 and n <= 0).
int test_case_5(int n) {
    int x;
    if (n > 0) goto label_init;
    x = 2;
    goto label_end;

label_init:
    x = 1;

label_end:
    return x; // Safe
}
