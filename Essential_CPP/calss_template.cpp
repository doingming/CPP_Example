#include <iostream>
#include <stdlib.h>

template <typename T1,typename T2>//这里不能有分号
class ZZZ{
    public:
        ZZZ(T1 x, T2 y): m_x(x),m_y(y) {    //构造函数参数初始化列表
            //TODO
        }
    public:
        T1 getX() const;    //const成员函数
        T2 getY() const;
        void setX(T1 x);
        void setY(T2 y);
    private:
        T1 m_x;
        T2 m_y;
};

// 对类的成员函数进行定义
template <class T1, class T2>//模板头
T1 ZZZ<T1, T2>::getX() const{
    return m_x;
}
template <class T1, class T2>//模板头
T2 ZZZ<T1, T2>::getY() const{
    return m_y;
}
template <class T1, class T2>//模板头
void ZZZ<T1, T2>::setX(T1 x){
    m_x = x;
}
template <class T1, class T2>//模板头
void ZZZ<T1, T2>::setY(T2 y){
    m_y = y;
}


int main(){
    ZZZ<int, int> p1(10, 20);// 出现于complex之后的尖括号，表示complex是一个template class(模板类)，参数类型是int类型，就如：     //complex<double> purei(0.0, 7.9);
    std::cout<<"x="<<p1.getX()<<", y="<<p1.getY()<<std::endl;

    ZZZ<int, char*> p2(10, "east 180");
    std::cout<<"x="<<p2.getX()<<", y="<<p2.getY()<<std::endl;

    ZZZ<char*, char*> *p3 = new ZZZ<char*, char*>("east180 ", "west210 ");
    std::cout<<"x="<<p3->getX()<<", y="<<p3->getY()<<std::endl;
    
    system("pause");
    return 0;
}
