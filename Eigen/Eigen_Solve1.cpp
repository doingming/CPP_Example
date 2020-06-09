// Eigen学习之简单线性方程与矩阵分解


#include <iostream>
#include <eigen3/Eigen/Dense>

using namespace std;
using namespace Eigen;


 
/****************************
* 本程序演示了 Eigen 基本类型的使用   和   ldlt llt 分解法
****************************/

#define MATRIX_SIZE 100

int main()
{
    // 解方程
    // 我们求解 A * x = b 这个方程
    // 直接求逆自然是最直接的，但是求逆运算量大
    // 解线性方程的计算方法，也包括LU分解法，QR分解法   解这类方程 Ax = b

    Matrix3f Ab;
    Vector3f ba;
    Ab << 1,2,3, 4,5,6, 7,8,10;
    ba << 3,3,4;
    cout<<"Here is the Matrix A:\n"<< Ab <<endl;
    cout<<" Here is the vector b:\n"<< ba <<endl;


    // 直接求逆
    Vector3f xx = Ab.inverse()*ba;              // Ab.inverse() 矩阵求逆
    cout <<"use normal inverse is " << endl;
    cout<<xx<<endl;


    // *放到 GITHUB\CPP_Example\Eigen\Eigen_quickReference.cpp 中运行调试会报错。
    Vector3f xxx = Ab.colPivHouseholderQr().solve(ba);
    cout<<"colPivHouseholderQr() The solution is:\n"<<xxx<<endl;

    xxx = Ab.fullPivHouseholderQr().solve(ba);
    cout<<"fullPivHouseholderQr() The solution is:\n"<<xxx<<endl;


    // lu分解法
    xxx = Ab.lu()  .solve(ba);
    cout<<"The solution is:\n"<<xxx<<endl;

    xxx = Ab.partialPivLu().solve(ba);
    cout<<"The solution is:\n"<<xxx<<endl;

    xxx = Ab.fullPivLu().solve(ba);
    cout<<"The solution is:\n"<<xxx<<endl;


    // --------------------------------------------分割线--------------------------------------

    // Eigen也可以解决矩阵相乘的问题   ldlt LDLT分解法     要求矩阵A正或负半定

    // Matrix3f A,b;
    // A << 2,-1,-1,6,7,7,9,10,2;
    // b << 1,2,3,1,1,2,1,1,1;
    // cout<<"Here is the matrix A:\n"<<A<<endl;
    // cout<<"Here is the right hand side b:\n"<<b<<endl;
    // Matrix3f x = A.ldlt().solve(b);
    // cout<<"The solution is:\n"<<x<<endl;

    Matrix2f A,b;
    A << 2,-1,-1,3;
    b << 1,2,3,1;
    cout<<"Here is the matrix A:\n"<<A<<endl;
    cout<<"Here is the right hand side b:\n"<<b<<endl;
    Matrix2f x = A.ldlt().solve(b);
    cout<<"The solution is:\n"<<x<<endl;

    
    // llt  LLT分解法      要求矩阵A正定
    Eigen::Matrix3f down;
    down<< 2,-1,-1,6,7,7,9,10,2;

    Eigen::Matrix3f P=down*down.transpose();
    std::cout<<"P"<<P<<std::endl;
    Eigen::Matrix3f ml=P.llt().matrixL();
    Eigen::Matrix3f testP=ml*ml.transpose();
    std::cout<<"mllt"<<std::endl<<ml<<std::endl;
    std::cout<<"testP"<<std::endl<<testP<<std::endl;




    system("pause");
    return 0;
}