import os

cases = {
    "test_case_1.cpp": """// Positive Case 1: Correlated Constraints
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
""",
    "test_case_2.cpp": """// Positive Case 2: Loop with Flag
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
""",
    "test_case_3.cpp": """// Positive Case 3: Initialization by Reference
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
""",
    "test_case_4.cpp": """// Positive Case 4: Member Initialization in Helper Method
// 'value' is initialized in 'init()', called by constructor.
// Cppcheck often warns if member is not initialized in constructor body or list.
class MyClass {
    int value;
public:
    MyClass() {
        init();
    }
    void init() {
        value = 10;
    }
    int get() { return value; }
};

int test_case_4() {
    MyClass c;
    return c.get(); // Safe
}
""",
    "test_case_5.cpp": """// Positive Case 5: Goto Spaghetti
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
"""
}

for filename, content in cases.items():
    with open(filename, 'w') as f:
        f.write(content)
    print(f"Overwrote {filename}")
