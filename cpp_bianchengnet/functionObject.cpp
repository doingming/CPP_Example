// 仿函数  函数对象
// 仿函数本质就是类重载了一个operator()，创建一个行为类似函数的对象。

#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <algorithm>// count_if


// 仿函数例子一
// 单个操作数 unary function object
class func22
{
public:
    float operator()(float a1) const
    {   //重载()运算符
    return a1 + 3;
    }
};


// 仿函数例子二
// 两个操作数 binary function object
struct MyPlus{
    int operator()(const int &a , const int &b) const{
        return a+b;
    }
};


// 仿函数例子三
class ShorterThan {
    public:
        explicit ShorterThan(int maxLength) : length(maxLength) {}      // 构造函数 ， 被explicit关键字修饰的类构造函数，不能进行自动地隐式类型转换，只能显式地进行类型转换。
        bool operator() (const std::string& str) const {                // 重载 () 运算符  只有一个操作数
            return str.length() < length;
        }
    private:
        const int length;
};


// 普通函数  可以使用 std::ptr_fun(func33) 将普通函数转化为仿函数  fftest 移到 find.cpp
bool compare(std::string input_fruits)
{
    return input_fruits.length() < 6;
}



//仿函数的使用
int main() {

    MyPlus a;
    std::cout << MyPlus()(1,2) << std::endl;            //1、通过产生临时对象调用重载运算符         //ff (在STL中，当需要传递仿函数对象的时候,常用这种方式，
                                                                                                 //ff 因为传递进去仅仅为了给容器内部成员赋值，所以没有必要生成对象，产生临时对象即可。)
    std::cout << a.operator()(1,2) << std::endl;        //2、通过对象显示调用重载运算符
    std::cout << a(1,2) << std::endl;                   //3、通过对象类似函数调用 隐示地调用重载运算符  
    
    func22 cd;
    std::cout << func22()(5) << std::endl;
    std::cout << cd.operator()(5) << std::endl;
    std::cout << cd(5) << std::endl;
    
    std::vector<std::string>myVector;
    myVector.push_back("apple");
    myVector.push_back("banana");
    myVector.push_back("lemon");
    myVector.push_back("pear");
    myVector.push_back("oranges");
    int length = 6 ,result = 0;
    result = std::count_if(myVector.begin(), myVector.end(), ShorterThan(length));//直接调用即可
    std::cout << "count_if resulta: " << result << std::endl;



    result = std::count_if(myVector.begin(), myVector.end(), compare);// count_if第三个参数使用只有一个参数一个bool返回值的普通函数
    std::cout << "count_if resultb: " << result << std::endl;

    result = std::count_if(myVector.begin(), myVector.end(), std::ptr_fun(compare));// count_if第三个参数使用仿函数
    std::cout << "count_if resultc: " << result << std::endl;


    system("pause");
    return 0;
}



