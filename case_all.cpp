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
    return y;
}//不会报uninitialized，因为两个if语句是独立的，cppcheck认为至少有一个会执行，从而保证x被初始化。


int foo_while(int cond){
    int x;
    while(cond){
        x = 1;
    }
    return x;
} //不会报uninitialized，认为while循环体至少运行一次。

int foo_for(int cond){
    int x;
    for(int i = x;cond;){
        x = 1;
    }
    return x;
}// 不会报uninitialized，认为for循环体至少运行一次。

int foo_for2(int cond){
    int x;
    for(int i = x;cond;){
        // x = 1;
    }
    return 0;
}// 报uninitialized，当循环体内没有赋值时检查for条件中第一个分号前的语句。