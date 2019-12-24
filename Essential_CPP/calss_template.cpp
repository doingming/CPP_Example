#include <iostream>
#include <stdlib.h>

template <typename T1,typename T2>
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

template <class T1, class T2>
void ZZZ<T1, T2>::setX(T1 x){
    m_x = x;
}
template <class T1, class T2>
void ZZZ<T1, T2>::setY(T2 y){
    m_y = y;
}

template <class T1, class T2>
T1 ZZZ<T1, T2>::getX() const{
    return m_x;
}
template <class T1, class T2>
T2 ZZZ<T1, T2>::getY() const{
    return m_y;
}


int main(){
    ZZZ<int, int> p1(10, 20);
    std::cout<<"x="<<p1.getX()<<", y="<<p1.getY()<<std::endl;

    ZZZ<int, char*> p2(10, "east 180");
    std::cout<<"x="<<p2.getX()<<", y="<<p2.getY()<<std::endl;

    ZZZ<char*, char*> *p3 = new ZZZ<char*, char*>("east180 ", "west210 ");
    std::cout<<"x="<<p3->getX()<<", y="<<p3->getY()<<std::endl;
    
    system("pause");
    return 0;
}
