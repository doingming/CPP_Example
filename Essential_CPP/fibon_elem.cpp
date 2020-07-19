#include <iostream>
#include <stdlib.h>
#include <vector>

// 使用已初始化的数组 elem_vals 来初始化vector容器对象 elem_seq 。
// P79


int main(){

    const int seq_size = 5;


    int ia[8] = {1,2,3,4,5,6,7,21};     //array
    std::vector< int > fib(ia, ia+8);   //vector

    int elem_vals[seq_size] = { 32,33,34,45,47};                //array
    std::vector<int> elem_seq(elem_vals, elem_vals+seq_size);   //利用一个已初始化的array作为该vector的初值
    

    int *pvals = elem_vals;                 //数组指针
    std::vector<int> *pseq = &elem_seq;     //vector指针
    pseq = &elem_seq;
    std::cout << (*pseq)[3] << std::endl;
    std::cout << pvals[2] << std::endl;
    
    std::cout << fib[0] << std::endl;
    std::cout << fib[1] << std::endl;
    std::cout << fib[2] << std::endl;
    std::cout << fib[3] << std::endl;
    std::cout << fib[4] << std::endl;
    std::cout << fib[5] << std::endl;
    std::cout << fib[6] << std::endl;

    system("pause");
    return 0;
}