// 验证循环内赋值
// 对于while循环，认为while循环体至少运行一次，循环体内对变量赋值时，跳过循环条件判断，认为initialized
int foo(int cond){
    int x;
    while(cond){
        x = 1;
    }
    return x;
} 