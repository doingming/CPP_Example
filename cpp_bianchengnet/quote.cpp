/* 引用 */

#include <iostream>
#include <stdlib.h>

int &plus_ten(int &n){  //引用作为函数返回值
    n = n + 10;
    return n;
}

int main() {
    int a = 99;
    int &aa = a;
    int b = 33;

    std::cout << a << ", " << aa << std::endl;//引用可以看做是数据的一个别名
    std::cout << &a << ", " << &aa << std::endl;//通过这个别名和原来的名称都能够找到这份数据

    aa = 78;
    std::cout << a << ", " << aa << std::endl;
    
    a += 3;
    b = plus_ten(aa);
    std::cout << b << " b +10" << std::endl;

    system("pause");
    return 0;
}