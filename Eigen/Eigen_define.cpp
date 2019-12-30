#include <iostream>
#include <stdlib.h>
#include "eigen3/Eigen/Dense"

using namespace std;


int main()
{
    Eigen::MatrixXd m(2,2);             //声明一个MatrixXd类型的变量，它是2*2的矩阵，未初始化
    m(0,0) = 3;                         //将矩阵第1个元素初始化3
    m(1,0) = 2.5;                       //将矩阵第3个元素初始化2.5
    m(0,1) = -6;
    m(1,1) = m(1, 0) + m(0, 1);

    //    3   -6
    //  2.5 -3.5
    std::cout << m << std::endl;
    
    system("pause");
    return 0;
}

