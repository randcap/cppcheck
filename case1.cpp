int one_if(int cond) {
    int x;
    int y;
    if (cond) {
        x = 1;
    }
    y = x;
    return y; // cond==0 路径未初始化
} //会报uninitialized

int double_if(int cond1, int cond2) {
    int x;
    int y;
    if (cond1) {
        x = 1;
    }
    if (cond2) {
        x = 1;
    }
    y = x;
    return y; // cond1==0 && cond2==1 路径未初始化
} //不会报uninitialized，因为两个if语句是独立的，cppcheck认为至少有一个会执行，从而保证x被初始化。




//补充：
//此段代码中cppcheck不会报y未被初始化，尽管cond有可能为0，因为y的值依赖于x，而x在某些路径上可能未被初始化。
//问题分析，当y=x语句出现时，cppcheck默认y被初始化，因为它没有追踪x的未初始化状态传递给y。
//Cppcheck 没有完整追踪未初始化值的传播链。它主要检测直接使用未初始化变量，但对于 y = x（x 未初始化）这种情况，可能只报告 x 的问题，而不会继续追踪 y。
//改进建议：增强对未初始化值传播的追踪能力，使其能够识别通过赋值传递的未初始化状态。例如，在检测到 x 未初始化后，继续检查所有使用 x 的变量（如 y），并标记它们为潜在未初始化。
//todo 在 valueflow.cpp 中，当检测到 y = x 且 x 有 UninitValue 时，应该给 y 也添加 UninitValue 标记