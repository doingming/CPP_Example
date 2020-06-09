// http://eigen.tuxfamily.org/dox/AsciiQuickReference.txt

#include <iostream>
#include <stdlib.h>
#include "eigen3/Eigen/Dense"
#include <algorithm>
#include <functional>


using namespace Eigen;

Matrix<double, 3, 3> A;                     // Fixed rows and cols. Same as Matrix3d.
Matrix<double, 3, Dynamic> B;               // Fixed rows, dynamic cols.
Matrix<double, Dynamic, Dynamic> C;         // Full dynamic. Same as MatrixXd.
Matrix<float, Dynamic, Dynamic> D;         // Full dynamic. Same as MatrixXd.
Matrix<double, 3, 3, RowMajor> E;           // Row major; default is column-major.
Matrix3f P, Q, R;                              // 3x3 float matrix.
Vector3f x, y, z;                           // 3x1 float matrix.
RowVector3f a, b, c;                        // 1x3 float matrix.
VectorXd v, vx;                                 // Dynamic column vector of doubles

VectorXf t;
Matrix<double, 6, 6> H;


float func(float arg1)  
{
    arg1 += 2; 
  
    return arg1;  
}  


int main()
{
    double s;
    
    int l=0,i=1,j=1,n = 2;
    int rows=4,cols=4;
    int size=9,low=2,high=6,step=1;

    b << 1,2,3;

    std::cout << "quick start"<< std::endl;
    C.resize(2,3);
    C << 11,12,13,
         14,15,16;


    // Basic usage
    //Eigen          //Matlab          //comment
    l=x.size();      //length(x)       //vector size                             // 向量的长度
    l=C.rows();      //size(C,1)       //number of rows                         // 矩阵的行数
    l=C.cols();      //size(C,2)       //number of columns                      // 矩阵的列数
    s=x(i);          //x(i+1)          //Matlab is 1-based  (vector)            // 访问向量元素（Matlab的下标从1开始计数）
    s=C(i,j);        //C(i+1,j+1)      //                                       // 访问矩阵元素


//  A.resize(4, 4);     // Runtime error if assertions are on.
//  B.resize(4, 9);     // Runtime error if assertions are on.
    A.resize(3, 3);     // Ok; size didn't change.
    B.resize(3, 9);     // Ok; only dynamic cols changed.

    A << 1, 2, 3,       // Initialize A. The elements can also be
        4, 5, 6,       // matrices, which are stacked along cols
        7, 8, 9;       // and then the rows are stacked.
    B << A, A, A;       // B is three horizontally stacked A's.
    A.fill(10);         // Fill A with all 10's.

    P << 1, 2, 3,  
        4, 5, 6,
        7, 8, 9; 
          
    H << 1, 2, 3, 0, 0, 2,     
        4, 5, 6, 0, 0, 2,      
        7, 8, 9, 0, 0, 2,
        0, 0, 0, 0, 0, 2,
        0, 0, 0, 0, 0, 2,
        1, 1, 1, 1, 1, 0;        


    // Eigen                                    // Matlab
    C=MatrixXd::Identity(rows,cols);            // eye(rows,rols)                   //单位矩阵
    C.Identity(rows,cols +1);                   // C = eye(rows,rols)               //单位矩阵
    std::cout << C << std::endl << std::endl;
    
    C=MatrixXd::Zero(rows,cols);                // zeros(rows,cols)                 //全零矩阵
    C.setZero(rows +1,cols);                    // C = zeros(rows,cols)             //全零矩阵
    std::cout << C << std::endl << std::endl;

    C=MatrixXd::Ones(rows,cols);                // ones(rows,cols)                  //全一矩阵
    C.setOnes(rows,cols +1);                    // C = ones(rows,cols)              //全一矩阵
    std::cout << C << std::endl << std::endl;

    C=MatrixXd::Random(rows,cols);              // rand(rows,cols)*2-1          // MatrixXd::Random returns uniform random numbers in (-1, 1).          //MatrixXd::Random 返回范围为(-1, 1)的均匀分布的随机数
    C.setRandom(rows +1,cols);                  // C = rand(rows,cols)*2-1           //返回范围为(-1, 1)的均匀分布的随机数
    std::cout << C << std::endl << std::endl;

    v=VectorXd::LinSpaced(size,low,high);       // linspace(low,high,size)'         //vector 返回size个等差数列，第一个数为low，最后一个数为high
    std::cout << v << std::endl << std::endl;
    vx.setLinSpaced(size,low,high + 2);         // v= linspace(low,high,size)'      //返回size个等差数列，第一个数为low，最后一个数为high 
    std::cout << vx << std::endl << std::endl;
    VectorXi vv = VectorXi::LinSpaced(((high-low)/step)+1,      // low:step:hi      //以step为步长的等差数列。((hi-low)/step)+1为个数
                    low,low+step*(size-1));  //
    std::cout << vv << std::endl << std::endl;


    // Matrix slicing and blocks. All expressions listed here are read/write.
    // Templated size versions are faster. Note that Matlab is 1-based (a size N
    // vector is x(1)...x(N)).
    // 矩阵分块
    // Eigen                            // Matlab                               // Comment
    x.head(n);                          // x(1:n)                               the first n coeffs          //前n个元素
    // x.head<n>();                     // x(1:n)                                                           //前n个元素
    x.tail(n);                          // x(end - n + 1: end)                  the last n coeffs           //倒数n个元素 
    // x.tail<n>();                     // x(end - n + 1: end)                                              //倒数n个元素
    x.segment(i, n);                    // x(i+1 : i+n)                         the n coeffs in the range [i : i + n - 1]       //切片
    // x.segment<n>(i);                 // x(i+1 : i+n)                                                                         //切片
    C = H.block(i, j, rows, cols);      // H(i+1 : i+rows, j+1 : j+cols)        the rows x cols sub-matrix starting from position (i,j)     //块
    // H.block<rows, cols>(i, j);       // H(i+1 : i+rows, j+1 : j+cols)                                                                    //块
    C = H.row(i);                       // H(i+1, :)            4 5 6 0 0 2                                 //第i行
    C = H.col(j);                       // H(:, j+1)            (2 5 8 0 0 1)                               //第j列

    C = H.leftCols(cols);               // H(:, 1:cols)                                                     //前cols列
    // H.leftCols<cols>();              // H(:, 1:cols)                                                     //前cols列
    C = H.middleCols(j, cols);          // H(:, j+1:j+cols)                                                 //中间cols列
    // H.middleCols<cols>(j)            // H(:, j+1:j+cols)                                                 //中间cols列
    C = H.rightCols(cols);              // H(:, end-cols+1:end)                                             //后cols列
    // H.rightCols<cols>()              // H(:, end-cols+1:end)                                             //后cols列

    C = H.topRows(rows);                // H(1:rows, :)                                                     //前rows行
    // H.topRows<rows>()                // H(1:rows, :)                                                     //前rows行
    C = H.middleRows(i, rows);          // H(i+1:i+rows, :)                                                 //中间rows行  
    // H.middleRows<rows>(i)            // H(i+1:i+rows, :)                                                 //中间rows行  
    H.bottomRows(rows);                 // H(end-rows+1:end, :)                                             //最后rows行      
    // H.bottomRows<rows>()             // H(end-rows+1:end, :)                                             //最后rows行      

    C = H.topLeftCorner(rows, cols);        // H(1:rows, 1:cols)                                            //左上角块
    C = H.topRightCorner(rows, cols);       // H(1:rows, end-cols+1:end)                                    //右上角块
    C = H.bottomLeftCorner(rows, cols);     // H(end-rows+1:end, 1:cols)                                    //左下角块
    C = H.bottomRightCorner(rows, cols);    // H(end-rows+1:end, end-cols+1:end)                            //右下角块
    // H.topLeftCorner<rows,cols>()         // H(1:rows, 1:cols)                                            //左上角块
    // H.topRightCorner<rows,cols>()        // H(1:rows, end-cols+1:end)                                    //右上角块
    // H.bottomLeftCorner<rows,cols>()      // H(end-rows+1:end, 1:cols)                                    //左下角块
    // H.bottomRightCorner<rows,cols>()     // H(end-rows+1:end, end-cols+1:end)                            //右下角块
    

    // Of particular note is Eigen's swap function which is highly optimized.
    // Eigen                           // Matlab
    // 矩阵元素交换
    R.row(i) = P.col(j);               // R(i, :) = P(:, j)
    R.col(j).swap(P.col(j+1));      // R(:, [j1 j2]) = R(:, [j2, j1])                                       //交换列 

    std::cout << "R:" << std::endl << R << std::endl << std::endl;



    D.resize(3,3);
    D << 11,12,13,
         14,15,16,
         17,18,19;
    // Views, transpose, etc;
    // 矩阵的转置
    // Eigen                           // Matlab
    D = R.adjoint();                        // R'                                       // 共轭转置
    D = R.transpose();                      // R.' or conj(R')       // Read-write      // 矩阵的转置
    t = R.diagonal();                       // diag(R)               // Read-write      // 对角元素
    D = t.asDiagonal();                     // diag(x)                                  // 对角矩阵化
    D = R.transpose().colwise().reverse();  // rot90(R)              // 可读/写         //逆时针旋转90度
    D = R.rowwise().reverse();              // fliplr(R)             // 水平翻转  
    D = R.colwise().reverse();              // flipud(R)             // 垂直翻转 
    D = R.replicate(i+1,j);                 // repmat(P,i,j)         // 复制矩阵，垂直复制i个，水平复制j个

    std::cout << D << std::endl << std::endl;

    Q << 1,2,2,  // 初始化 Q矩阵
         1,1,2,
         1,1,1;
    // All the same as Matlab, but matlab doesn't have *= style operators.      四则运算，和Matlab相同。但Matlab中不能使用*=这样的赋值运算符  
    // Matrix-vector.  Matrix-matrix.   Matrix-scalar.  s=15
    y  = R*x;           R  = P*Q;        R  = P*s;
    a  = b*R;           R  = P - Q;      R  = s*P;
    a *= R;             R  = P + Q;      R  = P/s;
                        R *= Q;          R  = s*P;
                        R += Q;          R *= s;
                        R -= Q;          R /= s;

    std::cout << "P:" << std::endl << P << std::endl << std::endl ;
    // Vectorized operations on each element independently              逐像素（元素）操作
    // Eigen                            // Matlab
    R = P.cwiseProduct(Q);              // R = P .* Q                   两个矩阵元素对应相乘
    R = P.array() * s;                  // R = P .* s                   矩阵元素乘以s
    R = P.cwiseQuotient(Q);             // R = P ./ Q                   两个矩阵元素对应相除
    R = P.array() / Q.array();          // R = P ./ Q                   同上
    R = P.array() + s;                  // R = P + s                    矩阵元素加上s
    R = P.array() - s;                  // R = P - s                    //逐元素减法（s为标量）
    R.array() += s;                     // R = R + s                    //逐元素加法（s为标量）
    R.array() -= s;                     // R = R - s                    //逐元素减法（s为标量）
    R.array() < Q.array();              // R < Q                        //逐元素比较运算
    R.array() <= Q.array();             // R <= Q                       //逐元素比较运算
    R = P.cwiseInverse();               // 1 ./ P                       //矩阵元素取倒数
    R = P.array().inverse();            // 1 ./ P                       //矩阵元素取倒数
    R = P.array().sin();                // sin(P)                       //逐元素计算正弦函数  
    R = P.array().cos();                // cos(P)                       //逐元素计算余弦函数
    R = P.array().pow(s);               // P .^ s                       //逐元素计算幂函数
    R = P.array().square();             // P .^ 2                       //逐元素计算平方
    R = P.array().cube();               // P .^ 3                       //逐元素计算立方
    R = P.cwiseSqrt();                  // sqrt(P)                      //逐元素计算平方根
    R = P.array().sqrt();               // sqrt(P)                      //逐元素计算平方根
    R = P.array().exp();                // exp(P)                       //逐元素计算指数函数
    R = P.array().log();                // log(P)                       //逐元素计算对数函数
    R = Q.cwiseMax(P);                  // max(Q, P)                    //逐元素取Q和P的最大值  
    R = Q.array().max(P.array());       // max(Q, P)                    //逐元素取Q和P的最大值
    R = Q.cwiseMin(P);                  // min(Q, P)                    //逐元素取R和P的最小值
    R = Q.array().min(P.array());       // min(Q, P)                    //逐元素取R和P的最小值
    R = P.cwiseAbs();                   // abs(P)                       //逐元素计算R和P的绝对值  
    R = P.array().abs();                // abs(P)                       //逐元素计算R和P的绝对值  
    R = P.cwiseAbs2();                  // abs(P.^2)                    //逐元素计算平方 
    R = P.array().abs2();               // abs(P.^2)                    //逐元素计算平方 
    R = (R.array() < s).select(P,Q );   // (R < s ? P : Q)              //根据R的元素值是否小于s，选择P和Q的对应元素
    R = (Q.array()==0).select(P,R);     // R(Q==0) = P(Q==0)            //根据Q中元素等于零的位置选择P中元素
    R = P.unaryExpr(std::ptr_fun(func)); // R = arrayfun(func, P)       // with: scalar func(const scalar &x);   // 对P中的每个元素应用func函数   // C++11中 std::ptr_fun 被更通用的 std::function 和 std::ref 所替代

    std::cout << R << std::endl << std::endl;


    // Reductions.
    int r, c;
    // Eigen                  // Matlab
    s = P.minCoeff();              // min(R(:))                                                     // 最小值
    s = P.maxCoeff();              // max(R(:))                                                     // 最大值
    s = P.minCoeff(&r, &c);    // [s, i] = min(R(:)); [r, c] = ind2sub(size(R), i);                 //取最小值和它的位置
    s = P.maxCoeff(&r, &c);    // [s, i] = max(R(:)); [r, c] = ind2sub(size(R), i);                 //取最大值和它的位置
    s = P.sum();                   // sum(R(:))                                                     //求和（所有元素）
    t = P.colwise().sum();         // sum(R)                                                        //按列求和  得到一个vector
    t = P.rowwise().sum();         // sum(R, 2) or sum(R')'                                         //按行求和  得到一个vector
    s = D.prod();                  // prod(R(:))                                                    // 累积（累乘）
    t = P.colwise().prod();        // prod(R)                                                       // 按列累积
    t = P.rowwise().prod();        // prod(R, 2) or prod(R')'                                       // 按行累积
    s = P.trace();                 // trace(R)                                                      // 矩阵的迹
    s = P.all();                   // all(R(:))                                                     //是否所有元素都非零
    t = P.colwise().all();         // all(R)                                                        //按列判断，是否该列所有元素都非零
    t = P.rowwise().all();         // all(R, 2)                                                     //按行判断，是否该行所有元素都非零
    s = P.any();                   // any(R(:))                                                     //是否有元素非零
    t = P.colwise().any();         // any(R)                                                        //按列判断，是否该列有元素都非零
    t = P.rowwise().any();         // any(R, 2)                                                     //按行判断，是否该行有元素都非零


    // Dot products, norms, etc.        // 向量 点积，范数等
    // Eigen                        // Matlab
    s = x.norm();                   // norm(x).    Note that norm(R) doesn't work in Eigen.          //范数（注意：Eigen中没有norm(R)）  
    s = x.squaredNorm();            // dot(x, x)   Note the equivalence is not true for complex      //平方和（注意：对于复数而言，不等价）
    s = x.dot(y);                   // dot(x, y)                                                     //点积（点乘）
    t = x.cross(y);                 // cross(x, y) Requires #include <Eigen/Geometry>                //交叉积（叉乘），需要头文件 #include <Eigen/Geometry> 


    //// Type conversion      // 类型转换
    // Eigen                  // Matlab
    A.cast<double>();         // double(A)                                                          //变成双精度类型
    A.cast<float>();          // single(A)                                                          //变成单精度类型
    A.cast<int>();            // int32(A)                                                           //变成整型
    A.real();                 // real(A)                                                            //实部
    A.imag();                 // imag(A)                                                            //虚部
    // if the original type equals destination type, no work is done

    
    // Note that for most operations Eigen requires all operands to have the same type:             // 注意：Eigen中，绝大多数的涉及多个操作数的运算都要求操作数具有相同的类型
    MatrixXf F = MatrixXf::Zero(3,3);
    // A += F;                // illegal in Eigen. In Matlab A = A+F is allowed                     // A是double类型
    A += F.cast<double>(); // F converted to double and then added (generally, conversion happens on-the-fly)

    // Eigen can map existing memory into Eigen matrices.                                                                                       // Eigen 可以将已存储数据的缓存 映射成 Eigen矩阵
    float array[3];
    Vector3f::Map(array).fill(10);            // create a temporary Map over array and sets entries to 10
    int data[4] = {1, 2, 3, 4};
    Matrix2i mat2x2(data);                    // copies data into mat2x2                                                                        // 将 data 复制到 mat2x2
    Matrix2i::Map(data) = 2*mat2x2;           // overwrite elements of data with 2*mat2x2                                                       // 使用 2*mat2x2 覆写data的元素
    MatrixXi::Map(data, 2, 2) += mat2x2;      // adds mat2x2 to elements of data (alternative syntax if size is not know at compile time)       // 加法，将 mat2x2 加到 data的元素上 (当编译时不知道大小时，可选的语法) 



    // ------------------------------------------------------------------------------------------------------------------------------------------
    // Solve Ax = b. Result stored in x. Matlab: x = A \ b.                             // 求解线性方程组  可以参照GITHUB\CPP_Example\Eigen\Eigen_Solve1.cpp
    // R = P.ldlt().solve(Q);  // A sym. p.s.d.    #include <Eigen/Cholesky>            // LDLT分解法     要求矩阵A正或负半定
    // R = P.llt() .solve(Q);  // A sym. p.d.      #include <Eigen/Cholesky>            // LLT分解法      要求矩阵A正定
    R = P.lu()  .solve(Q);  // Stable and fast. #include <Eigen/LU>                     // LU分解法       或 R = P.partialPivLu().solve(Q); 或 R = P.fullPivLu().solve(Q);
    // R = P.qr()  .solve(Q);  // No pivoting.     #include <Eigen/QR>
    // R = P.svd() .solve(Q);  // Stable, slowest. #include <Eigen/SVD>
    // .ldlt() -> .matrixL() and .matrixD()
    // .llt()  -> .matrixL()
    // .lu()   -> .matrixL() and .matrixU()
    // .qr()   -> .matrixQ() and .matrixR()
    // .svd()  -> .matrixU(), .singularValues(), and .matrixV()

    std::cout << R << std::endl << std::endl;


    // Eigenvalue problems
    // Eigen                          // Matlab
    A.eigenvalues();                  // eig(A);                    // 矩阵特征值  包含实部和虚部
    EigenSolver<Matrix3d> eig(A);     // [vec val] = eig(A)
    eig.eigenvalues();                // diag(val)                  // 特征值，与上面的特征值相等
    eig.eigenvectors();               // vec                        // 特征向量
    // For self-adjoint matrices use SelfAdjointEigenSolver<>


    system("pause");
    return 0;
}