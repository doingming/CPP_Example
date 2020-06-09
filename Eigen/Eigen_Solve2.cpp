// 逆矩阵  矩阵行列式  最小二乘


#include <iostream>
#include <eigen3/Eigen/Dense>

using namespace std;
using namespace Eigen;

int main()
{
    


// 计算特征值和特征向量的算法
    Matrix2f Aa;
    Aa << 1,2,2,3;
    cout<<"Here is the matrix A:\n"<<Aa<<endl;
    SelfAdjointEigenSolver<Matrix2f> eigensolver(Aa);
    if( eigensolver.info() != Success ) abort();
    cout<<" The eigenvalues of Aa are:\n"<<eigensolver.eigenvalues()<<endl;
    cout<<" Here is a matrix whose columns are eigenvectors of A\n"
        <<" corresponding to these eigenvalues:\n"
        <<eigensolver.eigenvectors()<<endl;


// 逆矩阵 和 矩阵行列式
// Eigen 也提供了求逆矩阵和求矩阵行列式的算法，但是这两种算法对于大型矩阵来说都是非常不经济的算法，当需要对大型矩阵做这种的操作时，需要自己判断到底需不需这样做。但是对于小型矩阵 则可以没有顾虑地使用.
    Matrix3f Ac;
    Ac << 1,2,1,
         2,1,0,
         -1,1,2;

    cout<<"Here is the matrix Ac:\n"<<Ac<<endl;
    cout<<"The determinant of Ac is "<<Ac.determinant()<<endl;        // 矩阵行列式
    cout<<"The inverse of Ac is:\n"<<Ac.inverse()<<endl;              // 逆矩阵


// Eigen也提供了解最小二乘问题的解法，并给出两种实现，分别是BDCSVD和JacobiSVD,其中推荐使用的一种是BDCSVD。下面是一个例子
    MatrixXf Ad = MatrixXf::Random(3,2);
    cout<<"Here is the matrix Ad:\n"<<Ad<<endl;
    VectorXf bc = VectorXf::Random(3);
    cout<<"Here is the right hand side bc:\n"<<bc<<endl;
    cout<<"The least-squares solution is:\n"
        <<Ad.bdcSvd(ComputeThinU|ComputeThinV).solve(bc)<<endl;




    system("pause");
    return 0;
}