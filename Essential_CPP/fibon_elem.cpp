#include <iostream>
#include <stdlib.h>
#include <vector>

int main(){
    const int seq_size = 5;
    int elem_vals[seq_size] = { 32,33,34,45,47};//array
    std::vector<int> elem_seq(elem_vals, elem_vals+seq_size);//利用一个已初始化的array作为该vector的初值

    int *pvals = elem_vals;//数组指针
    std::vector<int> *pseq = &elem_seq;//vector指针
    pseq = &elem_seq;
    std::cout << (*pseq)[3] << std::endl;
    std::cout << pvals[2] << std::endl;
    
    system("pause");
    return 0;
}