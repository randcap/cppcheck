### ECNU软件分析与验证前沿-cppcheck工具调研与使用
- 案例文件目录： \
cppcheck/case1.cpp \
cppcheck/case2.cpp \
cppcheck/case3.cpp \
cppcheck/uninit_test/ 
- 案例检测结果统计: \
cppcheck/uninit_test/comparison_table.txt 
- 补充说明:\
本仓库中的cppcheck.exe是注释掉uninitValueflow方法后重新编译的。\
同时还借助AI实现了一个好像没什么用的小功能，对于uninitValueflow方法，程序中有语句y=x，当x是uninit时，y也会报uninit了，也即uninit的状态可以传递了。（但是组长说只需要检测到最开头的uninitvar，也即定位到根源就行，所以这个功能没有放在报告中。仔细思考好像确实没用）
