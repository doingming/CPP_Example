#include <iostream>
#include <stdlib.h>
#include "eigen3/Eigen/Dense"

using namespace std;



using namespace Eigen;

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



    
    Matrix<double, Dynamic, Dynamic> C;

    C.resize(3,3);
    C << 11,12,13,
        17,18,19,
         14,15,16;


    // Eigen::Matrix<double, 3, 1> jv;     // 3行1列
    Eigen::VectorXd jv(3);           //ff 和上行效果一样

    Eigen::ArrayXd vo(6);
    vo << 1, 2, 3, 4, 5, 6;
    // jv << 11,12,13;          // 必须先指定大小 Eigen::VectorXd jv(3)
    jv = MatrixXd::Zero(3,1);   // 可以定义是不指定大小 Eigen::VectorXd jv;
    std::cout << "jvjvjvjv=" << std::endl << jv << std::endl << std::endl;
    std::cout << "vovovovo=" << std::endl << vo << std::endl << std::endl;

    vo.segment(0,3) = jv;         // 只对 vo 前三个元素赋值
    std::cout << "after 'vo.segment(1,4) *= 2', vo =" << std::endl << vo << std::endl;


    jv = C.diagonal(); 
    std::cout << "jvjvjv--jv=" << std::endl << jv << std::endl << std::endl;



    system("pause");
    return 0;
}

