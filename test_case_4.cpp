// Positive Case 4: Member Initialization in Helper Method
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
