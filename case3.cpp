// 对于for循环，循环体内对变量赋值时，直接认为inited，如果循环体内没有赋值，检查for循环的第一个分号前是否有赋值或者引用
int foo(int cond){
    int x;
    for(int i = x;cond;){
        // x = 1;
    }
    return x;
}
